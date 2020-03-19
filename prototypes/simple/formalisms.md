# Formalizing the simple profile

We need sufficient formalization to allow the creation of input and validation programs. The assumption here is the [simple](https://github.com/dcmi/dcap/tree/master/prototypes/simple) prototype that we have agreed on as the basic "core".

In essence, the below is the template for the profile template. It is necessary to think "meta" here.


## General concepts

### Entity
The entity is optional because we have decided that one could have a profile with an assumed single entity. 

### Property

### Value

## Elements of the profile template

### Entity_name
cardinality: 0,n

This is what defines the entity. If this is absent then no entity is defined. There can be more than one entity in the profile, and each must have a unique entity name. Although this is called "name" it is an identifier and may be an IRI. 

### Entity_label
cardinality 0,1

This is a bit more difficult. The entity label exists *only* if there is an entity. It is optional. However, we may need a SKOS-like rule where there is one label allowed per language tag.

## Property
Cardinality: 1,n
? Change name to Property_ID?

If there are one or more entities, properties are subordinated to specific entities. Otherwise, the properties in the profile are properties of an unnamed single entity. This element identifies the property and must be unique within the profile. 

### Property_label
Cardinality: 0,1 

The same rules apply here as for the Entity_label regarding the desire to specify one per language tag.

### Mandatory
Cardinality: 0,1

A binary field*. If not coded, no rules regarding "mandatory" can be applied. This probably means that the default is "not mandatory".

* We have to decide what values are accepted for a binary field, such as "0/1" "T/F" "Yes/No"

### Repeatable
Cardinality: 0,1

A binary field. If not coded, no rules regarding repeatability can be applied. This probably means that the default is "repeatable".

### Value_type
Cardinality: 0,1

I'm not sure if this should be 1,1 or 0,1 with a default. If there is a default, it should be literal ("text" in the ContentMD examples). Although there are many possible content types, if this is left entirely open in terms of values interoperability will be harmed. We should probably develop at least one pick-list with standard value types that we think will be needed. There could be a "core" list that is a subset of a more ample list. IRIs for type standards should be encouraged.

### Value (constraint?)
Cardinality: 0,1

This is an element for additional constraints on the value beyond simple value data type. This could be: a pick list of literal values; one or more IRI stems; minimum and maximum length for strings (?); etc.

It's hard to know what to call this, but the concept is pretty clear.

### Annotation
Cardinality: 0,1

As there is one annotation column for each property in the template, this is at the property level and can provide additional information on the property or the specific value constraints. This element is wide open in terms of content. It will probably be a text field in most cases. If there is a lot to say about the property then this can be lengthy. Because we are looking at a tabular format there is a limit of one per row (which corresponds to the definition of a property and its value). As with other literal fields, we need to decide how to handle language literals.
