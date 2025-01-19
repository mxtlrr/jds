# jds
Julia Set viewer written in C. Cross-platform for both Linux and Windows. No external dependencies other than:
- Graphics library (raylib)
- Arbitrary Floating-Point Precision Library (libGMP)

## Getting JDS
TODO

## Using JDS
*Not everything is listed here! Most things are self-explanatory!*

### Color data to change palette
This can either be
- 'r'
- 'g', or
- 'b'

This changes the main color palette. Selecting 'r' will make every non-black color
a shade of red. Same goes for green and blue. Default with no input is blue.

### Accuracy multiplier
The accuracy multiplier just increases the $R$ value when computing the Julia
set. As far as I can tell, this improves accuracy when zooming in / needing more
precision, which is why it's a slider.

The higher this value is, the more accurate. If you don't want to zoom in but
want to see pretty fractals, set this slider to 2.

### Complex number
This is just any complex number $a+bi$ such that $a \neq 0$ and the precision of
both $a$ and $b$ must be at most 5 digits. Meaning $0.23154+1.23914i$ is perfectly
valid, but any more frsactional digits to either would be invalid.

Additionally, there's some other stuff that hasn't been implemented for complex
numbers:
- Exponential parts (i.e. $0.7885e^{i\cdot 2\pi}$.
- Parsing of complex numbers where $b = 0$.

Everything else, like negative parts, only the imaginary parts have been
implemented.

#### The "RESET" button
This just resets both the color data input box and the complex number textbox.

### Rendering
Currently JDS supports only rendering to [PPM](https://en.wikipedia.org/wiki/Netpbm). Eventually, I'll implement BMP and JPEG/PNG. Until then, you're able to use
ffmpeg to convert from ppm to png, i.e.

```
ffmpeg -i render.ppm render.png
```


## Screenshot
![](./img/17Jan2025-JDS.png)
*JDS rendering* $f_c(z) = z^2 + 0.4+0.4i$ *with an escape value of approximately* $2\cdot 1.54$.

# What's a Julia Set?
The Julia set, $J$, is defined from a function $f_c$. Values in this set are known
to be "chaotic", meaning that a small change in any element could completely
change behaviour, i.e. escape off to infinity.

To check if $p \in J$ for any point $p$, we'd repeatedly apply $f_c$ to it $n$
times. If, at any point, $p > R$, then it is not part of the set. To give
interesting results, $R$, the escape radius can be modified. An example is the
Mandlebrot set has an $R = \pm 2$

Typically, $f_c$ looks like a quadratic, namely $f_c(z) = z^2 + c$, where $c \in
\mathbb{C}$ (additionally, $c$ is the only thing you're able to change). An 
example of $f_c$ could be $f_c(z) = z^2 + 0.45 + 0.1428i$, $i=\sqrt{-1}$.

## What about all those cool colors I see?
There are two main ways to add color to a Julia set render:
- Escape time (more rough/discrete)
- Smooth coloring (continous)

### Escape time algorithm
It's a very simple algorithm:
1. For every pixel, store the amount of iterations it takes to escape to infinity
    1. If it doesn't color it black. 
2. Look the value up in some look up table
3. Color the pixel accordingly

### Smooth coloring
TODO

# Planned Features
- [ ] Exporting to image formats
  - [X] PPM
  - [ ] BMP
  - [ ] JPEG
- [ ] Coloring
  - [ ] Smooth coloring (checkbox?)
  - [X] "discrete" coloring (non-smooth / non-continous)
- [X] Customizing parameters:
  - [X] Accuracy radius
  - [X] $c$
- [ ] Zooming in/out
