# Dublin Core Application Profile - Model and Vocabulary

**Date:**
August 21, 2020

**Status:**
Draft - Request for Comments

**Editors:**
Karen Coyle

**Contributors**
Tom Baker, DCMI
Phil Barker
John Huck, University of Alberta
Ben Reisenberg, University of Washington


## Introduction

This is a first draft of a vocabulary for simple application profiles, as developed by the Dublin Core Metadata Initiative community. This draft is not considered to be complete although it may be sufficient for some purposes. The draft assumes that the profile defines the rules for instance data in RDF, although it may also be useful for other data formats. 

There is often confusion about the "meta" levels when talking about profiles and metadata. This vocabulary is used to define a *profile*, which is a description and set of rules that can be used to create input interfaces with rules and constraints, or validation processes that operate over existing data. The contents of the profile are not the same as the contents of instance data.

## Model

The Dublin Core application profile has a simple basic structure. 

Each profile consists of:

* Zero or more entities with
  * one or more statements
  
 Each entity in the profile is described with:
 
  * one entity identifier
  * zero or one label
  
 Each statement consists of:
  
  * one property identifier
    * zero or one label
    * zero or one boolean statement for cardinality "Mandatory"
    * zero or one boolean statement for cardinality "Repeatable"
    * zero or one value type
    * zero or one annotation
    * zero or one referral to an entity defined in the profile

Not yet included in this model, but intended to be added by the working group are the following additions to the statement:

* RDF node type
* Value constraint type
* Value constraint

## Vocabulary
### Entity
**entityID** - an identifier for the entity description in the profile. May be global or local. The entityID is required if the profile will describe a specified entity

  * cardinality: per entity - mandatory, not repeatable
  * datatype: IRI (recommended) or local identifier
  
**entityLabel**- a human-facing label for the entity that can be used in documentation and displays. See [label]

* cardinality: optional, repeatable if a language string
* datatype: xsd:string | rdf:langString

### Statement
**propertyID** - propertyID - for the RDF-based profile, the property ID must be the IRI of a vocabulary term that is defined elsewhere in RDF, RDFS, or OWL.

* cardinality: per property - mandatory, not repeatable
* datatype: IRI

**propertyLabel** - a human-facing label for the entity that can be used in documentation and displays. See [label]

* cardinality: optional, repeatable if a language string or: if there are property labels in multiple languages
* datatype: string
    
**mandatory** - is the property mandatory? a boolean (yes/no) 

* cardinality: optional, not repeatable
* datatype: Boolean

**repeatable** - is the property repeatable? a boolean (yes/no)

 * cardinality: optional, not repeatable
* datatype: Boolean

**entityShapeReference** - provides a link when the value of a property is a reference to an entity in the profile.

*cardinality: optional, not repeatable
*datatype: string, matching entityID value

**annotation** - free text area for any further information relating to the property or its usage

* cardinality: optional, not repeatable
* datatype: string

### Note on labels

Labels are short texts intended to be read by human beings, to be displayed at any point where the profile will be viewed. If the profile serves an audience with a single natural language choice, the label is a single string of one or a few words. For communities that cross languages and wish to have the displays match the language of the viewer, the RDF [langString](https://www.w3.org/TR/rdf-schema/#ch_langstring) data type is used. See the User Guide (link) for input rules.



