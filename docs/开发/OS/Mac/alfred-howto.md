# alfred howto

1. [create interactive shell](#create-interactive-shell)
   1. [alfred documentation](#alfred-documentation)
   2. [alfred create script](#alfred-create-script)
   3. [alfred repo](#alfred-repo)
2. [script filter](#script-filter)
3. [generate icon based on number](#generate-icon-based-on-number)

## create interactive shell

In this post [shell - Arrow key/Enter menu - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/146570/arrow-key-enter-menu/415155), there is a few of hacked scripts that allow me to design a potion list.

Among of this, the package `dialog` is a little too fancy.

### alfred documentation

- [Guides and Tutorials - Alfred Help and Support](https://www.alfredapp.com/help/guides-and-tutorials/)

### alfred create script

use `script filter`

- [Using script filters in Alfred Workflows | by Jay McCormack | Jay’s Blog | Medium](https://medium.com/jays-blog/using-script-filters-in-alfred-workflows-61432fd78e39)

### alfred repo

Strongly Recommended

- [zenorocha/alfred-workflows: A collection of Alfred 3 and 4 workflows that will rock your world](https://github.com/zenorocha/alfred-workflows)

- [hzlzh/AlfredWorkflow.com: A public Collection of Alfred Workflows.](https://github.com/hzlzh/AlfredWorkflow.com)

a python kit

- [deanishe/alfred-workflow: Full-featured library for writing Alfred 3 & 4 workflows](https://github.com/deanishe/alfred-workflow)

ref:

- [Run Script Action - Alfred Help and Support](https://www.alfredapp.com/help/workflows/actions/run-script/)

- [Permission Error on External AppleScript Script - Workflow Help & Questions - Alfred App Community Forum](https://www.alfredforum.com/topic/10631-permission-error-on-external-applescript-script/)

- ["Run script" not working for workflow - Workflow Help & Questions - Alfred App Community Forum](https://www.alfredforum.com/topic/8066-run-script-not-working-for-workflow/)

ref:

- [shell - Arrow key/Enter menu - Unix & Linux Stack Exchange](https://unix.stackexchange.com/questions/146570/arrow-key-enter-menu/415155)

## script filter

ref:

official documentation of script filter with interface

- [Script Filter Results and the XML Format — Alfred-Workflow 1.13 documentation](https://alfred-workflow.readthedocs.io/en/latest/xml_format.html)

icon interface

- [[SOLVED] Show correct icons in Script Filter - Workflow Help & Questions - Alfred App Community Forum](https://www.alfredforum.com/topic/14230-solved-show-correct-icons-in-script-filter/)

## generate icon based on number

ref:

install pillow

- [Installation — Pillow (PIL Fork) 8.4.0 documentation](https://pillow.readthedocs.io/en/stable/installation.html)

- [Create images with Python PIL and Pillow and write text on them](https://code-maven.com/create-images-with-python-pil-pillow)

use `multiline_text`

- [ImageDraw Module — Pillow (PIL Fork) 8.4.0 documentation](https://pillow.readthedocs.io/en/stable/reference/ImageDraw.html#example-draw-multiline-text)

`anchor="mm"`

- [Text anchors — Pillow (PIL Fork) 8.4.0 documentation](https://pillow.readthedocs.io/en/stable/handbook/text-anchors.html#text-anchors)
