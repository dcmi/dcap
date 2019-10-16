# Prototypes directory

There may be some more organization of this directory and clearer naming of prototypes. 

In general, prototype should have: 
* a template file that is a template for profiles; 
* one or more instances of profiles

The prototypes may also show instance data that conforms to the profile, but we have recognized that the same template will NOT generate the profile instance and the instance data.

## Book Case in YAML

1. bookCaseEG.xls
1. bookCaseEG.ods
1. bookCaseEG.yaml

This does not (yet) have a profile template file; however, a template for this model . The YAML file makes use of entities and values that have identifiers and are each "called" from the higher entity level (e.g. description entity "calls" statement entities). The spreadsheet file (.xls or .ods) uses a separate sheet for each identified entity.

## One-sheet spreadsheet template

1. Template_for_documentation.csv
1. Template_for_instance_data.csv

A simple template similar to the profile2 template. The valueType is general (e.g. entity, literal, uri). It has a position for an entity value.

## One-sheet spreadsheet from Hackathon

1. profile2Template.csv
1. profile2Instance.csv

The template file is similar to the one-sheet one above but with some modifications made during the Hackathon. Each row represents an entity, a statement, and a value constraint. 
