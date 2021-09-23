# dune-fmt

dune-fmt is an opinionated dune file formater. Fundamentally parsers [S-expression](https://en.wikipedia.org/wiki/S-expression) files and prints them with a non expected format for the Lisp classical representation.

The main reason for this creation was while reading [A New Approach to Optimal Code Formatting](https://static.googleusercontent.com/media/research.google.com/ca//pubs/archive/44667.pdf). Wanted to try out the concepts explained in the paper, but endup not following it.

## Usage

```bash
dune-fmt "dune" --write-in-place=false
```

## Example

### Input

```dune
(library
 (name Source)
 (public_name dune-fmt)
 (libraries sexplib)
 (flags
  (:standard -w +A-4-9-44-48-40-42 -warn-error -3-4-9-44-48 -safe-string)))
```

### Output

```dune
(
 library
  (name Source)
  (public_name dune-fmt)
  (libraries sexplib)
  (flags
   (
     :standard
     -w
     +A-4-9-44-48-40-42
     -warn-error
     -3-4-9-44-48
     -safe-string
   )
  )
)
```
