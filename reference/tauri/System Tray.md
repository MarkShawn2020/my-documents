---
title: System Tray
slug: system-tray-1766149360960
source: https://v2.tauri.app/learn/system-tray/
datetime: 2025-12-19T13:02:40.959Z
---

# System Tray

Tauri allows you to create and customize a system tray for your application. This can enhance the user experience by providing quick access to common actions.

## [Configuration](#configuration)

[Section titled “Configuration”](#configuration)

First of all, update your `Cargo.toml` to include the necessary feature for the system tray.

src-tauri/Cargo.toml

```
tauri = { version = "2.0.0", features = [ "tray-icon" ] }
```

## [Usage](#usage)

[Section titled “Usage”](#usage)

The tray API is available in both JavaScript and Rust.

### [Create a Tray Icon](#create-a-tray-icon)

[Section titled “Create a Tray Icon”](#create-a-tray-icon)

-   [JavaScript](#tab-panel-918)
-   [Rust](#tab-panel-919)

Use the [`TrayIcon.new`](/reference/javascript/api/namespacetray/#new) static function to create a new tray icon:

```
import { TrayIcon } from '@tauri-apps/api/tray';
const options = {  // here you can add a tray menu, title, tooltip, event handler, etc};
const tray = await TrayIcon.new(options);
```

See [`TrayIconOptions`](/reference/javascript/api/namespacetray/#trayiconoptions) for more information on the customization options.

```
use tauri::tray::TrayIconBuilder;
tauri::Builder::default()    .setup(|app| {        let tray = TrayIconBuilder::new().build(app)?;        Ok(())    })
```

See [`TrayIconBuilder`](https://docs.rs/tauri/2.0.0/tauri/tray/struct.TrayIconBuilder.html) for more information on customization options.

### [Change the Tray Icon](#change-the-tray-icon)

[Section titled “Change the Tray Icon”](#change-the-tray-icon)

When creating the tray you can use the application icon as the tray icon:

-   [JavaScript](#tab-panel-920)
-   [Rust](#tab-panel-921)

```
import { TrayIcon } from '@tauri-apps/api/tray';import { defaultWindowIcon } from '@tauri-apps/api/app';
const options = {  icon: await defaultWindowIcon(),};
const tray = await TrayIcon.new(options);
```

```
let tray = TrayIconBuilder::new()  .icon(app.default_window_icon().unwrap().clone())  .build(app)?;
```

### [Add a Menu](#add-a-menu)

[Section titled “Add a Menu”](#add-a-menu)

To attach a menu that is displayed when the tray is clicked, you can use the `menu` option.

Note

By default the menu is displayed on both left and right clicks.

To prevent the menu from popping up on left click, call the [`menu_on_left_click(false)`](https://docs.rs/tauri/2.0.0/tauri/tray/struct.TrayIconBuilder.html#method.menu_on_left_click) Rust function or set the [`menuOnLeftClick`](/reference/javascript/api/namespacetray/#properties-1) JavaScript option to `false`.

-   [JavaScript](#tab-panel-922)
-   [Rust](#tab-panel-923)

```
import { TrayIcon } from '@tauri-apps/api/tray';import { Menu } from '@tauri-apps/api/menu';
const menu = await Menu.new({  items: [    {      id: 'quit',      text: 'Quit',    },  ],});
const options = {  menu,  menuOnLeftClick: true,};
const tray = await TrayIcon.new(options);
```

```
use tauri::{  menu::{Menu, MenuItem},  tray::TrayIconBuilder,};
let quit_i = MenuItem::with_id(app, "quit", "Quit", true, None::<&str>)?;let menu = Menu::with_items(app, &[&quit_i])?;
let tray = TrayIconBuilder::new()  .menu(&menu)  .menu_on_left_click(true)  .build(app)?;
```

#### [Listen to Menu Events](#listen-to-menu-events)

[Section titled “Listen to Menu Events”](#listen-to-menu-events)

-   [JavaScript](#tab-panel-924)
-   [Rust](#tab-panel-925)

On JavaScript you can attach a menu click event listener directly to the menu item:

-   Using a shared menu click handler
    
    ```
    import { Menu } from '@tauri-apps/api/menu';
    function onTrayMenuClick(itemId) {  // itemId === 'quit'}
    const menu = await Menu.new({  items: [    {      id: 'quit',      text: 'Quit',      action: onTrayMenuClick,    },  ],});
    ```
    
-   Using a dedicated menu click handler
    
    ```
    import { Menu } from '@tauri-apps/api/menu';
    const menu = await Menu.new({  items: [    {      id: 'quit',      text: 'Quit',      action: () => {        console.log('quit pressed');      },    },  ],});
    ```
    

Use the [`TrayIconBuilder::on_menu_event`](https://docs.rs/tauri/2.0.0/tauri/tray/struct.TrayIconBuilder.html#method.on_menu_event) method to attach a tray menu click event listener:

```
use tauri::tray::TrayIconBuilder;
TrayIconBuilder::new()  .on_menu_event(|app, event| match event.id.as_ref() {    "quit" => {      println!("quit menu item was clicked");      app.exit(0);    }    _ => {      println!("menu item {:?} not handled", event.id);    }  })
```

### [Listen to Tray Events](#listen-to-tray-events)

[Section titled “Listen to Tray Events”](#listen-to-tray-events)

The tray icon emits events for the following mouse events:

-   click: triggered when the cursor receives a single left, right or middle click, including information on whether the mouse press was released or not
-   Double click: triggered when the cursor receives a double left, right or middle click
-   Enter: triggered when the cursor enters the tray icon area
-   Move: triggered when the cursor moves around the tray icon area
-   Leave: triggered when the cursor leaves the tray icon area

Note

Linux: Unsupported. The event is not emitted even though the icon is shown and will still show a context menu on right click.

-   [JavaScript](#tab-panel-926)
-   [Rust](#tab-panel-927)

```
import { TrayIcon } from '@tauri-apps/api/tray';
const options = {  action: (event) => {    switch (event.type) {      case 'Click':        console.log(          `mouse ${event.button} button pressed, state: ${event.buttonState}`        );        break;      case 'DoubleClick':        console.log(`mouse ${event.button} button pressed`);        break;      case 'Enter':        console.log(          `mouse hovered tray at ${event.rect.position.x}, ${event.rect.position.y}`        );        break;      case 'Move':        console.log(          `mouse moved on tray at ${event.rect.position.x}, ${event.rect.position.y}`        );        break;      case 'Leave':        console.log(          `mouse left tray at ${event.rect.position.x}, ${event.rect.position.y}`        );        break;    }  },};
const tray = await TrayIcon.new(options);
```

See [`TrayIconEvent`](/reference/javascript/api/namespacetray/#trayiconevent) for more information on the event payload.

```
use tauri::{    Manager,    tray::{MouseButton, MouseButtonState, TrayIconBuilder, TrayIconEvent}};
TrayIconBuilder::new()  .on_tray_icon_event(|tray, event| match event {    TrayIconEvent::Click {      button: MouseButton::Left,      button_state: MouseButtonState::Up,      ..    } => {      println!("left click pressed and released");      // in this example, let's show and focus the main window when the tray is clicked      let app = tray.app_handle();      if let Some(window) = app.get_webview_window("main") {        let _ = window.unminimize();        let _ = window.show();        let _ = window.set_focus();      }    }    _ => {      println!("unhandled event {event:?}");    }  })
```

See [`TrayIconEvent`](https://docs.rs/tauri/2.0.0/tauri/tray/enum.TrayIconEvent.html) for more information on the event type.

For detailed information about creating menus, including menu items, submenus, and dynamic updates, see the [Window Menu](/learn/window-menu/) documentation.

[Edit page](https://github.com/tauri-apps/tauri-docs/edit/v2/src/content/docs/learn/system-tray.mdx)

Last updated: Sep 5, 2025

[Previous  
Splashscreen](/learn/splashscreen/) [Next  
Window Customization](/learn/window-customization/)

* * *

[Support on Open Collective](https://opencollective.com/tauri) [Sponsor on GitHub](https://github.com/sponsors/tauri-apps)

© 2025 Tauri Contributors. CC-BY / MIT