# aosp changes

1. [aosp surfaceflinger changes](#aosp-surfaceflinger-changes)
   1. [conclusion](#conclusion)
   2. [7 -> 8](#7---8)
   3. [8 -> 9](#8---9)
   4. [9 -> 10](#9---10)
   5. [10 -> 11](#10---11)
   6. [7 -> 11](#7---11)
2. [aosp code changes of native/service/surfaceflinger](#aosp-code-changes-of-nativeservicesurfaceflinger)
   1. [aosp diff 7 vs 8](#aosp-diff-7-vs-8)
      1. [diff 7-8 `./native`](#diff-7-8-native)
      2. [diff 7-8 `../service`](#diff-7-8-service)
      3. [diff 7-8 `.../surfaceflinger`](#diff-7-8-surfaceflinger)
   2. [aosp diff: 8 vs 9](#aosp-diff-8-vs-9)
      1. [diff 8-9 `./native`](#diff-8-9-native)
      2. [diff 8-9 `../service`](#diff-8-9-service)
      3. [diff 8-9 `.../surfaceflinger`](#diff-8-9-surfaceflinger)
   3. [aosp diff: 9 vs 10](#aosp-diff-9-vs-10)
      1. [v10 change](#v10-change)
      2. [diff 9-10 `./native`](#diff-9-10-native)
      3. [diff 9-10 `../service`](#diff-9-10-service)
      4. [diff 9-10 `.../surfaceflinger`](#diff-9-10-surfaceflinger)
      5. [diff 9-10 `..../RenderEngine`](#diff-9-10-renderengine)
   4. [aosp diff: 10 vs 11](#aosp-diff-10-vs-11)
      1. [diff 10-11: `./native`](#diff-10-11-native)
      2. [diff 10-11: `../service`](#diff-10-11-service)
      3. [diff 10-11: `.../surfaceflinger`](#diff-10-11-surfaceflinger)
   5. [aosp diff: 7 vs 11](#aosp-diff-7-vs-11)
      1. [diff 7-11 `./native`](#diff-7-11-native)
      2. [diff 7-11 `../service`](#diff-7-11-service)
      3. [diff 7-11 `.../surfaceflinger`](#diff-7-11-surfaceflinger)
3. [aosp version changes about 架构、图形、安全、性能、测试](#aosp-version-changes-about-架构图形安全性能测试)
   1. [aosp 11 changes](#aosp-11-changes)
      1. [IMPORTANT: 图形](#important-图形)
   2. [aosp 10 changes](#aosp-10-changes)
   3. [aosp 9 changes](#aosp-9-changes)
   4. [aosp 8 changes](#aosp-8-changes)
      1. [IMPORTANT: 多显示器支持](#important-多显示器支持)
   5. [aosp 7 changes](#aosp-7-changes)
      1. [IMPORTANT: Vulkan API](#important-vulkan-api)
      2. [IMPORTANT: OpenGL™ ES 3.2 API](#important-opengl-es-32-api)
      3. [IMPORTANT: VR support](#important-vr-support)

## aosp surfaceflinger changes

### conclusion

1. `Android.mk` -> `Android.bp` (since 8, force 9)
2. removed `SurfaceFlinger_hwc1` which we used (9)
3. moved and re-constructed `RenderEngine` (10)
4. `.h` and `.cpp` separated (10)

### 7 -> 8

!!!warning 1. :warning: aosp 8 started using `Android.bp` (with `Android.mk`) 2. added `vr` and `displayservice` dirs under `../service` 3. removed `FenceTracker` and added some other interfaces (which seem not important) under `.../surfaceflinger`

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642701057733-8de0f763298cfd286796098b1728a840b54e92cf5b5b1a20f2a0694dbcfcbf27.png)

### 8 -> 9

!!!warning 1. :warning: aosp 9 started removing `Android.mk` 2. :warning: removed `SurfaceFlingerConsumer` and `SurfaceFlinger_hwc1`(we used) under `.../surfaceflinger`

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642702347374-44c2399ce465a71d3457951b6b75f6d9817e0b5275d319739ab9990be6834e0a.png)

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642702376282-6c347554b97a8c7ab69da89161443f8fffbd8958beb43bae42a6da6ac41388b4.png)

### 9 -> 10

!!!warning 1. :warning: `.h` and `.cpp` separated into `include` and `src` 2. :warning: `RenderEngine` is moved and reconstructed from under `naive/services/surfaceflinger` to under `native/libs/renderengine/`

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642702835607-de98d43cf127b4152c1d5f435da82410aebbc29302139f3bb2d6e4f2cd3f54f9.png)

![picture 24](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642703465268-ba17e0c40f3eb6dc8a17651c5b7271d209466e28a24e5ad08851bc2cb4e38914.png)

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642704090343-e251150b35f462aa7bbeeacf8f22024f0d8d5c82627c83a9a8bafb8cfc47f8ad.png)

### 10 -> 11

!!!warning aosp 11 added back the `FrameTracer`, and added `SurfaceFlingerDefaultFactory` update@2022-01-26: 太惨了，最重要的函数`doComposeSurfaces`不见了！文件级别还不够细，还得是函数级别才行……

![picture 28](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642704300910-3303fe00e44dcccc7b5325d8f945c406bddc0a0745b3d22198b7041e3d357bc4.png)

### 7 -> 11

![picture 46](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642668812648-413b3300a3200e7f1b4c85daa2da89195047eb5a606fba9e9bd58f113134b4f7.png)

![picture 48](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642668901996-bc7d9331aecd12ecd48ec458e05e6f1f4ffa95704e7f4e672a33b4e4d73685c3.png)

## aosp code changes of native/service/surfaceflinger

### aosp diff 7 vs 8

#### diff 7-8 `./native`

##### :warning: aosp 8 started using `Android.bp` (with `Android.mk`)

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642700740315-50e0bb18ecdf03e72572cf0a074fb9b154569f0ffaa0e13ce4ab95e7954d0bcc.png)

#### diff 7-8 `../service`

added `vr` and `displayservice` directories.

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642700922519-777c9495cc7d5489fe3675ea670e013ad1b36b29fd3ff376a3314b9d12472036.png)

#### diff 7-8 `.../surfaceflinger`

removed `FenceTracker` and added some other interfaces (which seem not important)

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642701057733-8de0f763298cfd286796098b1728a840b54e92cf5b5b1a20f2a0694dbcfcbf27.png)

### aosp diff: 8 vs 9

#### diff 8-9 `./native`

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642701257918-822bdf1a490b46b64ed803476f8f006c1d71a44e3dfb17eda0001e39f5713a0d.png)

#### diff 8-9 `../service`

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642701311594-359e8b7b4ce355b9cc4f84d2dfebf21665b60dcbb88296ecec1525d110f1f089.png)

#### diff 8-9 `.../surfaceflinger`

##### :warning: removed `SurfaceFlingerConsumer` and `SurfaceFlinger_hwc1` and `Android.mk`

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642702347374-44c2399ce465a71d3457951b6b75f6d9817e0b5275d319739ab9990be6834e0a.png)

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642702376282-6c347554b97a8c7ab69da89161443f8fffbd8958beb43bae42a6da6ac41388b4.png)

### aosp diff: 9 vs 10

#### v10 change

##### :warning: `.h` and `.cpp` separated into `include` and `src`

#### diff 9-10 `./native`

![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642702624393-410c445ccfd991d91097d8bccf2ec01dac77a473ca7000c371a48204122dd755.png)

#### diff 9-10 `../service`

![picture 20](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642702666363-e3648d1fde4e45c2df8e0af38fb2a64ffbc77bb5335ca9d66b54a3e7ba965521.png)

#### diff 9-10 `.../surfaceflinger`

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642702835607-de98d43cf127b4152c1d5f435da82410aebbc29302139f3bb2d6e4f2cd3f54f9.png)

#### diff 9-10 `..../RenderEngine`

the `CompositionEngine` added is not the former `RenderEngine`

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642703298440-c89776ebdf033b3c5b852a342b74e9ba9c4d1cc091e0fc0b5fdacfb8e1ff7273.png)

indeed, it moves from under `native/service` to under `native/libs`.

##### "warning: `RenderEngine` is under `native/libs/renderengine/gl` in AOSP 10

![picture 24](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642703465268-ba17e0c40f3eb6dc8a17651c5b7271d209466e28a24e5ad08851bc2cb4e38914.png)

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642704090343-e251150b35f462aa7bbeeacf8f22024f0d8d5c82627c83a9a8bafb8cfc47f8ad.png)

### aosp diff: 10 vs 11

#### diff 10-11: `./native`

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642704182326-c8e4cfb07f0a9efc63aee13725337465c63d71b84a883e16088841e97a95a61d.png)

#### diff 10-11: `../service`

![picture 27](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642704217482-7fc1a2231f3922c4d445f9477b4a8a0c0fd0c75c55ba567e8985e1de36623571.png)

#### diff 10-11: `.../surfaceflinger`

##### :warning: aosp 11 added back the `FrameTracer`, and added `SurfaceFlingerDefaultFactory`

![picture 28](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642704300910-3303fe00e44dcccc7b5325d8f945c406bddc0a0745b3d22198b7041e3d357bc4.png)

### aosp diff: 7 vs 11

#### diff 7-11 `./native`

![picture 44](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642668660936-88f3dbe0a55bf73e0f17294850e20253b2e4543d2871576907863aa791b2aeb9.png)

#### diff 7-11 `../service`

![picture 45](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642668727915-ce64867824398d804684bbddf38d45eeac44d5982e2f3bff5709070c841f7483.png)

#### diff 7-11 `.../surfaceflinger`

![picture 46](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642668812648-413b3300a3200e7f1b4c85daa2da89195047eb5a606fba9e9bd58f113134b4f7.png)  
![picture 48](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642668901996-bc7d9331aecd12ecd48ec458e05e6f1f4ffa95704e7f4e672a33b4e4d73685c3.png)

## aosp version changes about 架构、图形、安全、性能、测试

### aosp 11 changes

![picture 38](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661937875-9395cb050cd510ce0241d085d0d0d18346a490c87a73089707398f798ce34c83.png)

![picture 39](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642662104980-9319aa466246b7c81a3261445204dedcd596cb31c7a0e5a40b78aff124d9240b.png)

![picture 40](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642662115998-7146e607bdc8cf10d949930c76bcea9c202b46964d95a79a9123bdb91907c2ca.png)

![picture 41](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642662129881-fe58c1adfe2815f44c8f0fb9a38ffcaac6a878d7a6ca22de7a5503b328f7d55c.png)

#### [IMPORTANT: 图形](https://developer.android.com/about/versions/11/features#graphics)

![picture 42](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642662221453-4a2f06837b1ba8b86405cd0c44b07f391a2e308b719fe5f1f815a7fa8018d1f4.png)

![picture 43](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642662231570-e951c4ec876352c2d535075199cdc3cde1a97b2ad4b1dbdcf6fad624647ad184.png)

ref:

- [功能和 API 概览  |  Android 开发者  |  Android Developers](https://developer.android.com/about/versions/11/features)

### aosp 10 changes

![picture 28](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661658817-40a1b2e305e6a974f4c880a09c1f44d3eb58adeb1d5085b50ab3ddc873302554.png)

![picture 29](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661695856-24a0eea3b49417bea1de616840b096a30e89f7ba280bcb05b1f0dc0fb0dbbf63.png)

![picture 30](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661718996-c8acbc0833cabe5e49db402870f3a5b2a94545c11f0d913d3bba196c3a3a2056.png)

![picture 31](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661729795-3d72c4d287b25d388aa25e68df6d07332836aeb3544211322047a955aaeb6afc.png)

![picture 32](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661754156-cf9d4e538db6b37b5465638e8bcf4e902837b4448608204e4d1dd91b987be7d8.png)

![picture 33](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661789129-06692fe626afc80d5e6d7f8186b195f339b08f2967df543a585a70d3606fe664.png)

![picture 34](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661815913-84ded1315aa4197931c8d4a1bbfc53a8e0fa70a15aa78763153e71f43a3f057e.png)

![picture 35](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661835506-88ef5370bec63c91dade1cf37876a2355cb436db99e816882a207f15e1fcfef2.png)

![picture 36](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661843444-74ed25bf1834b07235dbef93a9b2a1db644718e3d9eb1a94e81d5e7654a3cf23.png)

![picture 37](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661858178-c7eb2efa04e02f8cca7c2cb46ef3993891cd9af8fb315ebfdf0f6384a7f12bce.png)

ref:

- [面向开发者的 Android 10  |  Android 开发者  |  Android Developers](https://developer.android.com/about/versions/10/highlights)

### aosp 9 changes

![picture 24](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661553995-159c8b1fbb05e655e24c34f806bfe3169bb675e3585666d6d6976dc20060d54b.png)

![picture 25](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661571665-5b43b36c81e60db10a51b032c4f36a9f010cfe51659c1b139ecbb1fefcc2bb2f.png)

![picture 26](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661612154-850a0ffb3a11a06c649770ab8d5549a824eb8dc1f1f331730b2a48be01e88233.png)

![picture 27](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661620656-83e18e583a0f94b738ff9c881b44b41014b0289facdc250195950e8de5b0325e.png)

ref:

- [Android 9 功能和 API  |  Android 开发者  |  Android Developers](https://developer.android.com/about/versions/pie/android-9.0)

### aosp 8 changes

![picture 19](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661296101-e439cf6469c25fb351c63c0be61995cf1ed9661e16eedf0f2a119a3e45d425e6.png)

![picture 20](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661330480-752c8f28c1b1483a31939c38baefd788289ea8af54e5eab60bd7de0e2161c37d.png)

#### [IMPORTANT: 多显示器支持](https://developer.android.com/about/versions/oreo/android-8.0#mds)

![picture 21](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661360991-c6cb2cffbca426e95010c789393b0f0eb795f8e65a9862e9c87619a629a2d68a.png)

![picture 22](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661423928-7f469690e59060def95f3b0776048fbb0c4ba67d12c9f2efadcb002e7fc8ea8b.png)

![picture 23](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661486439-06eca199076ddf9126c9ad7d75905fdc0b40e82a9269eaae8ef2478778441d62.png)

ref:

- [Android 8.0 功能和 API  |  Android 开发者  |  Android Developers](https://developer.android.com/about/versions/oreo/android-8.0)

### aosp 7 changes

![picture 10](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661026078-5453d2c7d157c2b29ddb6c11baa463daba274f9238b11bcba72633fe0e41da4a.png)

![picture 11](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661050505-a5152ce6aa2b88a520f9982ec5453b09064c970cc4d35c1f2da8fb9f5f5adcc3.png)

![picture 13](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661076846-e2b79d34fcf090cbe9efb708245119dd8c500a2aa93e4f0e7f2ac59733902121.png)

![picture 12](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661067057-158f52d6e686c258eaa595e9f48aec5246e4fd746fc89915d09b905fcbd52538.png)

#### [IMPORTANT: Vulkan API](https://developer.android.com/about/versions/nougat/android-7.0#vulkan)

![picture 14](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661088253-32aa86d60f801599b98ee135b7b322c8f03ad5050d41524640ca4ef0dc2bd6d4.png)

![picture 15](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661129877-81627c2d4171ab62ff2e84b9db141872501b17d3aaca3adef5b2cf41b01dd231.png)

#### [IMPORTANT: OpenGL™ ES 3.2 API](https://developer.android.com/about/versions/nougat/android-7.0#gles_32)

![picture 16](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661143361-29878bb4a8b112b5d651dcffcb37f25fb00f7115e6575670d6eb1a356d0e6c9a.png)

#### [IMPORTANT: VR support](https://developer.android.com/about/versions/nougat/android-7.0#vr)

![picture 17](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661217988-d33e9b09701c4f81c5647f136b553d4301a709073ffc8a64c04c555745e0d036.png)

![picture 18](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/notes-aosp-1642661245989-846a6276e5ee67ddcea2b8e06c3fc1a9ac7f59c8d7a7ae519fa0f3d54d0e3aa1.png)

ref:

- [Android 7.0 开发者版本  |  Android 开发者  |  Android Developers](https://developer.android.com/about/versions/nougat/android-7.0)
