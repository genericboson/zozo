grammar FlatBuffers;

// --- Parser Rules ---

schema
    : include* ( 
        namespace_decl 
        | type_decl 
        | enum_decl 
        | root_decl 
        | file_extension_decl 
        | file_identifier_decl 
        | attribute_decl 
        | rpc_decl 
        | object 
    )* EOF
    ;

include
    : 'include' StringConstant ';'
    ;

namespace_decl
    : 'namespace' Ident ( '.' Ident )* ';'
    ;

attribute_decl
    : 'attribute' ( Ident | StringConstant ) ';'
    ;

type_decl
    : ( 'table' | 'struct' ) Ident metadata '{' field_decl+ '}'
    ;

enum_decl
    : ( 'enum' Ident ':' type_ | 'union' Ident ) metadata '{' commasep_enumval_decl '}'
    ;

root_decl
    : 'root_type' Ident ';'
    ;

field_decl
    : Ident ':' type_ ( '=' scalar )? metadata ';'
    ;

rpc_decl
    : 'rpc_service' Ident '{' rpc_method+ '}'
    ;

rpc_method
    : Ident '(' Ident ')' ':' Ident metadata ';'
    ;

type_
    : 'bool' | 'byte' | 'ubyte' | 'short' | 'ushort' | 'int' | 'uint' 
    | 'float' | 'long' | 'ulong' | 'double' | 'int8' | 'uint8' | 'int16' 
    | 'uint16' | 'int32' | 'uint32' | 'int64' | 'uint64' | 'float32' 
    | 'float64' | 'string' 
    | '[' type_ ']' 
    | Ident
    ;

enumval_decl
    : Ident ( '=' IntegerConstant )? metadata
    ;

metadata
    : ( '(' commasep_metadata_item ')' )?
    ;

scalar
    : BooleanConstant | IntegerConstant | FloatConstant
    ;

object
    : '{' commasep_object_item '}'
    ;

single_value
    : scalar | StringConstant
    ;

value
    : single_value 
    | object 
    | '[' commasep_value ']'
    ;

file_extension_decl
    : 'file_extension' StringConstant ';'
    ;

file_identifier_decl
    : 'file_identifier' StringConstant ';'
    ;

// --- Helper Parser Rules (Handling commasep) ---

commasep_enumval_decl
    : (enumval_decl ( ',' enumval_decl )*)?
    ;

commasep_metadata_item
    : (Ident ( ':' single_value )? ( ',' Ident ( ':' single_value )? )*)?
    ;

commasep_object_item
    : (Ident ':' value ( ',' Ident ':' value )*)?
    ;

commasep_value
    : (value ( ',' value )*)?
    ;


// --- Lexer Rules ---

BooleanConstant
    : 'true' | 'false'
    ;

Ident
    : [a-zA-Z_] [a-zA-Z0-9_]*
    ;

IntegerConstant
    : HexIntegerConstant
    | DecIntegerConstant
    ;

fragment DecIntegerConstant
    : [-+?]? [0-9]+
    ;

fragment HexIntegerConstant
    : [-+?]? '0' [xX] [0-9a-fA-F]+
    ;

FloatConstant
    : HexFloatConstant
    | DecFloatConstant
    | SpecialFloatConstant
    ;

fragment DecFloatConstant
    : [-+?]? ( ('.' [0-9]+) | ([0-9]+ '.' [0-9]*) | [0-9]+ ) ([eE] [-+?]? [0-9]+)?
    ;

fragment HexFloatConstant
    : [-+?]? '0' [xX] ( ('.' [0-9a-fA-F]+) | ([0-9a-fA-F]+ '.' [0-9a-fA-F]*) | [0-9a-fA-F]+ ) ([pP] [-+?]? [0-9]+)
    ;

fragment SpecialFloatConstant
    : [-+?]? ('nan' | 'inf' | 'infinity')
    ;

StringConstant
    : '"' ( '\\"' | . )*? '"'
    ;

WS
    : [ \t\r\n]+ -> skip
    ;