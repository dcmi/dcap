# AP Hack

Google spreadsheet: https://docs.google.com/spreadsheets/d/1Dvda7Sqa3eZdz44BWNtUWjJ2CrJeNlHvLCHbPOro7Js/edit#gid=0

Stefanie's data:

http://asch.wiki.gwdg.de/index.php/ASCH_Model

Item data: 

http://asch.wiki.gwdg.de/index.php/Item_DSP

Tom's template:

https://github.com/dcmi/dcap/tree/master/template_tom


Data so far:
<pre>
Profile
  entity1
    property: dct:title
      valueKind: xsd:literal
      minOccur: 1
      maxOccur: 1
    property: dct:date
      minOccur: 1
      maxOccur: 1
      valueKind: xsd:year
    property: dct:creator
      valueKind: entity2
  entity2
    property: foaf:name
      valueKind: xsd:literal
      minOccur : 1
      maxOccur : -1
    property: foaf:homepage
      valueKind: xsd:mbox
      minOccur : 0
      maxOccur : 1
  entity3
     property: dct:date
       minOccur: 1
       maxOccur: 1
       valueKind: xsd:monthDay
     property: xxx:yyy
       valueKind: xsd:literal
       minOccur: 1
       maxOccur: 1
     </pre>


"proof of concept" program (Ruby):
https://gist.github.com/masao/08a14cb14a005ca26e183a7b9b410f07
- Excel template to SHACL (RDF/Turtle) format.
    - Using ruby-roo library: https://github.com/roo-rb/roo

### Authoring & Publishing

https://github.com/nishad/dc2019-hack-day/
https://github.com/nishad/ap-gh-example
