
#gopt

**an extremely simple, yet powerful commandline parser for single-dash, single-char options**

## Is it threadsafe?

Yup. Unlike getopt(), it doesn't use any global variables, and doesn't force you to either.<br />

## How do I use it?

See the examples in the `examples/` directory. Sorry for not providing a better answer, but it's very straightforward. Don't worry!

## Is it binary safe? I.e., can I use it on other argv-like vectors?

As long as you *know* the size of the vector, sure! I don't use it for that, but technically,
nothing would keep you from doing it.

## Why did you release it into the public domain?

It's a trivial algorithm, too trivial to justify putting on copyrights/lefts.

## Does that mean you stopped developing `gopt`?

Nope. Of course `gopt` will be updated, should need arise. For now, `gopt` is still waiting for multi-options support... :-)

