This prototype has two variants:

* `E130.csv`, a simple [csv template](E130.csv) that is quite close to [the one discussed at the DCMI 2019 hackathon](https://github.com/dcmi/dcap/tree/master/prototypes/simpleFromHackathon)

  * Entity_name
  * Entity_label
  * Property
  * Property_label
  * Cardinality
  * Value (_not_ part of the hackathon model)
  * Value_type
  * Annotation

* `E130b.csv`, a [slightly different csv template](E130b.csv) with the following:

  * Entity_name (but no Entity_label)
  * Property
  * Property_label
  * Mand (Mand and Repeat instead of one column for Cardinality)
  * Repeat
  * Value (_not_ part of the hackathon model)
  * Value_type
  * Annotation

For each of these models, there is a Jupyter notebook with code that converts the profile to a Wikidata Entity Schema in ShEx:

* [for converting E130.csv](E130.ipynb)
* [for converting E130b.csv](E130b.ipynb)
