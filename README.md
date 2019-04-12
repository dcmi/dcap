# Dublin Core Application Profile (DCAP)

The concept of the <em>metadata application profile</em> is important for DCMI and the Dublin Core community. It has underpinned many of DCMI's development efforts in recent years - not least of which the <a href="/specifications/dublin-core/singapore-framework/">Singapore Framework</a>. There is significant community interest in developing tools to aid in creating and documenting application profiles. There is a related interest in assuring that profiles specify validation rules for the data that they define.  

Previous work in the Dublin Core community defined a [framework](/specifications/dublin-core/singapore-framework/) for application profiles and a [constraint language](http://www.dublincore.org/specifications/dublin-core/dc-dsp/) based on the [Dublin Core Abstract Model](http://www.dublincore.org/specifications/dublin-core/abstract-model/). This current work will use some of the concepts developed previously but will not be bound to those specifications.

Some key steps in the process will be:

1. Gathering use cases and [requirements](requirements.md) for application profiles that will guide the work
1. Development of a [basic vocabulary]( for the creation of application profiles 
1. Alignment of the application profile vocabulary with actionable constraints, possibly using existing constraint languages
1. If possible, development of a user interface for the creation of application profiles

 All of this should be done keeping in mind the "core" concept that has been the philosophy behind the work of the Dublin Core Metadata Initiative. This favors simple solutions that can be used by the broadest community, and that are extensible where more detail is needed.


# Proposal for a New Description Set Profile



1. The elements that would be needed to create a profile are defined in a table [here](schemaList.csv). Because RDF does not support validation of metadata schemas, it is hoped that the actionable DSP can be implemented in the [Shapes Expression](http://shex.io/) (ShEx) language.
