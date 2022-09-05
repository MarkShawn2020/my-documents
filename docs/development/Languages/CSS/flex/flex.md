## Why are there no `justify-items` and `justify-self` properties?

This is a good question not only me but also some other one do wonder like [In CSS Flexbox, why are there no "justify-items" and "justify-self" properties? - Stack Overflow](https://stackoverflow.com/questions/32551291/in-css-flexbox-why-are-there-no-justify-items-and-justify-self-properties).

It concerns with some design concept about flex, the behind consideration is far beyond my shallow thought.

Thanks to this question, as well as the answer provided by [Methods for Aligning Flex Items along the Main Axis](https://stackoverflow.com/questions/32551291/in-css-flexbox-why-are-there-no-justify-items-and-justify-self-properties#:~:text=%2B600-,Methods%20for%20Aligning%20Flex%20Items%20along%20the%20Main%20Axis,-As%20stated%20in).

Finally, what I wanna realize is an item separate from the constraint of father container <img alt="picture 6" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639923663880-12682991c6a0a6e9ad06936482ea69734a45d298a3fb84e0e900750fad22933f.png" width="720" /> , and which can be easily solved out by using the key `margin: auto`(`m-auto` in tailwindcss).

Hence, it behaves what I was expected to: <img alt="picture 7" src="https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/1639923803788-1ea69442ce26ea2fb40cf68466f9a1694727c497e9123989ad6167273eb5d0b7.png" width="720" />

Thanks!

reference:

- [A Complete Guide to Flexbox - CSS-Tricks](https://css-tricks.com/snippets/css/a-guide-to-flexbox/)
- [In CSS Flexbox, why are there no "justify-items" and "justify-self" properties? - Stack Overflow](https://stackoverflow.com/questions/32551291/in-css-flexbox-why-are-there-no-justify-items-and-justify-self-properties)
