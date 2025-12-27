---
title: Global Shortcut
slug: global-shortcut-1766149267397
source: https://v2.tauri.app/plugin/global-shortcut/
datetime: 2025-12-19T13:01:07.396Z
---

# Global Shortcut

[GitHub](https://github.com/tauri-apps/plugins-workspace/tree/v2/plugins/global-shortcut) [npm](https://www.npmjs.com/package/@tauri-apps/plugin-global-shortcut) [crates.io](https://crates.io/crates/tauri-plugin-global-shortcut)

API Reference[](/reference/javascript/global-shortcut/)[](https://docs.rs/tauri-plugin-global-shortcut)

Register global shortcuts.

## [Supported Platforms](#supported-platforms)

[Section titled “Supported Platforms”](#supported-platforms)

*This plugin requires a Rust version of at least **1.77.2***

| Platform | Level | Notes |
| --- | --- | --- |
| windows | 
 | 

 |
| linux | 

 | 

 |
| macos | 

 | 

 |
| android | 

 | 

 |
| ios | 

 | 

 |

## [Setup](#setup)

[Section titled “Setup”](#setup)

Install the global-shortcut plugin to get started.

-   [Automatic](#tab-panel-1082)
-   [Manual](#tab-panel-1083)

Use your project’s package manager to add the dependency:

-   [npm](#tab-panel-1071)
-   [yarn](#tab-panel-1072)
-   [pnpm](#tab-panel-1073)
-   [deno](#tab-panel-1074)
-   [bun](#tab-panel-1075)
-   [cargo](#tab-panel-1076)

```
npm run tauri add global-shortcut
```

```
yarn run tauri add global-shortcut
```

```
pnpm tauri add global-shortcut
```

```
deno task tauri add global-shortcut
```

```
bun tauri add global-shortcut
```

```
cargo tauri add global-shortcut
```

1.  Run the following command in the `src-tauri` folder to add the plugin to the project’s dependencies in `Cargo.toml`:
    
    ```
    cargo add tauri-plugin-global-shortcut --target 'cfg(any(target_os = "macos", windows, target_os = "linux"))'
    ```
    
2.  Modify `lib.rs` to initialize the plugin:
    
    src-tauri/src/lib.rs
    
    ```
    pub fn run() {    tauri::Builder::default()        .setup(|app| {            #[cfg(desktop)]            app.handle().plugin(tauri_plugin_global_shortcut::Builder::new().build());            Ok(())        })        .run(tauri::generate_context!())        .expect("error while running tauri application");}
    ```
    
3.  Install the JavaScript Guest bindings using your preferred JavaScript package manager:
    
    -   [npm](#tab-panel-1077)
    -   [yarn](#tab-panel-1078)
    -   [pnpm](#tab-panel-1079)
    -   [deno](#tab-panel-1080)
    -   [bun](#tab-panel-1081)
    
    ```
    npm install @tauri-apps/plugin-global-shortcut
    ```
    
    ```
    yarn add @tauri-apps/plugin-global-shortcut
    ```
    
    ```
    pnpm add @tauri-apps/plugin-global-shortcut
    ```
    
    ```
    deno add npm:@tauri-apps/plugin-global-shortcut
    ```
    
    ```
    bun add @tauri-apps/plugin-global-shortcut
    ```
    

## [Usage](#usage)

[Section titled “Usage”](#usage)

The global-shortcut plugin is available in both JavaScript and Rust.

-   [JavaScript](#tab-panel-1069)
-   [Rust](#tab-panel-1070)

```
import { register } from '@tauri-apps/plugin-global-shortcut';// when using `"withGlobalTauri": true`, you may use// const { register } = window.__TAURI__.globalShortcut;
await register('CommandOrControl+Shift+C', () => {  console.log('Shortcut triggered');});
```

src-tauri/src/lib.rs

```
pub fn run() {    tauri::Builder::default()        .setup(|app| {            #[cfg(desktop)]            {                use tauri_plugin_global_shortcut::{Code, GlobalShortcutExt, Modifiers, Shortcut, ShortcutState};
                let ctrl_n_shortcut = Shortcut::new(Some(Modifiers::CONTROL), Code::KeyN);                app.handle().plugin(                    tauri_plugin_global_shortcut::Builder::new().with_handler(move |_app, shortcut, event| {                        println!("{:?}", shortcut);                        if shortcut == &ctrl_n_shortcut {                            match event.state() {                              ShortcutState::Pressed => {                                println!("Ctrl-N Pressed!");                              }                              ShortcutState::Released => {                                println!("Ctrl-N Released!");                              }                            }                        }                    })                    .build(),                )?;
                app.global_shortcut().register(ctrl_n_shortcut)?;            }            Ok(())        })        .run(tauri::generate_context!())        .expect("error while running tauri application");}
```

## [Permissions](#permissions)

[Section titled “Permissions”](#permissions)

By default all potentially dangerous plugin commands and scopes are blocked and cannot be accessed. You must modify the permissions in your `capabilities` configuration to enable these.

See the [Capabilities Overview](/security/capabilities/) for more information and the [step by step guide](/learn/security/using-plugin-permissions/) to use plugin permissions.

src-tauri/capabilities/default.json

```
{  "$schema": "../gen/schemas/desktop-schema.json",  "identifier": "main-capability",  "description": "Capability for the main window",  "windows": ["main"],  "permissions": [    "global-shortcut:allow-is-registered",    "global-shortcut:allow-register",    "global-shortcut:allow-unregister"  ]}
```

## [Default Permission](#default-permission)

No features are enabled by default, as we believe the shortcuts can be inherently dangerous and it is application specific if specific shortcuts should be registered or unregistered.

## Permission Table

| Identifier | Description |
| --- | --- |
| 
`global-shortcut:allow-is-registered`

 | 

Enables the is\_registered command without any pre-configured scope.

 |
| 

`global-shortcut:deny-is-registered`

 | 

Denies the is\_registered command without any pre-configured scope.

 |
| 

`global-shortcut:allow-register`

 | 

Enables the register command without any pre-configured scope.

 |
| 

`global-shortcut:deny-register`

 | 

Denies the register command without any pre-configured scope.

 |
| 

`global-shortcut:allow-register-all`

 | 

Enables the register\_all command without any pre-configured scope.

 |
| 

`global-shortcut:deny-register-all`

 | 

Denies the register\_all command without any pre-configured scope.

 |
| 

`global-shortcut:allow-unregister`

 | 

Enables the unregister command without any pre-configured scope.

 |
| 

`global-shortcut:deny-unregister`

 | 

Denies the unregister command without any pre-configured scope.

 |
| 

`global-shortcut:allow-unregister-all`

 | 

Enables the unregister\_all command without any pre-configured scope.

 |
| 

`global-shortcut:deny-unregister-all`

 | 

Denies the unregister\_all command without any pre-configured scope.

 |

[Edit page](https://github.com/tauri-apps/tauri-docs/edit/v2/src/content/docs/plugin/global-shortcut.mdx)

Last updated: Feb 22, 2025

[Previous  
Geolocation](/plugin/geolocation/) [Next  
Haptics](/plugin/haptics/)

* * *

[Support on Open Collective](https://opencollective.com/tauri) [Sponsor on GitHub](https://github.com/sponsors/tauri-apps)

© 2025 Tauri Contributors. CC-BY / MIT