# Book Club
Application profile for a simple bookclub in CSV and ShEx,with some conformant instance data

Basic idea is that in addition to basic info about books, there is some social network info about who owns them and which owners  know to each other.

## bookclubEgs.csv

This is a single file with four different variations on the book club example.

1. This is a transcription of Phil's file ap.csv, but using the current columns and column headers.  I believe that this version does not fulfill the use case because it defines a dependency between books and members; a  dataset with one book and one member that have no links between them cannot be defined with this version. 
2. This table has a row for the shape that includes cardinality on the shape; otherwise it is the same as 1. It isn't clear if this can be validated in this format using RDF validation.
3. The third table uses a "manifest" method to define book and member as shapes within the book club, with desired cardinality.
4. The fourth table is based on #1 but does not change the cardinality commitment of shapes; it does demonstrate a possibly more readable style using a row for the shape above the row(s) for properties.

## Sample instance data

### data.ttl

Original file; all books and members are connected.

### data2.ttl

Based on data.ttl, one member added that is not the object of any triples in the file.

### bookclubeg1.ttl

One book, one author, one member. 
* Book has arc to author
* Book has arc to member
* Member has arc to book

### bookclubeg2.ttl

Same as bookclubeg1.ttl except adds one member with no arc to book, and no arc from book.

### bookclubeg3.ttl

Similar to bookclubeg2.ttl, but has manifest connecting books and members; one member has no arc back to book.

