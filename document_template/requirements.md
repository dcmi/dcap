DCAP documentation requirements

Header metadata - similar to https://www.dublincore.org/specifications/dublin-core/dcmi-terms/
- Editor
- Contributors
- Latest version link (dublincore.org)
- Link to Editor's Draft (Github)
- Version date
- Status


Table of contents - similar to https://www.dublincore.org/specifications/dublin-core/dcmi-terms/

Headers (four levels deep)

Font types
- Regular
- Code (monospace)
- "Element name" or glossary entry
  - with anchor for backlinks within the document
- "Definition" 
  How it is done in https://bit.ly/respec_editors_guide

    To define a term, simple wrap it in a <dfn> element.

        <dfn>some concept</dfn>

    Then, to link to it:

        <a>some concept</a>
        or 
        [=some concept=]

Section offsets ("boxes")

1. <pre> type: for code-like examples

2. <note> type: for notes that are not to be considered part of the 
   spec, like "This section is still under development."

Tables
- Could HTML tables be used? Easier to edit than Markdown 
  tables, and more flexible w.r.t. format.

References
- Link to entry in reference section 

Maybe
- "Data include" as per respec: 
  https://github.com/w3c/respec/wiki/data-include-format

