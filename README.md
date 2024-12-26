Version 1.1.0 (December 2024)

This release of Gremlin++ adds better support for traversal strategies as well as Python bindings.
These improvements are documented in the paper "Accelerating Graph Query Languages for Machine
Learning and Retrieval Augmented Generation", published at KGBigData at IEEE BigData 2024.

---------------------------------------------------------------

Version 1.0.0 (September 26, 2023)

This is a major overhaul of Gremlin++, replacing the original _Traverser_ structure
with virtual objects managed by _Maelstrom_ vectors.  Every aspect of Gremlin++
has been almost completely rewritten as a series of Maelstrom operations.
The OLAP behavior of Gremlin++ has also been standardized, and should roughly
match that of OLAP Gremlin.  Major performance and memory usage improvements are
available in this release.

---------------------------------------------------------------

Version 0.6.1 (October 11, 2022)

Gremlin++ is the core of a C++ interpreter for the Gremlin language.
It is licensed under the Apache license.  Version 0.6.1 makes some
semantic changes to accelerate traversals, most importantly the
reconceptualization of *scopes*.

Gremlin++ is a platform-independent header library.  To use Gremlin++
in your project, simply set it as an include directory.

Gremlin++ mostly follows the semantics of Gremlin, but with some
key differences (some steps are always barriers, scopes have a
different meaning, etc.)  These differences will be documented
in an upcoming paper.

--------------------------------------------------------------

Version 0.6.0 (June 11, 2022)

Gremlin++ is the core of a C++ interpreter for the Gremlin language.
It is licensed under the Apache license.  Version 0.6.0 overhauls the
performance of the interpreter and adds additional steps, primarily
to support the BitGraph project.  A 1.0 release is targeted for later
this year.

Gremlin++ is a platform-independent header library.  To use Gremlin++
in your project, simply set it as an include directory.

While the goal of Gremlin++ is to support the same semantics as
standard Gremlin, there are currently a few steps that differ,
particularly the Repeat Step.  Work is currently underway to
improve documentation of these differences.

--------------------------------------------------------------
Version 0.1.0 (October 18, 2019)

Gremlin++ is the core of a C++ interpreter for the Gremlin language.
It is licensed under the Apache license.

Currently Gremlin++ supports the following platforms:
  - Windows (Cygwin64)
  - Linux

Gremlin++ is a header library, so setting the include directory will
suffice.

