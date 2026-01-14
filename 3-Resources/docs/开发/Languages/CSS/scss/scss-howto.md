# scss howto

## mixin example

```scss
:before {
  position: absolute;
  display: block;
  content: ' ';
  width: 20px;
  height: 20px;
  background-image: url($logo);
  background-size: 20px 20px;
  left: 10px;
  top: 3px;
}

.warn {
  background: #de732d;
}
.warn:before {
  position: absolute;
  display: block;
  content: ' ';
  width: 20px;
  height: 20px;
  background-image: url('./svg/warn.svg');
  background-size: 20px 20px;
  left: 10px;
  top: 3px;
}

@include dir('#DE732D', './svg/warn.svg');
```
