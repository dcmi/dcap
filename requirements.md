# Requirements and motivation for a DC-AP

*(this file copied from https://github.com/kcoyle/RDF-AP/blob/master/requirements.md)*

Why? Who? What? How? Why do we want to create profiles? Who needs them? What functions do they need to provide? How will they work?

## Why?

Help someone else understand your data well enough to make use of it.  This is not unlike the more general problem with open source: you can declare your code ‘open’ and wish people ‘good luck’ or you can provide support.

* To understand variations 
  * on a standard
  * among partners
  * within a community
  * along a workflow
* To build consensus
  * by making decisions visible
  * by providing a focus for process
* To drive applications
* To drive user interfaces
  * input forms
  * displays
* To provide a framework for developing metadata templates

## Who?
* Creators: anyone providing data
* Users
  * anyone who can/is allowed to access the data
  * both people AND machines - not an either/or, but should be both (? if not both, then people?)

## What?
* To describe the basic structure of the data
  * To characterize the story that the data is designed to tell
  * To characterize the things described, and how they are described
  * To enumerate the elements that "anchor" a dataset? (E.g., the unique keys of a dbms: what has to be there to make the data useful)
* To describe the content of the data in more detail
  * subjects - properties - objects
  * things - attributes - values
* To describe the things that the metadata is "about"
  * How are those things defined?
  * How are they described?
  * How are the things related among themselves
  * What things can stand alone (i.e., be described independently of related things)?
* Properties, attributes, elements (use the one that makes most sense to you, assume they are the same)
  * What properties define the things? are required? 
  * What are the relationships between properties?
* Objects, values (same)
  * What is the value type or types for each property
  * what are/is the range of/ valid values
  * can values change? How?
* To describe relationships between values (e.g. start date <= end date)

## Administration of the profile
* Versioning
* Creator
* Rights
## How?
* markdown -> html
* wiki
* html with schema.org