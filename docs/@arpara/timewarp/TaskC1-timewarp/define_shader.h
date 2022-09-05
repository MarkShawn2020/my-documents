
/*
 * GLSL Barrel Distortion Shader Program based on pre-computed
 * lens distortion correction mesh.
 */
#if defined(IVR_GRAPHICS_API_GLES2)
static const char *s_barrelDistortion1VertexShader =
R"SHADER(
#version 100
precision mediump float;
uniform mat4 u_timewarp_mat;
uniform bool u_enable_timewarp;

attribute vec2 a_texcoord;
varying vec2 v_texcoord;

void main()
{
    if (u_enable_timewarp)
    {
        // re-project texture based on timewarp transform
        vec2 center = vec2(0.5, 0.5);
        vec2 uv_centered = a_texcoord - center;
        vec3 tan_eye_angle = vec3(uv_centered.x, uv_centered.y, 1.0);
        vec4 uv_warped = u_timewarp_mat * vec4(tan_eye_angle, 0.0);
        float rz = 1.0 / uv_warped.z;
        uv_centered = vec2(uv_warped.x * rz, uv_warped.y * rz);
        v_texcoord = uv_centered + center;
    }
    else
    {
        v_texcoord = a_texcoord;
    }
}
)SHADER";
#elif defined(IVR_GRAPHICS_API_GLCORE)
static const char *s_barrelDistortion1VertexShader =
R"SHADER(
#version 330
precision mediump float;
uniform mat4 u_timewarp_mat;
uniform bool u_enable_timewarp;

layout(location = 1) in vec2 a_texcoord;
out vec2 v_texcoord;

void main()
{
    if (u_enable_timewarp)
    {
        // re-project texture based on timewarp transform
        vec2 center = vec2(0.5, 0.5);
        vec2 uv_centered = a_texcoord - center;
        vec3 tan_eye_angle = vec3(uv_centered.x, uv_centered.y, 1.0);
        vec4 uv_warped = u_timewarp_mat * vec4(tan_eye_angle, 0.0);
        float rz = 1.0 / uv_warped.z;
        uv_centered = vec2(uv_warped.x * rz, uv_warped.y * rz);
        v_texcoord = uv_centered + center;
    }
    else
    {
        v_texcoord = a_texcoord;
    }
}
)SHADER";

#else
#error No implementation of Barrel Distortion 1 shader
#endif

#if defined(IVR_GRAPHICS_API_GLES2)
static const char *s_barrelDistortion1FragmentShader =
    R"SHADER(
#version 100
precision mediump float;

uniform sampler2D eye_texture;
uniform float u_aspect;
uniform float u_lens_scale;
uniform vec2 u_lens_center;
uniform vec2 u_uv_min;
uniform vec2 u_uv_max;
uniform vec2 u_chroma_red;
uniform vec2 u_chroma_blue;
uniform bool u_chroma_correct;
varying vec2 v_texcoord;

float chroma_scale(float radius, vec2 chroma_correction)
{
    float scale = chroma_correction[0] + chroma_correction[1] * radius;
    return scale;
}

vec2 transform_to_lens_offset(vec2 view_uv)
{
    // Move origin to center of viewport and scale to -1 to 1
    vec2 lens_offset = view_uv * 2.0 - 1.0;

    // translate origin to lens center
    lens_offset -= u_lens_center;

    // Correct for the aspect ratio
    lens_offset.y /= u_aspect;

    return lens_offset;
}

vec2 transform_to_texture_coordinate(vec2 lens_offset)
{
    vec2 uv = lens_offset;

    // Restore correct aspect ratio
    uv.y *= u_aspect;

    // Translate origin back to screen center
    uv += u_lens_center;

    // Apply scale adjustment to account for eye texture resolution
    // may be higher than the final screen resolution
    uv *= u_lens_scale;

    // Scale and translate back into normal texture coordinates between 0 and 1
    uv = (uv * 0.5) + 0.5;

    return uv;
}

