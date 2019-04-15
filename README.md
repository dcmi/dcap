# Dublin Core Application Profile (DCAP)

The concept of the <em>metadata application profile</em> is important for DCMI and the Dublin Core community. It has underpinned many of DCMI's development efforts in recent years. There is significant community interest in developing tools to aid in creating and documenting application profiles. There is a related interest in assuring that profiles specify validation rules for the data that they define.  

Previous work in the Dublin Core community defined a [framework](/specifications/dublin-core/singapore-framework/) for application profiles and a [constraint language](http://www.dublincore.org/specifications/dublin-core/dc-dsp/) based on the [Dublin Core Abstract Model](http://www.dublincore.org/specifications/dublin-core/abstract-model/). This current work will use some of the concepts developed previously but will not be bound to those specifications.

The profiles project potentially will include development of a revised framework to support application profiles, a revised abstract model, and an application profile constraint language.

## A Core Vocabulary for Profiles

The idea behind this project is that there is a growing need to develop vocabularies for the creation of data and metadata. The goal of interoperability among data stores encourages the reuse of existing vocabularies for this purpose, and thus to create local profiles that can be understood as widely as possible. Some developers of applications work with complex platforms for data creation and validation. Metadata is used by nearly every information technology function, from the simple web page to an institutional database, and many people involved in those functions are developing their metadata without the aid of complex and often expensive technology nor the use of professional data developers. This project aims to provide a simple core vocabulary that allows the reuse of elements defined in the public sphere of the web, and to assign basic constraints to those elements; a core vocabulary as simple to understand and use as Dublin Core, but with a different set of outcomes. 

### Project Outcomes

Outcomes in this project will be:

1. Gathering use cases and [requirements](requirements.md) for application profiles that will guide the work
1. Scoping the project to an initial set of requirments that can be addressed in a short period of time, but that can be extended in the future if desired
1. Development of a [basic vocabulary](schemaList.csv) for the creation of application profiles 
1. Alignment of the application profile vocabulary with actionable constraints, possibly using existing constraint languages
1. Development of one or more example workflows using commonly known technologies
1. Creation of reusable examples, especially of the most common functions
1. If possible, the development of a demonstrator appliction for the creation of profiles

All of this should be done keeping in mind the "core" concept that has been the philosophy behind the work of the Dublin Core Metadata Initiative. This favors simple solutions that can be used by the broadest community, and that are extensible where more detail is needed.

#### Supporting Documents 

There is an initial seeding of some documents to support these tasks. These documents are expected to be fully revised during the project.

1. A gathering of use cases for application profile constraints
1. A [requirements](requirements.md) document
1. [Design patterns](patterns.md) for basic constraints
1. Comparison of some [existing profile vocabularies](BIBFRAMEcompare.csv)
1. [Elements list](schemaList.csv), based in part on the DSP


2019-04-15: [check changes proposed in a PR](https://github.com/dcmi/dcap/pull/2/files/8ef86558a72d6d9dacb9d7d4d8268f98b372a77a)
