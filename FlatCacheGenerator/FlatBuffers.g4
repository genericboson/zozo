grammar FlatBuffers;

// --- Parser Rules ---

schema returns [ FlatCacheGenerator.FlatBufferTree output ]
@init { $output = new FlatCacheGenerator.FlatBufferTree(); }
    : (includeOne = include { $output.m_includes.Add($includeOne.output); } )* ( 
        namespaceOne = namespace_decl { $output.m_namespaces.Add($namespaceOne.output); }
        | typeOne = type_decl { $output.m_types.Add($typeOne.output); }
        | enum_decl 
        | root_decl 
        | file_extension_decl 
        | file_identifier_decl 
        | attribute_decl 
        | rpc_decl 
        | object 
    )* EOF
    ;

include returns [ string output ]
@init { $output = ""; }
    : 'include' stringConstantOne = StringConstant { $output += $stringConstantOne.text; } ';'
    ;

namespace_decl returns [ string output ]
@init { $output = ""; }
    : 'namespace' identFirst = Ident { $output += $identFirst.text; } 
    ( '.' identLeft = Ident { $output += $identLeft.text; } )* ';'
    ;

attribute_decl
    : 'attribute' ( Ident | StringConstant ) ';'
    ;

type_decl returns [ FlatCacheGenerator.FlatBufferType output ]
@init { $output = new FlatCacheGenerator.FlatBufferType(); }
    : ( 'table' { $output.m_kind = FlatCacheGenerator.TypeKind.Table; } | 'struct' { $output.m_kind = FlatCacheGenerator.TypeKind.Struct; } ) 
    identOne = Ident {  $output.m_name = $identOne.text; } 
    metadata '{' ( fieldOne = field_decl { $output.m_fields.Add($fieldOne.output); } )+ '}'
    ;

enum_decl
    : ( 'enum' Ident ':' type_ | 'union' Ident ) metadata '{' commasep_enumval_decl '}'
    ;

root_decl
    : 'root_type' Ident ';'
    ;

field_decl returns [ FlatCacheGenerator.FlatBufferField output ]
@init { $output = new FlatCacheGenerator.FlatBufferField(); }
    : identOne = Ident { $output.m_name = $identOne.text; } 
    ':' 
    typeOne = type_ { $output.m_type = $typeOne.text; }
    ( '=' scalarOne = scalar { $output.m_defaultValue = $scalarOne.text; } )? 
    metadata 
    ';'
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