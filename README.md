# JDS
Julia Set renderer written in C. Completely from scratch (only dependency is `raylib` for GUI).

## Compilation
Dependencies:
- gcc
- raylib ([click here](https://github.com/raysan5/raylib/wiki/Working-on-Windows) for Windows setup)

Run `make` to compile.

# Desired Features
- [ ] Optimize zooming (drops to $< 30$ FPS when zooming)
- [ ] Arbitrary floating point precision to be able to zoom in arbitrarily much.
- [ ] Add more GUI elements
  - [X] Checkboxes
  - [X] Dropdowns (for rendering)
  - [ ] Improve on sliders and textboxes (add backspacing and cursor)
- [ ] Give user more control over the fractal polynomial
- [ ] Custom palette generation other than it being based off of red, green or blue.
- [ ] Swap between continous and discrete coloring.
- [ ] Render image formats
	- [X] PPM
	- [X] BMP
	- [ ] JPEG?
	- [ ] PNG?

# Contribution
Open a pull request.