void main()
{
    // compute uv for red and blue channels to account for chromatic aberration
    if (u_chroma_correct)
    {
        // first transform screen coordinate to lens centered coordinate
        vec2 uv_centered = transform_to_lens_offset(v_texcoord);

        vec2 uv_centered_squared = uv_centered * uv_centered;
        float radius = sqrt(uv_centered_squared.x + uv_centered_squared.y);

        // scale and translate texture coordinate to uv region containing the eye image
        vec2 range_scale = (u_uv_max - u_uv_min);

        // correct red component
        vec2 offset_red = uv_centered * chroma_scale(radius, u_chroma_red);
        vec2 texture_uv_r = transform_to_texture_coordinate(offset_red);
        texture_uv_r = (texture_uv_r * range_scale) + u_uv_min;

        // correct blue component
        vec2 offset_blue = uv_centered * chroma_scale(radius, u_chroma_blue);
        vec2 texture_uv_b = transform_to_texture_coordinate(offset_blue);
        texture_uv_b = (texture_uv_b * range_scale) + u_uv_min;

        // uncorrected green component
        vec2 texture_uv_g = transform_to_texture_coordinate(uv_centered);
        texture_uv_g = (texture_uv_g * range_scale) + u_uv_min;

        vec4 color;
        color.r = texture2D(eye_texture, texture_uv_r).r;
        color.g = texture2D(eye_texture, texture_uv_g).g;
        color.b = texture2D(eye_texture, texture_uv_b).b;
        color.a = 1.0;

        gl_FragColor = color;
    }
    else
    {
        vec2 range_scale = (u_uv_max - u_uv_min);
        vec2 texture_uv = (v_texcoord * range_scale) + u_uv_min;

        gl_FragColor = texture2D(eye_texture, texture_uv);
    }
}
)SHADER";
#elif defined(IVR_GRAPHICS_API_GLCORE)
static const char* s_barrelDistortion1FragmentShader =
R"SHADER(
#version 330
precision mediump float;

uniform sampler2D eye_texture;
uniform float u_aspect;
uniform float u_lens_scale;
uniform vec2 u_lens_center;
uniform vec2 u_uv_min;
uniform vec2 u_uv_max;
uniform vec2 u_chroma_red;
uniform vec2 u_chroma_blue;
uniform bool u_chroma_correct;
in vec2 v_texcoord;
out vec4 o_frag_color;

float chroma_scale(float radius, vec2 chroma_correction)
{
    float scale = chroma_correction[0] + chroma_correction[1] * radius;
    return scale;
}

vec2 transform_to_lens_offset(vec2 view_uv)
{
    // Move origin to center of viewport and scale to -1 to 1
    vec2 lens_offset = view_uv * 2.0 - 1.0;

    // translate origin to lens center
    lens_offset -= u_lens_center;

    // Correct for the aspect ratio
    lens_offset.y /= u_aspect;

    return lens_offset;
}

vec2 transform_to_texture_coordinate(vec2 lens_offset)
{
    vec2 uv = lens_offset;

    // Restore correct aspect ratio
    uv.y *= u_aspect;

    // Translate origin back to screen center
    uv += u_lens_center;

    // Apply scale adjustment to account for eye texture resolution
    // may be higher than the final screen resolution
    uv *= u_lens_scale;

    // Scale and translate back into normal texture coordinates between 0 and 1
    uv = (uv * 0.5) + 0.5;

    return uv;
}

void main()
{
    // compute uv for red and blue channels to account for chromatic aberration
    if (u_chroma_correct)
    {
        // first transform screen coordinate to lens centered coordinate
        vec2 uv_centered = transform_to_lens_offset(v_texcoord);

        vec2 uv_centered_squared = uv_centered * uv_centered;
        float radius = sqrt(uv_centered_squared.x + uv_centered_squared.y);

        // scale and translate texture coordinate to uv region containing the eye image
        vec2 range_scale = (u_uv_max - u_uv_min);

        // correct red component
        vec2 offset_red = uv_centered * chroma_scale(radius, u_chroma_red);
        vec2 texture_uv_r = transform_to_texture_coordinate(offset_red);
        texture_uv_r = (texture_uv_r * range_scale) + u_uv_min;

        // correct blue component
        vec2 offset_blue = uv_centered * chroma_scale(radius, u_chroma_blue);
        vec2 texture_uv_b = transform_to_texture_coordinate(offset_blue);
        texture_uv_b = (texture_uv_b * range_scale) + u_uv_min;

        // uncorrected green component
        vec2 texture_uv_g = transform_to_texture_coordinate(uv_centered);
        texture_uv_g = (texture_uv_g * range_scale) + u_uv_min;

        vec4 color;
        color.r = texture(eye_texture, texture_uv_r).r;
        color.g = texture(eye_texture, texture_uv_g).g;
        color.b = texture(eye_texture, texture_uv_b).b;
        color.a = 1.0;

        o_frag_color = color;
    }
    else
    {
        vec2 range_scale = (u_uv_max - u_uv_min);
        vec2 texture_uv = (v_texcoord * range_scale) + u_uv_min;

        o_frag_color = texture(eye_texture, texture_uv);
    }
}
)SHADER";
#else
#error No implementation of Barrel Distortion 1 shader
#endif
