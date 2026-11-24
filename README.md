# Beam Deflection Calculator

A command-line program written in C that calculates how far a rectangular beam bends under a load, and checks the result against a common design limit.
My second programming project as a first-year engineering student at Dalhousie University.

## What it does
- Handles two beam types:
  - **Cantilever** (fixed at one end, load at the free end)
  - **Simply supported** (supports at both ends, load in the middle)
- Lets you choose the material: steel (E = 200 GPa), aluminum (E = 69 GPa) or wood (E = 11 GPa)
- Takes the load (N), length (m), and the beam's width and height (mm)
- Prints the second moment of area, the deflection in mm, and whether the beam passes the **L/360** deflection limit

## Formulas used
| Quantity | Formula |
|---|---|
| Second moment of area (rectangle) | I = b · h³ / 12 |
| Cantilever deflection | δ = P · L³ / (3 · E · I) |
| Simply supported deflection | δ = P · L³ / (48 · E · I) |
| Allowed deflection | L / 360 |

## How to run
Compile with gcc (`-lm` links the math library for `pow()`):

```
gcc beam_deflection.c -o beam -lm
./beam
```

Or paste the code into [onlinegdb.com](https://www.onlinegdb.com) and click Run.

## Example
Steel cantilever, 500 N load, 1 m long, 50 mm wide, 50 mm tall:

```
Second moment of area I: 5.208e-07 m^4
Deflection: 1.600 mm
Allowed deflection (L/360): 2.778 mm
Result: OK, the beam passes the L/360 check.
```

The same beam only 10 mm tall deflects 200 mm and fails the check. Because height is cubed in I, a beam 5x taller is 125x stiffer.

## Testing
I checked the program against hand calculations:

| Case | Program | Hand calculation |
|---|---|---|
| Steel cantilever, 50 x 10 mm | 200.000 mm | 200 mm |
| Steel cantilever, 50 x 50 mm | 1.600 mm | 1.6 mm |
| Steel simply supported, 50 x 10 mm | 12.500 mm | 200 / 16 = 12.5 mm |

## What I learned
- **Pointers:** my functions store their results through pointer parameters (for example `calcI(b, h, &I)`), so one function can calculate a value and hand it back to `main`.
- **Math in C:** using `pow()` from `math.h`, and writing scientific notation like `200e9` for large values.
- **Units:** converting millimetres to metres before calculating, then converting the answer back to millimetres for the output. Most bugs in engineering code come from units.
- **Input checking:** rejecting invalid menu choices and values of zero or less, which would otherwise cause a divide-by-zero.
- **Verifying results:** comparing the program's output with hand calculations before trusting it.
