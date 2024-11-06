# Fract_ol

fract_ol [-g HEIGHT WIDTH] [-t TITLE] [-f FRACTAL] [-c CONSTANT]

## Description
Displays a fractal inside a window, the view of which is controllably using WASD or arrow keys, can be zoomed using the '+' and '-' key (both numpad and not). the centerpoint can also be changed by left-clicking inside the window. if you scroll within the window, both the centerpoint and zoom will change accordingly. at any time you can press the 'r' key or the middle mouse button to reset all movements and zoom to the beginning view.

## Options

NOTE: flags are taken _in order_, if you supply them in the wrong order, the program will terminate.

	-g HEIGHT WIDTH | OPTIONAL
		defines the dimensions of the window the fractal shows up in. default x = 600, y = 600

	-t TITLE | OPTIONAL
		supplies the name for the window the fractal shows up in. default "[name of fractal]"

	-f FRACTAL | REQUIRED
		Chooses which fractal to display. if -f is not supplied, or FRACTAL invalid, program terminates.
		the following fractals are available:
			m - Mandelbrot set, defined here as iterating the formula x.n+1 = x.n^2 + c, where c == x.0
				-c	c is instead some supplied constant (or [-0.744+0.148i] if not supplied), and thus a Julia set from the parameter space of the Mandelbrot set
			b - Burning ship, defined here as iterating the formula x.n+1 = (|Re(x.n)| + |Im(x.n)|)^2 + c, where c == x.0
				-c	c is instead some supplied constant (or [-1.15+-0.4i] if not supplied) and thus a Julia set from the parameter space of the Burning ship Fractal
			l - Lyapunov fractal, defined here as iterating the formula x.n+1 = r.n*x.n*(1 - x.n), where r.n flip flops between the x && y position using the supplied sequence (or "BBBBBBAAAAAA" if not supplied) based on current iteration, and x.0 == 0.5
	
	-c CONSTANT | OPTIONAL
		Determines which constants to use for fractals that require them. should -c be supplied, it MUST be supplied after -f.
		-c takes a varying amount of parameters in a specific order depending on which fractal is specified. the specifications are as follows:
			Mandelbrot set (-f m):
				-c REAL IMAGINARY
				c = REAL + IMAGINARY * i
			Burning ship fractal (-f b)
				-c REAL IMAGINARY
				c = REAL + IMAGINARY * i
			Lyupanov fractal (-f l)
				-c SEQUENCE
				sequence = SEQUENCE
