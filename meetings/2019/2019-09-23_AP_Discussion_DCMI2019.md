# Application Profiles discussion DCMI 2019

September 23, 2019
Large Lecture Room

## Some questions

- Is there a use case for a very, very simple application profile
template (e.g. list of terms and values)
- What is a preferred working format for an application profile? CSV?
JSON? YAML? XML?
- What tools are you using today to manage application profiles?
- What tools are lacking that you would like to have?

## Discussion of current initiatives
(List of known AP projects with actionable AP schemas: https://github.com/dcmi/dcap/wiki/Related-Projects)

* Dublin Core Application Profiles group
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
1. [DCAT profile "part" description vocabulary](https://w3c.github.io/dxwg/profilesont/)

### IMI DMD(Data Model Description) 

1. [About DMD](https://imi.go.jp/goi/datamodel-about/)
2. [DMD Specification](https://imi.go.jp/contents/2019/02/DMDSpecification_V301_20190228.pdf)

### Metabridge SimpleDSP (SDSP)

A simple DSP file can be created using a text editor or Microsoft Excel and upload to MetaBridge.

https://www.metabridge.jp/tutorial_dsp.html
