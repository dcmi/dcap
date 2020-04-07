# Application Profiles discussion DCMI 2019

[This file on HackMD](https://hackmd.io/2Jr3r2LySgmCVrSlC4YAmg?edit).

[This file in DCMI github](https://github.com/dcmi/dcap/blob/master/meetings/2019/2019-09-23_AP_Discussion_DCMI2019.md)

September 23, 2019
Large Lecture Room

## Some questions

- Is there a use case for a very, very simple application profile
template (e.g. list of terms and values)
- What is a preferred working format for an application profile? CSV?
JSON? YAML? XML?
- What tools are you using today to manage application profiles?
- What tools are lacking that you would like to have?
- How do Application profile relate to:
    - clinical information models
    - archetypes
    - FAIR [1](https://www.nature.com/articles/sdata201618) [2](https://www.force11.org/group/fairgroup/fairprinciples)
    

## Discussion of current initiatives
(List of known AP projects with actionable AP schemas: https://github.com/dcmi/dcap/wiki/Related-Projects)

### Dublin Core Application Profiles group
  * https://github.com/dcmi/dcap
  * Prior art: https://github.com/dcmi/dcap/tree/master/prior_art

### BIBFRAME

The BIBFRAME project has developed two online profile editors. These allow you to modify existing profiles or to create a profile "from scratch." To some extent they favor the creation of profiles of the BIBFRAME vocabulary, but might be usable for other profiles as well.

#### LoC Profile editor
  1. [Create new profile](http://bibframe.org/profile-edit/#/profile/create)
  1. [Profile list](http://bibframe.org/profile-edit/#/profile/list)

#### Stanford Profile editor (synopia)
1. [Sinopia home page](https://sinopia.io/)
2. [Sinopia profile editor](https://profile-editor.sinopia.io/#/profile/sinopia)

### Resource Description and Access (RDA)

#### [EURIG Application Profile (PDF)](https://d-nb.info/1186104252/34)

### Digital Public Library of America (DPLA)
[Metadata Application Profile - PDF](https://pro.dp.la/hubs/metadata-application-profile)

### YAMA
"Yet Another Metadata Application Profile" ([YAMA](https://nishad.github.io/yama/spec/latest/)) is a YAML-based "preprocessor to create standard metadata application profile formats". It relies on versioning to allow appropriate processing of profiles and validation of profiles. It makes use of concepts introduced in the Dublin Core Application Profiles: descriptions and statements. 

### W3C DCAT Profiles

1. [Round up of definitions of profiles](https://www.w3.org/2017/dxwg/wiki/ProfileContext)
1. [PROF profile "part" description vocabulary](https://w3c.github.io/dxwg/profiles/)

### IMI DMD(Data Model Description) 

1. [About DMD](https://imi.go.jp/goi/datamodel-about/)
2. [DMD Specification](https://imi.go.jp/contents/2019/02/DMDSpecification_V301_20190228.pdf)
3. [DMD Diagram (English)](https://cl.ly/c048cd/dmd-diagram.pdf)

### Using Wikidata as the means to build Application Profiles.
[Introductory slides](https://docs.google.com/presentation/d/1G6VDqU0BcnZ3UqYyF5oa7vJ8vI0kbKYT6ZeJOgCGvJo/edit?usp=sharing) 

references: 

* [Wikidata as an intuitive resource towards
semantic data modeling in data FAIRification](http://ceur-ws.org/Vol-2275/short1.pdf)
* [The FAIR Guiding Principles for scientific data management and stewardship](https://www.nature.com/articles/sdata201618)


### Hackday pitches
* https://hackmd.io/i7tC1gC6RXOFtzElnhlpZw?view

### Metabridge SimpleDSP (SDSP)

A simple DSP file can be created using a text editor or Microsoft Excel and upload to MetaBridge.

https://www.metabridge.jp/tutorial_dsp.html

### Minutes

Karen: We are asking people to stand up and present various developments.

[Tom Baker explains history of application profiles since 1999 in Dublin Core community.  Push circa 2006-2008 for machine-processable application profiles, but lack of tool development.  

Nishad: Metabridge project in Japan - developed CSV-based authoring environment - http://metabridge.jp [?].  Made YAML-based "preprocessor".  One of the richest data serialization formats.  Can be parsed by standard libraries. Can use templates to generate HTML pages from Github repositories.  We tried to take YAML, define very minimal language, based on [DC-DSP](http://dublincore.org/documents/dc-dsp).  YAML processable with any programming language. Our duty to help communities with simple, human-usable tools, to create profiles.

Andra: Wikibase Universal Bot: made YAML-based by Diego Chialva.

Andra: Background is biomedical informatics.  FAIR data (Findable Accessible Interoperable Reusable).  Creating FAIR application profiles (we call them semantic models.)  [Shows example:] People coming together with different data models for three days, using Wikidata as intermediate form.  Doctors and experts discuss model.  This model is passed to data stewards, who create more complex SPARQL queries.

[Question]: Domain expert = subject expert (with no background in metadata).

Andra: That is the role of the data steward. Subject experts + data stewards (who know about YAML, ShEx, etc).

Karen: One of our goals with Dublin Core work: something that is simple enough for people to work with - which will then be turned into something that is more code-like.  For very simple profiles - we have all been involved with projects that died because nobody could create a good user interface.

Karen on W3C DCAT: People cataloging datasets in European Union.  Profiles are large PDFs with alot of text and tables - not "actionable".  In addition, people creating RDF files and some are creating ShEx and SHACL schemas.  They are ending up with complex set of documents needed to support the application profile.  One element of the W3C group: attempt to create vocabulary that allows you to pull together documents needed to use an application profiles, "PROF" (profiles vocabulary).

Karen: Unlikely you will have an application profiles in one [file] - rather, vocabulary defined in one place, constraints in another. Put everything into one big file - or split into supporting documents of different functionality?

Nuno: Work at Europeana.  So I hear alot about profiles!  Has an application profile (Europeana Data Model) - several application profiles created in past.  Europeana has been based on XML profile - now wants to use RDF validation technology.

APs born out of EDM: want to find ways for people to share profiles.

Karen: Have there been efforts to validate across application profiles in Europeana?

Nuno: That is one of the goals and is why we participate in W3C groups.

Stefanie: We do not know how to get our data into Europeana.

Karen: We want to gather questions - at Hack Day.  How simple can it be and still be useful for people?  One of our first questions: is there a use case for an AP so simple that it is just a list of terms.

Karen: Would like to enable people to create a profile in a spreadsheet.  We are unsure we can get the functionality we need into something that simple.

Karen: Twenty years ago: lack of tools.  More tools today, but they tend to be based around certain formats (RDF, JSON, XML).  Everyone likes their tools.

Andra: When we meet for our three-day meetings, the most efficient tool is the whiteboard.  But what you cannot capture: whether ORs or ANDs - requires a data steward.  We draw APs in Powerpoint, but put into X.  Cytoscape.  Trying to bridge the gap.  Still a huge gap - getting whiteboard into machine-usable.

Nishad: Every tool involves skill set for tool.  Big concept of application profile.  DC-DSP tried to make a syntax.  But the main problem, from the whiteboard perspective.  We cannot visualize an application profile that easily. First question: if you try to create DPLA profile in all detail, huge.  Tool dependent on use cases and community. 

Stefanie: I have use case for really simple AP.  Colleagues coming to me when they have already started modeling.  They thought it would be simple and then they come to me and I have to start from scratch.  Idea: get them started.

Karen:
1) Simple template for subject experts.

Tom: Maybe we should be asking what APs are good for:

1) validation
2) input forms
3) display
4) consume / ingest 
5) mapping: 
6) consensus building

Karen: Making data "uniform" enough to ingest and merge. Preferences: "I prefer foaf:name".

We got alot of use cases on [Github repo](https://github.com/dcmi/dcap): see README file for link to application profile mailing list.

Karen: Look on Github for the [meeting notes]( https://github.com/dcmi/dcap/blob/master/meetings/2019/2019-09-23_AP_Discussion_DCMI2019.md)  

Hack Day:

* https://hackmd.io/i7tC1gC6RXOFtzElnhlpZw
