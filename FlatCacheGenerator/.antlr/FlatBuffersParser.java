// Generated from d:/projects/zozo/FlatCacheGenerator/FlatBuffers.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class FlatBuffersParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, T__30=31, 
		T__31=32, T__32=33, T__33=34, T__34=35, T__35=36, T__36=37, T__37=38, 
		T__38=39, T__39=40, T__40=41, T__41=42, T__42=43, T__43=44, T__44=45, 
		BooleanConstant=46, Ident=47, IntegerConstant=48, FloatConstant=49, StringConstant=50, 
		WS=51;
	public static final int
		RULE_schema = 0, RULE_include = 1, RULE_namespace_decl = 2, RULE_type_decl = 3, 
		RULE_enum_decl = 4, RULE_root_decl = 5, RULE_file_extension_decl = 6, 
		RULE_file_identifier_decl = 7, RULE_attribute_decl = 8, RULE_rpc_decl = 9, 
		RULE_annotation_decl = 10, RULE_object = 11, RULE_commasep_enumval_decl = 12, 
		RULE_commasep_metadata_item = 13, RULE_commasep_object_item = 14, RULE_commasep_value = 15, 
		RULE_commasep_annotation_decl = 16, RULE_field_decl = 17, RULE_rpc_method = 18, 
		RULE_type_ = 19, RULE_enumval_decl = 20, RULE_metadata = 21, RULE_scalar = 22, 
		RULE_single_value = 23, RULE_value = 24;
	private static String[] makeRuleNames() {
		return new String[] {
			"schema", "include", "namespace_decl", "type_decl", "enum_decl", "root_decl", 
			"file_extension_decl", "file_identifier_decl", "attribute_decl", "rpc_decl", 
			"annotation_decl", "object", "commasep_enumval_decl", "commasep_metadata_item", 
			"commasep_object_item", "commasep_value", "commasep_annotation_decl", 
			"field_decl", "rpc_method", "type_", "enumval_decl", "metadata", "scalar", 
			"single_value", "value"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'include'", "';'", "'namespace'", "'.'", "'table'", "'struct'", 
			"'{'", "'}'", "'enum'", "':'", "'union'", "'root_type'", "'file_extension'", 
			"'file_identifier'", "'attribute'", "'rpc_service'", "'//'", "','", "'='", 
			"'('", "')'", "'bool'", "'byte'", "'ubyte'", "'short'", "'ushort'", "'int'", 
			"'uint'", "'float'", "'long'", "'ulong'", "'double'", "'int8'", "'uint8'", 
			"'int16'", "'uint16'", "'int32'", "'uint32'", "'int64'", "'uint64'", 
			"'float32'", "'float64'", "'string'", "'['", "']'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, "BooleanConstant", 
			"Ident", "IntegerConstant", "FloatConstant", "StringConstant", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "FlatBuffers.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public FlatBuffersParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SchemaContext extends ParserRuleContext {
		public FlatCacheGenerator.FlatBufferTree output;
		public IncludeContext includeOne;
		public Namespace_declContext namespaceOne;
		public Type_declContext typeOne;
		public TerminalNode EOF() { return getToken(FlatBuffersParser.EOF, 0); }
		public List<Enum_declContext> enum_decl() {
			return getRuleContexts(Enum_declContext.class);
		}
		public Enum_declContext enum_decl(int i) {
			return getRuleContext(Enum_declContext.class,i);
		}
		public List<Root_declContext> root_decl() {
			return getRuleContexts(Root_declContext.class);
		}
		public Root_declContext root_decl(int i) {
			return getRuleContext(Root_declContext.class,i);
		}
		public List<File_extension_declContext> file_extension_decl() {
			return getRuleContexts(File_extension_declContext.class);
		}
		public File_extension_declContext file_extension_decl(int i) {
			return getRuleContext(File_extension_declContext.class,i);
		}
		public List<File_identifier_declContext> file_identifier_decl() {
			return getRuleContexts(File_identifier_declContext.class);
		}
		public File_identifier_declContext file_identifier_decl(int i) {
			return getRuleContext(File_identifier_declContext.class,i);
		}
		public List<Attribute_declContext> attribute_decl() {
			return getRuleContexts(Attribute_declContext.class);
		}
		public Attribute_declContext attribute_decl(int i) {
			return getRuleContext(Attribute_declContext.class,i);
		}
		public List<Rpc_declContext> rpc_decl() {
			return getRuleContexts(Rpc_declContext.class);
		}
		public Rpc_declContext rpc_decl(int i) {
			return getRuleContext(Rpc_declContext.class,i);
		}
		public List<ObjectContext> object() {
			return getRuleContexts(ObjectContext.class);
		}
		public ObjectContext object(int i) {
			return getRuleContext(ObjectContext.class,i);
		}
		public List<IncludeContext> include() {
			return getRuleContexts(IncludeContext.class);
		}
		public IncludeContext include(int i) {
			return getRuleContext(IncludeContext.class,i);
		}
		public List<Namespace_declContext> namespace_decl() {
			return getRuleContexts(Namespace_declContext.class);
		}
		public Namespace_declContext namespace_decl(int i) {
			return getRuleContext(Namespace_declContext.class,i);
		}
		public List<Type_declContext> type_decl() {
			return getRuleContexts(Type_declContext.class);
		}
		public Type_declContext type_decl(int i) {
			return getRuleContext(Type_declContext.class,i);
		}
		public SchemaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_schema; }
	}

	public final SchemaContext schema() throws RecognitionException {
		SchemaContext _localctx = new SchemaContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_schema);
		 ((SchemaContext)_localctx).output =  new FlatCacheGenerator.FlatBufferTree(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(55);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__0) {
				{
				{
				setState(50);
				((SchemaContext)_localctx).includeOne = include();
				 _localctx.output.m_includes.Add(((SchemaContext)_localctx).includeOne.output); 
				}
				}
				setState(57);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(73);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 129768L) != 0)) {
				{
				setState(71);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case T__2:
					{
					setState(58);
					((SchemaContext)_localctx).namespaceOne = namespace_decl();
					 _localctx.output.m_namespaces.AddRange(((SchemaContext)_localctx).namespaceOne.output); 
					}
					break;
				case T__4:
				case T__5:
					{
					setState(61);
					((SchemaContext)_localctx).typeOne = type_decl();
					 _localctx.output.m_types.Add(((SchemaContext)_localctx).typeOne.output); 
					}
					break;
				case T__8:
				case T__10:
					{
					setState(64);
					enum_decl();
					}
					break;
				case T__11:
					{
					setState(65);
					root_decl();
					}
					break;
				case T__12:
					{
					setState(66);
					file_extension_decl();
					}
					break;
				case T__13:
					{
					setState(67);
					file_identifier_decl();
					}
					break;
				case T__14:
					{
					setState(68);
					attribute_decl();
					}
					break;
				case T__15:
					{
					setState(69);
					rpc_decl();
					}
					break;
				case T__6:
					{
					setState(70);
					object();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(75);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(76);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IncludeContext extends ParserRuleContext {
		public string output;
		public Token stringConstantOne;
		public TerminalNode StringConstant() { return getToken(FlatBuffersParser.StringConstant, 0); }
		public IncludeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_include; }
	}

	public final IncludeContext include() throws RecognitionException {
		IncludeContext _localctx = new IncludeContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_include);
		 ((IncludeContext)_localctx).output =  ""; 
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(78);
			match(T__0);
			setState(79);
			((IncludeContext)_localctx).stringConstantOne = match(StringConstant);
			 _localctx.output += (((IncludeContext)_localctx).stringConstantOne!=null?((IncludeContext)_localctx).stringConstantOne.getText():null); 
			setState(81);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Namespace_declContext extends ParserRuleContext {
		public List<string> output;
		public Token identFirst;
		public Token identLeft;
		public List<TerminalNode> Ident() { return getTokens(FlatBuffersParser.Ident); }
		public TerminalNode Ident(int i) {
			return getToken(FlatBuffersParser.Ident, i);
		}
		public Namespace_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespace_decl; }
	}

	public final Namespace_declContext namespace_decl() throws RecognitionException {
		Namespace_declContext _localctx = new Namespace_declContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_namespace_decl);
		 ((Namespace_declContext)_localctx).output =  new List<string>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(83);
			match(T__2);
			setState(84);
			((Namespace_declContext)_localctx).identFirst = match(Ident);
			 _localctx.output.Add((((Namespace_declContext)_localctx).identFirst!=null?((Namespace_declContext)_localctx).identFirst.getText():null)); 
			setState(91);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__3) {
				{
				{
				setState(86);
				match(T__3);
				setState(87);
				((Namespace_declContext)_localctx).identLeft = match(Ident);
				 _localctx.output.Add((((Namespace_declContext)_localctx).identLeft!=null?((Namespace_declContext)_localctx).identLeft.getText():null)); 
				}
				}
				setState(93);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(94);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_declContext extends ParserRuleContext {
		public FlatCacheGenerator.FlatBufferType output;
		public Token identOne;
		public Annotation_declContext annotationOne;
		public Field_declContext fieldOne;
		public MetadataContext metadata() {
			return getRuleContext(MetadataContext.class,0);
		}
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public Annotation_declContext annotation_decl() {
			return getRuleContext(Annotation_declContext.class,0);
		}
		public List<Field_declContext> field_decl() {
			return getRuleContexts(Field_declContext.class);
		}
		public Field_declContext field_decl(int i) {
			return getRuleContext(Field_declContext.class,i);
		}
		public Type_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_decl; }
	}

	public final Type_declContext type_decl() throws RecognitionException {
		Type_declContext _localctx = new Type_declContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_type_decl);
		 ((Type_declContext)_localctx).output =  new FlatCacheGenerator.FlatBufferType(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(100);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__4:
				{
				setState(96);
				match(T__4);
				 _localctx.output.m_kind = FlatCacheGenerator.TypeKind.Table; 
				}
				break;
			case T__5:
				{
				setState(98);
				match(T__5);
				 _localctx.output.m_kind = FlatCacheGenerator.TypeKind.Struct; 
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(102);
			((Type_declContext)_localctx).identOne = match(Ident);
			  _localctx.output.m_name = (((Type_declContext)_localctx).identOne!=null?((Type_declContext)_localctx).identOne.getText():null); 
			setState(104);
			metadata();
			setState(108);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__16) {
				{
				setState(105);
				((Type_declContext)_localctx).annotationOne = annotation_decl();
				 _localctx.output.m_annotatedAttributes = ((Type_declContext)_localctx).annotationOne.output; 
				}
			}

			setState(110);
			match(T__6);
			setState(114); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(111);
				((Type_declContext)_localctx).fieldOne = field_decl();
				 _localctx.output.m_fields.Add(((Type_declContext)_localctx).fieldOne.output); 
				}
				}
				setState(116); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==Ident );
			setState(118);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Enum_declContext extends ParserRuleContext {
		public MetadataContext metadata() {
			return getRuleContext(MetadataContext.class,0);
		}
		public Commasep_enumval_declContext commasep_enumval_decl() {
			return getRuleContext(Commasep_enumval_declContext.class,0);
		}
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public Type_Context type_() {
			return getRuleContext(Type_Context.class,0);
		}
		public Enum_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enum_decl; }
	}

	public final Enum_declContext enum_decl() throws RecognitionException {
		Enum_declContext _localctx = new Enum_declContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_enum_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(126);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__8:
				{
				setState(120);
				match(T__8);
				setState(121);
				match(Ident);
				setState(122);
				match(T__9);
				setState(123);
				type_();
				}
				break;
			case T__10:
				{
				setState(124);
				match(T__10);
				setState(125);
				match(Ident);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(128);
			metadata();
			setState(129);
			match(T__6);
			setState(130);
			commasep_enumval_decl();
			setState(131);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Root_declContext extends ParserRuleContext {
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public Root_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_root_decl; }
	}

	public final Root_declContext root_decl() throws RecognitionException {
		Root_declContext _localctx = new Root_declContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_root_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(133);
			match(T__11);
			setState(134);
			match(Ident);
			setState(135);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class File_extension_declContext extends ParserRuleContext {
		public TerminalNode StringConstant() { return getToken(FlatBuffersParser.StringConstant, 0); }
		public File_extension_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_file_extension_decl; }
	}

	public final File_extension_declContext file_extension_decl() throws RecognitionException {
		File_extension_declContext _localctx = new File_extension_declContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_file_extension_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(137);
			match(T__12);
			setState(138);
			match(StringConstant);
			setState(139);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class File_identifier_declContext extends ParserRuleContext {
		public TerminalNode StringConstant() { return getToken(FlatBuffersParser.StringConstant, 0); }
		public File_identifier_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_file_identifier_decl; }
	}

	public final File_identifier_declContext file_identifier_decl() throws RecognitionException {
		File_identifier_declContext _localctx = new File_identifier_declContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_file_identifier_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(141);
			match(T__13);
			setState(142);
			match(StringConstant);
			setState(143);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Attribute_declContext extends ParserRuleContext {
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public TerminalNode StringConstant() { return getToken(FlatBuffersParser.StringConstant, 0); }
		public Attribute_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attribute_decl; }
	}

	public final Attribute_declContext attribute_decl() throws RecognitionException {
		Attribute_declContext _localctx = new Attribute_declContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_attribute_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(145);
			match(T__14);
			setState(146);
			_la = _input.LA(1);
			if ( !(_la==Ident || _la==StringConstant) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(147);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Rpc_declContext extends ParserRuleContext {
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public List<Rpc_methodContext> rpc_method() {
			return getRuleContexts(Rpc_methodContext.class);
		}
		public Rpc_methodContext rpc_method(int i) {
			return getRuleContext(Rpc_methodContext.class,i);
		}
		public Rpc_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rpc_decl; }
	}

	public final Rpc_declContext rpc_decl() throws RecognitionException {
		Rpc_declContext _localctx = new Rpc_declContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_rpc_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(149);
			match(T__15);
			setState(150);
			match(Ident);
			setState(151);
			match(T__6);
			setState(153); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(152);
				rpc_method();
				}
				}
				setState(155); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==Ident );
			setState(157);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Annotation_declContext extends ParserRuleContext {
		public List<string> output;
		public Commasep_annotation_declContext commasepOne;
		public Commasep_annotation_declContext commasep_annotation_decl() {
			return getRuleContext(Commasep_annotation_declContext.class,0);
		}
		public Annotation_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotation_decl; }
	}

	public final Annotation_declContext annotation_decl() throws RecognitionException {
		Annotation_declContext _localctx = new Annotation_declContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_annotation_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(159);
			match(T__16);
			setState(160);
			((Annotation_declContext)_localctx).commasepOne = commasep_annotation_decl();
			 ((Annotation_declContext)_localctx).output =  ((Annotation_declContext)_localctx).commasepOne.output; 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ObjectContext extends ParserRuleContext {
		public Commasep_object_itemContext commasep_object_item() {
			return getRuleContext(Commasep_object_itemContext.class,0);
		}
		public ObjectContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_object; }
	}

	public final ObjectContext object() throws RecognitionException {
		ObjectContext _localctx = new ObjectContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_object);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(163);
			match(T__6);
			setState(164);
			commasep_object_item();
			setState(165);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Commasep_enumval_declContext extends ParserRuleContext {
		public List<Enumval_declContext> enumval_decl() {
			return getRuleContexts(Enumval_declContext.class);
		}
		public Enumval_declContext enumval_decl(int i) {
			return getRuleContext(Enumval_declContext.class,i);
		}
		public Commasep_enumval_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_commasep_enumval_decl; }
	}

	public final Commasep_enumval_declContext commasep_enumval_decl() throws RecognitionException {
		Commasep_enumval_declContext _localctx = new Commasep_enumval_declContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_commasep_enumval_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(175);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Ident) {
				{
				setState(167);
				enumval_decl();
				setState(172);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__17) {
					{
					{
					setState(168);
					match(T__17);
					setState(169);
					enumval_decl();
					}
					}
					setState(174);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Commasep_metadata_itemContext extends ParserRuleContext {
		public List<TerminalNode> Ident() { return getTokens(FlatBuffersParser.Ident); }
		public TerminalNode Ident(int i) {
			return getToken(FlatBuffersParser.Ident, i);
		}
		public List<Single_valueContext> single_value() {
			return getRuleContexts(Single_valueContext.class);
		}
		public Single_valueContext single_value(int i) {
			return getRuleContext(Single_valueContext.class,i);
		}
		public Commasep_metadata_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_commasep_metadata_item; }
	}

	public final Commasep_metadata_itemContext commasep_metadata_item() throws RecognitionException {
		Commasep_metadata_itemContext _localctx = new Commasep_metadata_itemContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_commasep_metadata_item);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(193);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Ident) {
				{
				setState(177);
				match(Ident);
				setState(180);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__9) {
					{
					setState(178);
					match(T__9);
					setState(179);
					single_value();
					}
				}

				setState(190);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__17) {
					{
					{
					setState(182);
					match(T__17);
					setState(183);
					match(Ident);
					setState(186);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==T__9) {
						{
						setState(184);
						match(T__9);
						setState(185);
						single_value();
						}
					}

					}
					}
					setState(192);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Commasep_object_itemContext extends ParserRuleContext {
		public List<TerminalNode> Ident() { return getTokens(FlatBuffersParser.Ident); }
		public TerminalNode Ident(int i) {
			return getToken(FlatBuffersParser.Ident, i);
		}
		public List<ValueContext> value() {
			return getRuleContexts(ValueContext.class);
		}
		public ValueContext value(int i) {
			return getRuleContext(ValueContext.class,i);
		}
		public Commasep_object_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_commasep_object_item; }
	}

	public final Commasep_object_itemContext commasep_object_item() throws RecognitionException {
		Commasep_object_itemContext _localctx = new Commasep_object_itemContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_commasep_object_item);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(207);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Ident) {
				{
				setState(195);
				match(Ident);
				setState(196);
				match(T__9);
				setState(197);
				value();
				setState(204);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__17) {
					{
					{
					setState(198);
					match(T__17);
					setState(199);
					match(Ident);
					setState(200);
					match(T__9);
					setState(201);
					value();
					}
					}
					setState(206);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Commasep_valueContext extends ParserRuleContext {
		public List<ValueContext> value() {
			return getRuleContexts(ValueContext.class);
		}
		public ValueContext value(int i) {
			return getRuleContext(ValueContext.class,i);
		}
		public Commasep_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_commasep_value; }
	}

	public final Commasep_valueContext commasep_value() throws RecognitionException {
		Commasep_valueContext _localctx = new Commasep_valueContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_commasep_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(217);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2058285767196800L) != 0)) {
				{
				setState(209);
				value();
				setState(214);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__17) {
					{
					{
					setState(210);
					match(T__17);
					setState(211);
					value();
					}
					}
					setState(216);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Commasep_annotation_declContext extends ParserRuleContext {
		public List<string> output;
		public Token identFirst;
		public Token identOther;
		public List<TerminalNode> Ident() { return getTokens(FlatBuffersParser.Ident); }
		public TerminalNode Ident(int i) {
			return getToken(FlatBuffersParser.Ident, i);
		}
		public Commasep_annotation_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_commasep_annotation_decl; }
	}

	public final Commasep_annotation_declContext commasep_annotation_decl() throws RecognitionException {
		Commasep_annotation_declContext _localctx = new Commasep_annotation_declContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_commasep_annotation_decl);
		 ((Commasep_annotation_declContext)_localctx).output =  new List<string>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(229);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
			case 1:
				{
				setState(219);
				((Commasep_annotation_declContext)_localctx).identFirst = match(Ident);
				 _localctx.output.Add( (((Commasep_annotation_declContext)_localctx).identFirst!=null?((Commasep_annotation_declContext)_localctx).identFirst.getText():null) ); 
				setState(226);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__17) {
					{
					{
					setState(221);
					match(T__17);
					setState(222);
					((Commasep_annotation_declContext)_localctx).identOther = match(Ident);
					 _localctx.output.Add( (((Commasep_annotation_declContext)_localctx).identOther!=null?((Commasep_annotation_declContext)_localctx).identOther.getText():null) ); 
					}
					}
					setState(228);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Field_declContext extends ParserRuleContext {
		public FlatCacheGenerator.FlatBufferField output;
		public Token identOne;
		public Type_Context typeOne;
		public ScalarContext scalarOne;
		public Annotation_declContext annotationOne;
		public MetadataContext metadata() {
			return getRuleContext(MetadataContext.class,0);
		}
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public Type_Context type_() {
			return getRuleContext(Type_Context.class,0);
		}
		public ScalarContext scalar() {
			return getRuleContext(ScalarContext.class,0);
		}
		public Annotation_declContext annotation_decl() {
			return getRuleContext(Annotation_declContext.class,0);
		}
		public Field_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_field_decl; }
	}

	public final Field_declContext field_decl() throws RecognitionException {
		Field_declContext _localctx = new Field_declContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_field_decl);
		 ((Field_declContext)_localctx).output =  new FlatCacheGenerator.FlatBufferField(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(231);
			((Field_declContext)_localctx).identOne = match(Ident);
			 _localctx.output.m_name = (((Field_declContext)_localctx).identOne!=null?((Field_declContext)_localctx).identOne.getText():null); 
			setState(233);
			match(T__9);
			setState(234);
			((Field_declContext)_localctx).typeOne = type_();
			 _localctx.output.m_type = (((Field_declContext)_localctx).typeOne!=null?_input.getText(((Field_declContext)_localctx).typeOne.start,((Field_declContext)_localctx).typeOne.stop):null); 
			setState(240);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__18) {
				{
				setState(236);
				match(T__18);
				setState(237);
				((Field_declContext)_localctx).scalarOne = scalar();
				 _localctx.output.m_defaultValue = (((Field_declContext)_localctx).scalarOne!=null?_input.getText(((Field_declContext)_localctx).scalarOne.start,((Field_declContext)_localctx).scalarOne.stop):null); 
				}
			}

			setState(242);
			metadata();
			setState(243);
			match(T__1);
			setState(247);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__16) {
				{
				setState(244);
				((Field_declContext)_localctx).annotationOne = annotation_decl();
				 _localctx.output.m_annotatedAttributes = ((Field_declContext)_localctx).annotationOne.output; 
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Rpc_methodContext extends ParserRuleContext {
		public List<TerminalNode> Ident() { return getTokens(FlatBuffersParser.Ident); }
		public TerminalNode Ident(int i) {
			return getToken(FlatBuffersParser.Ident, i);
		}
		public MetadataContext metadata() {
			return getRuleContext(MetadataContext.class,0);
		}
		public Rpc_methodContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rpc_method; }
	}

	public final Rpc_methodContext rpc_method() throws RecognitionException {
		Rpc_methodContext _localctx = new Rpc_methodContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_rpc_method);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(249);
			match(Ident);
			setState(250);
			match(T__19);
			setState(251);
			match(Ident);
			setState(252);
			match(T__20);
			setState(253);
			match(T__9);
			setState(254);
			match(Ident);
			setState(255);
			metadata();
			setState(256);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Type_Context extends ParserRuleContext {
		public Type_Context type_() {
			return getRuleContext(Type_Context.class,0);
		}
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public Type_Context(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_; }
	}

	public final Type_Context type_() throws RecognitionException {
		Type_Context _localctx = new Type_Context(_ctx, getState());
		enterRule(_localctx, 38, RULE_type_);
		try {
			setState(285);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__21:
				enterOuterAlt(_localctx, 1);
				{
				setState(258);
				match(T__21);
				}
				break;
			case T__22:
				enterOuterAlt(_localctx, 2);
				{
				setState(259);
				match(T__22);
				}
				break;
			case T__23:
				enterOuterAlt(_localctx, 3);
				{
				setState(260);
				match(T__23);
				}
				break;
			case T__24:
				enterOuterAlt(_localctx, 4);
				{
				setState(261);
				match(T__24);
				}
				break;
			case T__25:
				enterOuterAlt(_localctx, 5);
				{
				setState(262);
				match(T__25);
				}
				break;
			case T__26:
				enterOuterAlt(_localctx, 6);
				{
				setState(263);
				match(T__26);
				}
				break;
			case T__27:
				enterOuterAlt(_localctx, 7);
				{
				setState(264);
				match(T__27);
				}
				break;
			case T__28:
				enterOuterAlt(_localctx, 8);
				{
				setState(265);
				match(T__28);
				}
				break;
			case T__29:
				enterOuterAlt(_localctx, 9);
				{
				setState(266);
				match(T__29);
				}
				break;
			case T__30:
				enterOuterAlt(_localctx, 10);
				{
				setState(267);
				match(T__30);
				}
				break;
			case T__31:
				enterOuterAlt(_localctx, 11);
				{
				setState(268);
				match(T__31);
				}
				break;
			case T__32:
				enterOuterAlt(_localctx, 12);
				{
				setState(269);
				match(T__32);
				}
				break;
			case T__33:
				enterOuterAlt(_localctx, 13);
				{
				setState(270);
				match(T__33);
				}
				break;
			case T__34:
				enterOuterAlt(_localctx, 14);
				{
				setState(271);
				match(T__34);
				}
				break;
			case T__35:
				enterOuterAlt(_localctx, 15);
				{
				setState(272);
				match(T__35);
				}
				break;
			case T__36:
				enterOuterAlt(_localctx, 16);
				{
				setState(273);
				match(T__36);
				}
				break;
			case T__37:
				enterOuterAlt(_localctx, 17);
				{
				setState(274);
				match(T__37);
				}
				break;
			case T__38:
				enterOuterAlt(_localctx, 18);
				{
				setState(275);
				match(T__38);
				}
				break;
			case T__39:
				enterOuterAlt(_localctx, 19);
				{
				setState(276);
				match(T__39);
				}
				break;
			case T__40:
				enterOuterAlt(_localctx, 20);
				{
				setState(277);
				match(T__40);
				}
				break;
			case T__41:
				enterOuterAlt(_localctx, 21);
				{
				setState(278);
				match(T__41);
				}
				break;
			case T__42:
				enterOuterAlt(_localctx, 22);
				{
				setState(279);
				match(T__42);
				}
				break;
			case T__43:
				enterOuterAlt(_localctx, 23);
				{
				setState(280);
				match(T__43);
				setState(281);
				type_();
				setState(282);
				match(T__44);
				}
				break;
			case Ident:
				enterOuterAlt(_localctx, 24);
				{
				setState(284);
				match(Ident);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Enumval_declContext extends ParserRuleContext {
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public MetadataContext metadata() {
			return getRuleContext(MetadataContext.class,0);
		}
		public TerminalNode IntegerConstant() { return getToken(FlatBuffersParser.IntegerConstant, 0); }
		public Enumval_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enumval_decl; }
	}

	public final Enumval_declContext enumval_decl() throws RecognitionException {
		Enumval_declContext _localctx = new Enumval_declContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_enumval_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(287);
			match(Ident);
			setState(290);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__18) {
				{
				setState(288);
				match(T__18);
				setState(289);
				match(IntegerConstant);
				}
			}

			setState(292);
			metadata();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MetadataContext extends ParserRuleContext {
		public Commasep_metadata_itemContext commasep_metadata_item() {
			return getRuleContext(Commasep_metadata_itemContext.class,0);
		}
		public MetadataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata; }
	}

	public final MetadataContext metadata() throws RecognitionException {
		MetadataContext _localctx = new MetadataContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_metadata);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(298);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__19) {
				{
				setState(294);
				match(T__19);
				setState(295);
				commasep_metadata_item();
				setState(296);
				match(T__20);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ScalarContext extends ParserRuleContext {
		public TerminalNode BooleanConstant() { return getToken(FlatBuffersParser.BooleanConstant, 0); }
		public TerminalNode IntegerConstant() { return getToken(FlatBuffersParser.IntegerConstant, 0); }
		public TerminalNode FloatConstant() { return getToken(FlatBuffersParser.FloatConstant, 0); }
		public ScalarContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_scalar; }
	}

	public final ScalarContext scalar() throws RecognitionException {
		ScalarContext _localctx = new ScalarContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_scalar);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(300);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 914793674309632L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Single_valueContext extends ParserRuleContext {
		public ScalarContext scalar() {
			return getRuleContext(ScalarContext.class,0);
		}
		public TerminalNode StringConstant() { return getToken(FlatBuffersParser.StringConstant, 0); }
		public Single_valueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_single_value; }
	}

	public final Single_valueContext single_value() throws RecognitionException {
		Single_valueContext _localctx = new Single_valueContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_single_value);
		try {
			setState(304);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case BooleanConstant:
			case IntegerConstant:
			case FloatConstant:
				enterOuterAlt(_localctx, 1);
				{
				setState(302);
				scalar();
				}
				break;
			case StringConstant:
				enterOuterAlt(_localctx, 2);
				{
				setState(303);
				match(StringConstant);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ValueContext extends ParserRuleContext {
		public Single_valueContext single_value() {
			return getRuleContext(Single_valueContext.class,0);
		}
		public ObjectContext object() {
			return getRuleContext(ObjectContext.class,0);
		}
		public Commasep_valueContext commasep_value() {
			return getRuleContext(Commasep_valueContext.class,0);
		}
		public ValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value; }
	}

	public final ValueContext value() throws RecognitionException {
		ValueContext _localctx = new ValueContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_value);
		try {
			setState(312);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case BooleanConstant:
			case IntegerConstant:
			case FloatConstant:
			case StringConstant:
				enterOuterAlt(_localctx, 1);
				{
				setState(306);
				single_value();
				}
				break;
			case T__6:
				enterOuterAlt(_localctx, 2);
				{
				setState(307);
				object();
				}
				break;
			case T__43:
				enterOuterAlt(_localctx, 3);
				{
				setState(308);
				match(T__43);
				setState(309);
				commasep_value();
				setState(310);
				match(T__44);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u00013\u013b\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0005\u00006\b\u0000\n\u0000\f\u0000"+
		"9\t\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0005\u0000H\b\u0000\n\u0000\f\u0000K\t\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0005\u0002Z\b\u0002\n\u0002\f\u0002]\t\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0003\u0003"+
		"e\b\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0003\u0003m\b\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0004\u0003s\b\u0003\u000b\u0003\f\u0003t\u0001\u0003\u0001"+
		"\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0003\u0004\u007f\b\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0004\t\u009a\b\t\u000b\t\f\t\u009b\u0001\t\u0001\t\u0001\n"+
		"\u0001\n\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\f\u0001\f\u0001\f\u0005\f\u00ab\b\f\n\f\f\f\u00ae\t\f\u0003\f\u00b0"+
		"\b\f\u0001\r\u0001\r\u0001\r\u0003\r\u00b5\b\r\u0001\r\u0001\r\u0001\r"+
		"\u0001\r\u0003\r\u00bb\b\r\u0005\r\u00bd\b\r\n\r\f\r\u00c0\t\r\u0003\r"+
		"\u00c2\b\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000e\u0001\u000e\u0005\u000e\u00cb\b\u000e\n\u000e\f\u000e\u00ce"+
		"\t\u000e\u0003\u000e\u00d0\b\u000e\u0001\u000f\u0001\u000f\u0001\u000f"+
		"\u0005\u000f\u00d5\b\u000f\n\u000f\f\u000f\u00d8\t\u000f\u0003\u000f\u00da"+
		"\b\u000f\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0005"+
		"\u0010\u00e1\b\u0010\n\u0010\f\u0010\u00e4\t\u0010\u0003\u0010\u00e6\b"+
		"\u0010\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0003\u0011\u00f1\b\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0003\u0011\u00f8"+
		"\b\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0003\u0013\u011e\b\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0003"+
		"\u0014\u0123\b\u0014\u0001\u0014\u0001\u0014\u0001\u0015\u0001\u0015\u0001"+
		"\u0015\u0001\u0015\u0003\u0015\u012b\b\u0015\u0001\u0016\u0001\u0016\u0001"+
		"\u0017\u0001\u0017\u0003\u0017\u0131\b\u0017\u0001\u0018\u0001\u0018\u0001"+
		"\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0003\u0018\u0139\b\u0018\u0001"+
		"\u0018\u0000\u0000\u0019\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012"+
		"\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,.0\u0000\u0002\u0002\u0000"+
		"//22\u0002\u0000..01\u015b\u00007\u0001\u0000\u0000\u0000\u0002N\u0001"+
		"\u0000\u0000\u0000\u0004S\u0001\u0000\u0000\u0000\u0006d\u0001\u0000\u0000"+
		"\u0000\b~\u0001\u0000\u0000\u0000\n\u0085\u0001\u0000\u0000\u0000\f\u0089"+
		"\u0001\u0000\u0000\u0000\u000e\u008d\u0001\u0000\u0000\u0000\u0010\u0091"+
		"\u0001\u0000\u0000\u0000\u0012\u0095\u0001\u0000\u0000\u0000\u0014\u009f"+
		"\u0001\u0000\u0000\u0000\u0016\u00a3\u0001\u0000\u0000\u0000\u0018\u00af"+
		"\u0001\u0000\u0000\u0000\u001a\u00c1\u0001\u0000\u0000\u0000\u001c\u00cf"+
		"\u0001\u0000\u0000\u0000\u001e\u00d9\u0001\u0000\u0000\u0000 \u00e5\u0001"+
		"\u0000\u0000\u0000\"\u00e7\u0001\u0000\u0000\u0000$\u00f9\u0001\u0000"+
		"\u0000\u0000&\u011d\u0001\u0000\u0000\u0000(\u011f\u0001\u0000\u0000\u0000"+
		"*\u012a\u0001\u0000\u0000\u0000,\u012c\u0001\u0000\u0000\u0000.\u0130"+
		"\u0001\u0000\u0000\u00000\u0138\u0001\u0000\u0000\u000023\u0003\u0002"+
		"\u0001\u000034\u0006\u0000\uffff\uffff\u000046\u0001\u0000\u0000\u0000"+
		"52\u0001\u0000\u0000\u000069\u0001\u0000\u0000\u000075\u0001\u0000\u0000"+
		"\u000078\u0001\u0000\u0000\u00008I\u0001\u0000\u0000\u000097\u0001\u0000"+
		"\u0000\u0000:;\u0003\u0004\u0002\u0000;<\u0006\u0000\uffff\uffff\u0000"+
		"<H\u0001\u0000\u0000\u0000=>\u0003\u0006\u0003\u0000>?\u0006\u0000\uffff"+
		"\uffff\u0000?H\u0001\u0000\u0000\u0000@H\u0003\b\u0004\u0000AH\u0003\n"+
		"\u0005\u0000BH\u0003\f\u0006\u0000CH\u0003\u000e\u0007\u0000DH\u0003\u0010"+
		"\b\u0000EH\u0003\u0012\t\u0000FH\u0003\u0016\u000b\u0000G:\u0001\u0000"+
		"\u0000\u0000G=\u0001\u0000\u0000\u0000G@\u0001\u0000\u0000\u0000GA\u0001"+
		"\u0000\u0000\u0000GB\u0001\u0000\u0000\u0000GC\u0001\u0000\u0000\u0000"+
		"GD\u0001\u0000\u0000\u0000GE\u0001\u0000\u0000\u0000GF\u0001\u0000\u0000"+
		"\u0000HK\u0001\u0000\u0000\u0000IG\u0001\u0000\u0000\u0000IJ\u0001\u0000"+
		"\u0000\u0000JL\u0001\u0000\u0000\u0000KI\u0001\u0000\u0000\u0000LM\u0005"+
		"\u0000\u0000\u0001M\u0001\u0001\u0000\u0000\u0000NO\u0005\u0001\u0000"+
		"\u0000OP\u00052\u0000\u0000PQ\u0006\u0001\uffff\uffff\u0000QR\u0005\u0002"+
		"\u0000\u0000R\u0003\u0001\u0000\u0000\u0000ST\u0005\u0003\u0000\u0000"+
		"TU\u0005/\u0000\u0000U[\u0006\u0002\uffff\uffff\u0000VW\u0005\u0004\u0000"+
		"\u0000WX\u0005/\u0000\u0000XZ\u0006\u0002\uffff\uffff\u0000YV\u0001\u0000"+
		"\u0000\u0000Z]\u0001\u0000\u0000\u0000[Y\u0001\u0000\u0000\u0000[\\\u0001"+
		"\u0000\u0000\u0000\\^\u0001\u0000\u0000\u0000][\u0001\u0000\u0000\u0000"+
		"^_\u0005\u0002\u0000\u0000_\u0005\u0001\u0000\u0000\u0000`a\u0005\u0005"+
		"\u0000\u0000ae\u0006\u0003\uffff\uffff\u0000bc\u0005\u0006\u0000\u0000"+
		"ce\u0006\u0003\uffff\uffff\u0000d`\u0001\u0000\u0000\u0000db\u0001\u0000"+
		"\u0000\u0000ef\u0001\u0000\u0000\u0000fg\u0005/\u0000\u0000gh\u0006\u0003"+
		"\uffff\uffff\u0000hl\u0003*\u0015\u0000ij\u0003\u0014\n\u0000jk\u0006"+
		"\u0003\uffff\uffff\u0000km\u0001\u0000\u0000\u0000li\u0001\u0000\u0000"+
		"\u0000lm\u0001\u0000\u0000\u0000mn\u0001\u0000\u0000\u0000nr\u0005\u0007"+
		"\u0000\u0000op\u0003\"\u0011\u0000pq\u0006\u0003\uffff\uffff\u0000qs\u0001"+
		"\u0000\u0000\u0000ro\u0001\u0000\u0000\u0000st\u0001\u0000\u0000\u0000"+
		"tr\u0001\u0000\u0000\u0000tu\u0001\u0000\u0000\u0000uv\u0001\u0000\u0000"+
		"\u0000vw\u0005\b\u0000\u0000w\u0007\u0001\u0000\u0000\u0000xy\u0005\t"+
		"\u0000\u0000yz\u0005/\u0000\u0000z{\u0005\n\u0000\u0000{\u007f\u0003&"+
		"\u0013\u0000|}\u0005\u000b\u0000\u0000}\u007f\u0005/\u0000\u0000~x\u0001"+
		"\u0000\u0000\u0000~|\u0001\u0000\u0000\u0000\u007f\u0080\u0001\u0000\u0000"+
		"\u0000\u0080\u0081\u0003*\u0015\u0000\u0081\u0082\u0005\u0007\u0000\u0000"+
		"\u0082\u0083\u0003\u0018\f\u0000\u0083\u0084\u0005\b\u0000\u0000\u0084"+
		"\t\u0001\u0000\u0000\u0000\u0085\u0086\u0005\f\u0000\u0000\u0086\u0087"+
		"\u0005/\u0000\u0000\u0087\u0088\u0005\u0002\u0000\u0000\u0088\u000b\u0001"+
		"\u0000\u0000\u0000\u0089\u008a\u0005\r\u0000\u0000\u008a\u008b\u00052"+
		"\u0000\u0000\u008b\u008c\u0005\u0002\u0000\u0000\u008c\r\u0001\u0000\u0000"+
		"\u0000\u008d\u008e\u0005\u000e\u0000\u0000\u008e\u008f\u00052\u0000\u0000"+
		"\u008f\u0090\u0005\u0002\u0000\u0000\u0090\u000f\u0001\u0000\u0000\u0000"+
		"\u0091\u0092\u0005\u000f\u0000\u0000\u0092\u0093\u0007\u0000\u0000\u0000"+
		"\u0093\u0094\u0005\u0002\u0000\u0000\u0094\u0011\u0001\u0000\u0000\u0000"+
		"\u0095\u0096\u0005\u0010\u0000\u0000\u0096\u0097\u0005/\u0000\u0000\u0097"+
		"\u0099\u0005\u0007\u0000\u0000\u0098\u009a\u0003$\u0012\u0000\u0099\u0098"+
		"\u0001\u0000\u0000\u0000\u009a\u009b\u0001\u0000\u0000\u0000\u009b\u0099"+
		"\u0001\u0000\u0000\u0000\u009b\u009c\u0001\u0000\u0000\u0000\u009c\u009d"+
		"\u0001\u0000\u0000\u0000\u009d\u009e\u0005\b\u0000\u0000\u009e\u0013\u0001"+
		"\u0000\u0000\u0000\u009f\u00a0\u0005\u0011\u0000\u0000\u00a0\u00a1\u0003"+
		" \u0010\u0000\u00a1\u00a2\u0006\n\uffff\uffff\u0000\u00a2\u0015\u0001"+
		"\u0000\u0000\u0000\u00a3\u00a4\u0005\u0007\u0000\u0000\u00a4\u00a5\u0003"+
		"\u001c\u000e\u0000\u00a5\u00a6\u0005\b\u0000\u0000\u00a6\u0017\u0001\u0000"+
		"\u0000\u0000\u00a7\u00ac\u0003(\u0014\u0000\u00a8\u00a9\u0005\u0012\u0000"+
		"\u0000\u00a9\u00ab\u0003(\u0014\u0000\u00aa\u00a8\u0001\u0000\u0000\u0000"+
		"\u00ab\u00ae\u0001\u0000\u0000\u0000\u00ac\u00aa\u0001\u0000\u0000\u0000"+
		"\u00ac\u00ad\u0001\u0000\u0000\u0000\u00ad\u00b0\u0001\u0000\u0000\u0000"+
		"\u00ae\u00ac\u0001\u0000\u0000\u0000\u00af\u00a7\u0001\u0000\u0000\u0000"+
		"\u00af\u00b0\u0001\u0000\u0000\u0000\u00b0\u0019\u0001\u0000\u0000\u0000"+
		"\u00b1\u00b4\u0005/\u0000\u0000\u00b2\u00b3\u0005\n\u0000\u0000\u00b3"+
		"\u00b5\u0003.\u0017\u0000\u00b4\u00b2\u0001\u0000\u0000\u0000\u00b4\u00b5"+
		"\u0001\u0000\u0000\u0000\u00b5\u00be\u0001\u0000\u0000\u0000\u00b6\u00b7"+
		"\u0005\u0012\u0000\u0000\u00b7\u00ba\u0005/\u0000\u0000\u00b8\u00b9\u0005"+
		"\n\u0000\u0000\u00b9\u00bb\u0003.\u0017\u0000\u00ba\u00b8\u0001\u0000"+
		"\u0000\u0000\u00ba\u00bb\u0001\u0000\u0000\u0000\u00bb\u00bd\u0001\u0000"+
		"\u0000\u0000\u00bc\u00b6\u0001\u0000\u0000\u0000\u00bd\u00c0\u0001\u0000"+
		"\u0000\u0000\u00be\u00bc\u0001\u0000\u0000\u0000\u00be\u00bf\u0001\u0000"+
		"\u0000\u0000\u00bf\u00c2\u0001\u0000\u0000\u0000\u00c0\u00be\u0001\u0000"+
		"\u0000\u0000\u00c1\u00b1\u0001\u0000\u0000\u0000\u00c1\u00c2\u0001\u0000"+
		"\u0000\u0000\u00c2\u001b\u0001\u0000\u0000\u0000\u00c3\u00c4\u0005/\u0000"+
		"\u0000\u00c4\u00c5\u0005\n\u0000\u0000\u00c5\u00cc\u00030\u0018\u0000"+
		"\u00c6\u00c7\u0005\u0012\u0000\u0000\u00c7\u00c8\u0005/\u0000\u0000\u00c8"+
		"\u00c9\u0005\n\u0000\u0000\u00c9\u00cb\u00030\u0018\u0000\u00ca\u00c6"+
		"\u0001\u0000\u0000\u0000\u00cb\u00ce\u0001\u0000\u0000\u0000\u00cc\u00ca"+
		"\u0001\u0000\u0000\u0000\u00cc\u00cd\u0001\u0000\u0000\u0000\u00cd\u00d0"+
		"\u0001\u0000\u0000\u0000\u00ce\u00cc\u0001\u0000\u0000\u0000\u00cf\u00c3"+
		"\u0001\u0000\u0000\u0000\u00cf\u00d0\u0001\u0000\u0000\u0000\u00d0\u001d"+
		"\u0001\u0000\u0000\u0000\u00d1\u00d6\u00030\u0018\u0000\u00d2\u00d3\u0005"+
		"\u0012\u0000\u0000\u00d3\u00d5\u00030\u0018\u0000\u00d4\u00d2\u0001\u0000"+
		"\u0000\u0000\u00d5\u00d8\u0001\u0000\u0000\u0000\u00d6\u00d4\u0001\u0000"+
		"\u0000\u0000\u00d6\u00d7\u0001\u0000\u0000\u0000\u00d7\u00da\u0001\u0000"+
		"\u0000\u0000\u00d8\u00d6\u0001\u0000\u0000\u0000\u00d9\u00d1\u0001\u0000"+
		"\u0000\u0000\u00d9\u00da\u0001\u0000\u0000\u0000\u00da\u001f\u0001\u0000"+
		"\u0000\u0000\u00db\u00dc\u0005/\u0000\u0000\u00dc\u00e2\u0006\u0010\uffff"+
		"\uffff\u0000\u00dd\u00de\u0005\u0012\u0000\u0000\u00de\u00df\u0005/\u0000"+
		"\u0000\u00df\u00e1\u0006\u0010\uffff\uffff\u0000\u00e0\u00dd\u0001\u0000"+
		"\u0000\u0000\u00e1\u00e4\u0001\u0000\u0000\u0000\u00e2\u00e0\u0001\u0000"+
		"\u0000\u0000\u00e2\u00e3\u0001\u0000\u0000\u0000\u00e3\u00e6\u0001\u0000"+
		"\u0000\u0000\u00e4\u00e2\u0001\u0000\u0000\u0000\u00e5\u00db\u0001\u0000"+
		"\u0000\u0000\u00e5\u00e6\u0001\u0000\u0000\u0000\u00e6!\u0001\u0000\u0000"+
		"\u0000\u00e7\u00e8\u0005/\u0000\u0000\u00e8\u00e9\u0006\u0011\uffff\uffff"+
		"\u0000\u00e9\u00ea\u0005\n\u0000\u0000\u00ea\u00eb\u0003&\u0013\u0000"+
		"\u00eb\u00f0\u0006\u0011\uffff\uffff\u0000\u00ec\u00ed\u0005\u0013\u0000"+
		"\u0000\u00ed\u00ee\u0003,\u0016\u0000\u00ee\u00ef\u0006\u0011\uffff\uffff"+
		"\u0000\u00ef\u00f1\u0001\u0000\u0000\u0000\u00f0\u00ec\u0001\u0000\u0000"+
		"\u0000\u00f0\u00f1\u0001\u0000\u0000\u0000\u00f1\u00f2\u0001\u0000\u0000"+
		"\u0000\u00f2\u00f3\u0003*\u0015\u0000\u00f3\u00f7\u0005\u0002\u0000\u0000"+
		"\u00f4\u00f5\u0003\u0014\n\u0000\u00f5\u00f6\u0006\u0011\uffff\uffff\u0000"+
		"\u00f6\u00f8\u0001\u0000\u0000\u0000\u00f7\u00f4\u0001\u0000\u0000\u0000"+
		"\u00f7\u00f8\u0001\u0000\u0000\u0000\u00f8#\u0001\u0000\u0000\u0000\u00f9"+
		"\u00fa\u0005/\u0000\u0000\u00fa\u00fb\u0005\u0014\u0000\u0000\u00fb\u00fc"+
		"\u0005/\u0000\u0000\u00fc\u00fd\u0005\u0015\u0000\u0000\u00fd\u00fe\u0005"+
		"\n\u0000\u0000\u00fe\u00ff\u0005/\u0000\u0000\u00ff\u0100\u0003*\u0015"+
		"\u0000\u0100\u0101\u0005\u0002\u0000\u0000\u0101%\u0001\u0000\u0000\u0000"+
		"\u0102\u011e\u0005\u0016\u0000\u0000\u0103\u011e\u0005\u0017\u0000\u0000"+
		"\u0104\u011e\u0005\u0018\u0000\u0000\u0105\u011e\u0005\u0019\u0000\u0000"+
		"\u0106\u011e\u0005\u001a\u0000\u0000\u0107\u011e\u0005\u001b\u0000\u0000"+
		"\u0108\u011e\u0005\u001c\u0000\u0000\u0109\u011e\u0005\u001d\u0000\u0000"+
		"\u010a\u011e\u0005\u001e\u0000\u0000\u010b\u011e\u0005\u001f\u0000\u0000"+
		"\u010c\u011e\u0005 \u0000\u0000\u010d\u011e\u0005!\u0000\u0000\u010e\u011e"+
		"\u0005\"\u0000\u0000\u010f\u011e\u0005#\u0000\u0000\u0110\u011e\u0005"+
		"$\u0000\u0000\u0111\u011e\u0005%\u0000\u0000\u0112\u011e\u0005&\u0000"+
		"\u0000\u0113\u011e\u0005\'\u0000\u0000\u0114\u011e\u0005(\u0000\u0000"+
		"\u0115\u011e\u0005)\u0000\u0000\u0116\u011e\u0005*\u0000\u0000\u0117\u011e"+
		"\u0005+\u0000\u0000\u0118\u0119\u0005,\u0000\u0000\u0119\u011a\u0003&"+
		"\u0013\u0000\u011a\u011b\u0005-\u0000\u0000\u011b\u011e\u0001\u0000\u0000"+
		"\u0000\u011c\u011e\u0005/\u0000\u0000\u011d\u0102\u0001\u0000\u0000\u0000"+
		"\u011d\u0103\u0001\u0000\u0000\u0000\u011d\u0104\u0001\u0000\u0000\u0000"+
		"\u011d\u0105\u0001\u0000\u0000\u0000\u011d\u0106\u0001\u0000\u0000\u0000"+
		"\u011d\u0107\u0001\u0000\u0000\u0000\u011d\u0108\u0001\u0000\u0000\u0000"+
		"\u011d\u0109\u0001\u0000\u0000\u0000\u011d\u010a\u0001\u0000\u0000\u0000"+
		"\u011d\u010b\u0001\u0000\u0000\u0000\u011d\u010c\u0001\u0000\u0000\u0000"+
		"\u011d\u010d\u0001\u0000\u0000\u0000\u011d\u010e\u0001\u0000\u0000\u0000"+
		"\u011d\u010f\u0001\u0000\u0000\u0000\u011d\u0110\u0001\u0000\u0000\u0000"+
		"\u011d\u0111\u0001\u0000\u0000\u0000\u011d\u0112\u0001\u0000\u0000\u0000"+
		"\u011d\u0113\u0001\u0000\u0000\u0000\u011d\u0114\u0001\u0000\u0000\u0000"+
		"\u011d\u0115\u0001\u0000\u0000\u0000\u011d\u0116\u0001\u0000\u0000\u0000"+
		"\u011d\u0117\u0001\u0000\u0000\u0000\u011d\u0118\u0001\u0000\u0000\u0000"+
		"\u011d\u011c\u0001\u0000\u0000\u0000\u011e\'\u0001\u0000\u0000\u0000\u011f"+
		"\u0122\u0005/\u0000\u0000\u0120\u0121\u0005\u0013\u0000\u0000\u0121\u0123"+
		"\u00050\u0000\u0000\u0122\u0120\u0001\u0000\u0000\u0000\u0122\u0123\u0001"+
		"\u0000\u0000\u0000\u0123\u0124\u0001\u0000\u0000\u0000\u0124\u0125\u0003"+
		"*\u0015\u0000\u0125)\u0001\u0000\u0000\u0000\u0126\u0127\u0005\u0014\u0000"+
		"\u0000\u0127\u0128\u0003\u001a\r\u0000\u0128\u0129\u0005\u0015\u0000\u0000"+
		"\u0129\u012b\u0001\u0000\u0000\u0000\u012a\u0126\u0001\u0000\u0000\u0000"+
		"\u012a\u012b\u0001\u0000\u0000\u0000\u012b+\u0001\u0000\u0000\u0000\u012c"+
		"\u012d\u0007\u0001\u0000\u0000\u012d-\u0001\u0000\u0000\u0000\u012e\u0131"+
		"\u0003,\u0016\u0000\u012f\u0131\u00052\u0000\u0000\u0130\u012e\u0001\u0000"+
		"\u0000\u0000\u0130\u012f\u0001\u0000\u0000\u0000\u0131/\u0001\u0000\u0000"+
		"\u0000\u0132\u0139\u0003.\u0017\u0000\u0133\u0139\u0003\u0016\u000b\u0000"+
		"\u0134\u0135\u0005,\u0000\u0000\u0135\u0136\u0003\u001e\u000f\u0000\u0136"+
		"\u0137\u0005-\u0000\u0000\u0137\u0139\u0001\u0000\u0000\u0000\u0138\u0132"+
		"\u0001\u0000\u0000\u0000\u0138\u0133\u0001\u0000\u0000\u0000\u0138\u0134"+
		"\u0001\u0000\u0000\u0000\u01391\u0001\u0000\u0000\u0000\u001c7GI[dlt~"+
		"\u009b\u00ac\u00af\u00b4\u00ba\u00be\u00c1\u00cc\u00cf\u00d6\u00d9\u00e2"+
		"\u00e5\u00f0\u00f7\u011d\u0122\u012a\u0130\u0138";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}