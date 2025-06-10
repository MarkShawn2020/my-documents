tell application "pdf expert" to activate
    tell application "System Events"
    --your code

    keystroke "c" using command down

    set v to clipboard

    display dialog  v

    end tell

