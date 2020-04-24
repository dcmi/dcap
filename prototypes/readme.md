# Prototypes directory

This is a directory for experiments and prototypes of profiles. If you have profiles to submit you can email them to the list, ask on the email list to be added to the group of people who can submit files to this repo. Thank you!

There may be some more organization of this directory and clearer naming of prototypes. 

In general, prototype should have: 
* a template file that is a template for profiles; 
* one or more instances of profiles

The prototypes may also show instance data that conforms to the profile, but we have recognized that the same template will NOT generate the profile instance and the instance data.

## Minimal profile templates

### [Wikidata example](wikidata_painting)

Presented at DCMI 2019, this prototype has a simple, one "spreadsheet" csv file as input, and uses a program (available in a Jupyter notebook) to convert the file to the Wikidata Entity Schema format that is expressed in ShEx.

### [Book Case in YAML](templateYAML)

1. bookCaseEG.xls
1. bookCaseEG.ods
1. bookCaseEG.yaml

This does not (yet) have a profile template file; however, a template for this model . The YAML file makes use of entities and values that have identifiers and are each "called" from the higher entity level (e.g. description entity "calls" statement entities). The spreadsheet file (.xls or .ods) uses a separate sheet for each identified entity.

### [One-sheet spreadsheet template](bookCase1)

1. Template_for_documentation.csv
1. Template_for_instance_data.csv

A simple template similar to the profile2 template. The valueType is general (e.g. entity, literal, uri). It has a position for an entity value.

### [One-sheet spreadsheet from Hackathon](simpleFromHackathon)

1. profile2Template.csv
1. profile2Instance.csv

The template file is similar to the one-sheet one above but with some modifications made during the Hackathon. Each row represents an entity, a statement, and a value constraint. 

## Extended profile templates

### [Extended Template in JSON](extendedTemplateInJSON)

This is based on the fuller schema described in [simpleSchema.csv](/simpleSchema.csv) of Sep 2019
* [data1.json](prototypes/data1.json) (Sep 2019)
* [schema1.json](prototypes/schema1.json) (Sep 2019)
* [schema2.json](prototypes/extendedTemplateInJSON/schema2.json) (Nov 2019)
* [sinopiaProfile.json](prior_art/sinopiaProfile.json) (Apr 2019)
