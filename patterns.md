# Patterns for Application Profiles and Constraints

There are three main components of the application profile: entities, properties, and values. There are five primary types of relationships between these: entity/entity relationships, property/property relationships, and entity/property relationships, property/value relationships, and value/value relationships. The relationships can be of type dependency, choice, or compound.

## Primary and Secondary Entities

For the purpose of navigation of the graph, it may be useful to define a primary entity. This entity is the starting point for subsequent operations. The identifier of the entity may be considered the identifier for the *record*. All other entities are secondary.

* Main entity (0 or 1)
* Secondary entities (0 or unlimited)

Entities can be identified using RDF types (classes) or through specific properties. 

[Note: assume that cardinality can be used throughout, even if not expressly listed.]

## Stand alone

In the Dublin Core Description Set Profile there is a quality called "stand alone" for entities which is either true or false. This determines whether an entity can exist without being the object of some other entity. "False" is is a broader requirement than a dependency because it does not state a dependency on any particular other entity in the set. "True" would allow, for example, that there could be entities for persons even though they are not associated with a specific resource. This could also be useful in allowing entities to be created at a convenient point in the workflow without triggering errors before the description is completed.

## Properties

Once the entity/property and property/property relationships are applied, there can be rules that apply to the properties and their values:
* property cardinality (if not already defined in relationship patterns)
* property value rules

## Entity/entity relationships

* Dependency: 
  * if A then B / if A then not B
  * if A then (pattern), e.g. if A then (B or C), if A then (B and (C or D)), etc.
* Choice
  * one of (list), not one of (list)

## Entity/property relationships

* Dependency
  * if E1 then P1, if E1 then (patterns of P)
* Choice
  * one of (list), not one of (list)

## Property/property relationships

* Dependency: 
  * if A then B / if A then not B
  * if A then (pattern), e.g. if A then (B or C), if A then (B and (C or D)), etc.
  * value of A / relationship / value of B (greater than, less than, equal to)
* Choice
  * one of (list), not one of (list)
* Compound
  * A and B must both be present

## Property/value relationships

There will be many tests that can be done on property values, including ones with dependencies and choices. Some are enumerated here.

| Property value | must/must not|
| -------------- | ------------ |
| value type |  |
| value list (choice) |  |
| value pattern (regex) |  |

## Value/value relationships

* greater than/less than
  * birth date must be less than death date

## Open/Closed

The overall validation may require that the rules be closed, that is, that only the entities and properties in the Application Profile may be present. The presence of other entities or properties will be flagged as an error. [There will need to be a default of either open or closed that can be over-ridden.]
