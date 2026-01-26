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
		RULE_object = 10, RULE_commasep_enumval_decl = 11, RULE_commasep_metadata_item = 12, 
		RULE_commasep_object_item = 13, RULE_commasep_value = 14, RULE_commasep_annotation_decl = 15, 
		RULE_commasep_type_annotation_decl = 16, RULE_annotation_element_decl = 17, 
		RULE_type_annotation_decl = 18, RULE_field_decl = 19, RULE_field_annotation_decl = 20, 
		RULE_rpc_method = 21, RULE_type_ = 22, RULE_enumval_decl = 23, RULE_metadata = 24, 
		RULE_scalar = 25, RULE_single_value = 26, RULE_value = 27;
	private static String[] makeRuleNames() {
		return new String[] {
			"schema", "include", "namespace_decl", "type_decl", "enum_decl", "root_decl", 
			"file_extension_decl", "file_identifier_decl", "attribute_decl", "rpc_decl", 
			"object", "commasep_enumval_decl", "commasep_metadata_item", "commasep_object_item", 
			"commasep_value", "commasep_annotation_decl", "commasep_type_annotation_decl", 
			"annotation_element_decl", "type_annotation_decl", "field_decl", "field_annotation_decl", 
			"rpc_method", "type_", "enumval_decl", "metadata", "scalar", "single_value", 
			"value"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'include'", "';'", "'namespace'", "'.'", "'table'", "'struct'", 
			"'{'", "'}'", "'enum'", "':'", "'union'", "'root_type'", "'file_extension'", 
			"'file_identifier'", "'attribute'", "'rpc_service'", "','", "'('", "')'", 
			"'//'", "'='", "'bool'", "'byte'", "'ubyte'", "'short'", "'ushort'", 
			"'int'", "'uint'", "'float'", "'long'", "'ulong'", "'double'", "'int8'", 
			"'uint8'", "'int16'", "'uint16'", "'int32'", "'uint32'", "'int64'", "'uint64'", 
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
			setState(61);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__0) {
				{
				{
				setState(56);
				((SchemaContext)_localctx).includeOne = include();
				 _localctx.output.m_includes.Add(((SchemaContext)_localctx).includeOne.output); 
				}
				}
				setState(63);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(79);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 129768L) != 0)) {
				{
				setState(77);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case T__2:
					{
					setState(64);
					((SchemaContext)_localctx).namespaceOne = namespace_decl();
					 _localctx.output.m_namespaces.AddRange(((SchemaContext)_localctx).namespaceOne.output); 
					}
					break;
				case T__4:
				case T__5:
					{
					setState(67);
					((SchemaContext)_localctx).typeOne = type_decl();
					 _localctx.output.m_types.Add(((SchemaContext)_localctx).typeOne.output); 
					}
					break;
				case T__8:
				case T__10:
					{
					setState(70);
					enum_decl();
					}
					break;
				case T__11:
					{
					setState(71);
					root_decl();
					}
					break;
				case T__12:
					{
					setState(72);
					file_extension_decl();
					}
					break;
				case T__13:
					{
					setState(73);
					file_identifier_decl();
					}
					break;
				case T__14:
					{
					setState(74);
					attribute_decl();
					}
					break;
				case T__15:
					{
					setState(75);
					rpc_decl();
					}
					break;
				case T__6:
					{
					setState(76);
					object();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(81);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(82);
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
			setState(84);
			match(T__0);
			setState(85);
			((IncludeContext)_localctx).stringConstantOne = match(StringConstant);
			 _localctx.output += (((IncludeContext)_localctx).stringConstantOne!=null?((IncludeContext)_localctx).stringConstantOne.getText():null); 
			setState(87);
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
			setState(89);
			match(T__2);
			setState(90);
			((Namespace_declContext)_localctx).identFirst = match(Ident);
			 _localctx.output.Add((((Namespace_declContext)_localctx).identFirst!=null?((Namespace_declContext)_localctx).identFirst.getText():null)); 
			setState(97);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__3) {
				{
				{
				setState(92);
				match(T__3);
				setState(93);
				((Namespace_declContext)_localctx).identLeft = match(Ident);
				 _localctx.output.Add((((Namespace_declContext)_localctx).identLeft!=null?((Namespace_declContext)_localctx).identLeft.getText():null)); 
				}
				}
				setState(99);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(100);
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
		public Type_annotation_declContext typeAnnotationOne;
		public Field_declContext fieldOne;
		public MetadataContext metadata() {
			return getRuleContext(MetadataContext.class,0);
		}
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public Type_annotation_declContext type_annotation_decl() {
			return getRuleContext(Type_annotation_declContext.class,0);
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
			setState(106);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__4:
				{
				setState(102);
				match(T__4);
				 _localctx.output.m_kind = FlatCacheGenerator.TypeKind.Table; 
				}
				break;
			case T__5:
				{
				setState(104);
				match(T__5);
				 _localctx.output.m_kind = FlatCacheGenerator.TypeKind.Struct; 
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(108);
			((Type_declContext)_localctx).identOne = match(Ident);
			  _localctx.output.m_name = (((Type_declContext)_localctx).identOne!=null?((Type_declContext)_localctx).identOne.getText():null); 
			setState(110);
			metadata();
			setState(114);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__19) {
				{
				setState(111);
				((Type_declContext)_localctx).typeAnnotationOne = type_annotation_decl();
				 _localctx.output.m_indexes = ((Type_declContext)_localctx).typeAnnotationOne.output; 
				}
			}

			setState(116);
			match(T__6);
			setState(120); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(117);
				((Type_declContext)_localctx).fieldOne = field_decl();
				 _localctx.output.m_fields.Add(((Type_declContext)_localctx).fieldOne.output); 
				}
				}
				setState(122); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==Ident );
			setState(124);
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
			setState(132);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__8:
				{
				setState(126);
				match(T__8);
				setState(127);
				match(Ident);
				setState(128);
				match(T__9);
				setState(129);
				type_();
				}
				break;
			case T__10:
				{
				setState(130);
				match(T__10);
				setState(131);
				match(Ident);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(134);
			metadata();
			setState(135);
			match(T__6);
			setState(136);
			commasep_enumval_decl();
			setState(137);
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
			setState(139);
			match(T__11);
			setState(140);
			match(Ident);
			setState(141);
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
			setState(143);
			match(T__12);
			setState(144);
			match(StringConstant);
			setState(145);
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
			setState(147);
			match(T__13);
			setState(148);
			match(StringConstant);
			setState(149);
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
			setState(151);
			match(T__14);
			setState(152);
			_la = _input.LA(1);
			if ( !(_la==Ident || _la==StringConstant) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(153);
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
			setState(155);
			match(T__15);
			setState(156);
			match(Ident);
			setState(157);
			match(T__6);
			setState(159); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(158);
				rpc_method();
				}
				}
				setState(161); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==Ident );
			setState(163);
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
		enterRule(_localctx, 20, RULE_object);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(165);
			match(T__6);
			setState(166);
			commasep_object_item();
			setState(167);
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
		enterRule(_localctx, 22, RULE_commasep_enumval_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(177);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Ident) {
				{
				setState(169);
				enumval_decl();
				setState(174);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__16) {
					{
					{
					setState(170);
					match(T__16);
					setState(171);
					enumval_decl();
					}
					}
					setState(176);
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
		enterRule(_localctx, 24, RULE_commasep_metadata_item);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(195);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Ident) {
				{
				setState(179);
				match(Ident);
				setState(182);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__9) {
					{
					setState(180);
					match(T__9);
					setState(181);
					single_value();
					}
				}

				setState(192);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__16) {
					{
					{
					setState(184);
					match(T__16);
					setState(185);
					match(Ident);
					setState(188);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==T__9) {
						{
						setState(186);
						match(T__9);
						setState(187);
						single_value();
						}
					}

					}
					}
					setState(194);
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
		enterRule(_localctx, 26, RULE_commasep_object_item);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(209);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Ident) {
				{
				setState(197);
				match(Ident);
				setState(198);
				match(T__9);
				setState(199);
				value();
				setState(206);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__16) {
					{
					{
					setState(200);
					match(T__16);
					setState(201);
					match(Ident);
					setState(202);
					match(T__9);
					setState(203);
					value();
					}
					}
					setState(208);
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
		enterRule(_localctx, 28, RULE_commasep_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(219);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2058285767196800L) != 0)) {
				{
				setState(211);
				value();
				setState(216);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__16) {
					{
					{
					setState(212);
					match(T__16);
					setState(213);
					value();
					}
					}
					setState(218);
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
		enterRule(_localctx, 30, RULE_commasep_annotation_decl);
		 ((Commasep_annotation_declContext)_localctx).output =  new List<string>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(231);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
			case 1:
				{
				setState(221);
				((Commasep_annotation_declContext)_localctx).identFirst = match(Ident);
				 _localctx.output.Add( (((Commasep_annotation_declContext)_localctx).identFirst!=null?((Commasep_annotation_declContext)_localctx).identFirst.getText():null) ); 
				setState(228);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__16) {
					{
					{
					setState(223);
					match(T__16);
					setState(224);
					((Commasep_annotation_declContext)_localctx).identOther = match(Ident);
					 _localctx.output.Add( (((Commasep_annotation_declContext)_localctx).identOther!=null?((Commasep_annotation_declContext)_localctx).identOther.getText():null) ); 
					}
					}
					setState(230);
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
	public static class Commasep_type_annotation_declContext extends ParserRuleContext {
		public List<Dictionary<string,List<string>>> output;
		public Annotation_element_declContext elementFirst;
		public Annotation_element_declContext elementOther;
		public List<Annotation_element_declContext> annotation_element_decl() {
			return getRuleContexts(Annotation_element_declContext.class);
		}
		public Annotation_element_declContext annotation_element_decl(int i) {
			return getRuleContext(Annotation_element_declContext.class,i);
		}
		public Commasep_type_annotation_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_commasep_type_annotation_decl; }
	}

	public final Commasep_type_annotation_declContext commasep_type_annotation_decl() throws RecognitionException {
		Commasep_type_annotation_declContext _localctx = new Commasep_type_annotation_declContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_commasep_type_annotation_decl);
		 ((Commasep_type_annotation_declContext)_localctx).output =  new List<Dictionary<string,List<string>>>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(244);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Ident) {
				{
				setState(233);
				((Commasep_type_annotation_declContext)_localctx).elementFirst = annotation_element_decl();
				 _localctx.output.Add( ((Commasep_type_annotation_declContext)_localctx).elementFirst.output ); 
				setState(241);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__16) {
					{
					{
					setState(235);
					match(T__16);
					setState(236);
					((Commasep_type_annotation_declContext)_localctx).elementOther = annotation_element_decl();
					 _localctx.output.Add( ((Commasep_type_annotation_declContext)_localctx).elementOther.output ); 
					}
					}
					setState(243);
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
	public static class Annotation_element_declContext extends ParserRuleContext {
		public Dictionary<string,List<string>> output;
		public Token identOne;
		public Commasep_annotation_declContext commasepElemOne;
		public TerminalNode Ident() { return getToken(FlatBuffersParser.Ident, 0); }
		public Commasep_annotation_declContext commasep_annotation_decl() {
			return getRuleContext(Commasep_annotation_declContext.class,0);
		}
		public Annotation_element_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotation_element_decl; }
	}

	public final Annotation_element_declContext annotation_element_decl() throws RecognitionException {
		Annotation_element_declContext _localctx = new Annotation_element_declContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_annotation_element_decl);
		 ((Annotation_element_declContext)_localctx).output =  new Dictionary<string,List<string>>(); 
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(246);
			((Annotation_element_declContext)_localctx).identOne = match(Ident);
			setState(247);
			match(T__17);
			setState(248);
			((Annotation_element_declContext)_localctx).commasepElemOne = commasep_annotation_decl();
			 
			        _localctx.output[(((Annotation_element_declContext)_localctx).identOne!=null?((Annotation_element_declContext)_localctx).identOne.getText():null)] = ((Annotation_element_declContext)_localctx).commasepElemOne.output;
			    
			setState(250);
			match(T__18);
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
	public static class Type_annotation_declContext extends ParserRuleContext {
		public List<Dictionary<string,List<string>>> output;
		public Commasep_type_annotation_declContext commasepTypeOne;
		public Commasep_type_annotation_declContext commasep_type_annotation_decl() {
			return getRuleContext(Commasep_type_annotation_declContext.class,0);
		}
		public Type_annotation_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type_annotation_decl; }
	}

	public final Type_annotation_declContext type_annotation_decl() throws RecognitionException {
		Type_annotation_declContext _localctx = new Type_annotation_declContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_type_annotation_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(252);
			match(T__19);
			setState(253);
			((Type_annotation_declContext)_localctx).commasepTypeOne = commasep_type_annotation_decl();
			 ((Type_annotation_declContext)_localctx).output =  ((Type_annotation_declContext)_localctx).commasepTypeOne.output; 
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
		public Field_annotation_declContext fieldAnnotationOne;
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
		public Field_annotation_declContext field_annotation_decl() {
			return getRuleContext(Field_annotation_declContext.class,0);
		}
		public Field_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_field_decl; }
	}

	public final Field_declContext field_decl() throws RecognitionException {
		Field_declContext _localctx = new Field_declContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_field_decl);
		 ((Field_declContext)_localctx).output =  new FlatCacheGenerator.FlatBufferField(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(256);
			((Field_declContext)_localctx).identOne = match(Ident);
			 _localctx.output.m_name = (((Field_declContext)_localctx).identOne!=null?((Field_declContext)_localctx).identOne.getText():null); 
			setState(258);
			match(T__9);
			setState(259);
			((Field_declContext)_localctx).typeOne = type_();
			 _localctx.output.m_type = (((Field_declContext)_localctx).typeOne!=null?_input.getText(((Field_declContext)_localctx).typeOne.start,((Field_declContext)_localctx).typeOne.stop):null); 
			setState(265);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__20) {
				{
				setState(261);
				match(T__20);
				setState(262);
				((Field_declContext)_localctx).scalarOne = scalar();
				 _localctx.output.m_defaultValue = (((Field_declContext)_localctx).scalarOne!=null?_input.getText(((Field_declContext)_localctx).scalarOne.start,((Field_declContext)_localctx).scalarOne.stop):null); 
				}
			}

			setState(267);
			metadata();
			setState(268);
			match(T__1);
			setState(272);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__19) {
				{
				setState(269);
				((Field_declContext)_localctx).fieldAnnotationOne = field_annotation_decl();
				 _localctx.output.m_annotatedAttributes = ((Field_declContext)_localctx).fieldAnnotationOne.output; 
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
	public static class Field_annotation_declContext extends ParserRuleContext {
		public List<string> output;
		public Commasep_annotation_declContext commasepFieldOne;
		public Commasep_annotation_declContext commasep_annotation_decl() {
			return getRuleContext(Commasep_annotation_declContext.class,0);
		}
		public Field_annotation_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_field_annotation_decl; }
	}

	public final Field_annotation_declContext field_annotation_decl() throws RecognitionException {
		Field_annotation_declContext _localctx = new Field_annotation_declContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_field_annotation_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(274);
			match(T__19);
			setState(275);
			((Field_annotation_declContext)_localctx).commasepFieldOne = commasep_annotation_decl();
			 ((Field_annotation_declContext)_localctx).output =  ((Field_annotation_declContext)_localctx).commasepFieldOne.output; 
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
		enterRule(_localctx, 42, RULE_rpc_method);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(278);
			match(Ident);
			setState(279);
			match(T__17);
			setState(280);
			match(Ident);
			setState(281);
			match(T__18);
			setState(282);
			match(T__9);
			setState(283);
			match(Ident);
			setState(284);
			metadata();
			setState(285);
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
		enterRule(_localctx, 44, RULE_type_);
		try {
			setState(314);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__21:
				enterOuterAlt(_localctx, 1);
				{
				setState(287);
				match(T__21);
				}
				break;
			case T__22:
				enterOuterAlt(_localctx, 2);
				{
				setState(288);
				match(T__22);
				}
				break;
			case T__23:
				enterOuterAlt(_localctx, 3);
				{
				setState(289);
				match(T__23);
				}
				break;
			case T__24:
				enterOuterAlt(_localctx, 4);
				{
				setState(290);
				match(T__24);
				}
				break;
			case T__25:
				enterOuterAlt(_localctx, 5);
				{
				setState(291);
				match(T__25);
				}
				break;
			case T__26:
				enterOuterAlt(_localctx, 6);
				{
				setState(292);
				match(T__26);
				}
				break;
			case T__27:
				enterOuterAlt(_localctx, 7);
				{
				setState(293);
				match(T__27);
				}
				break;
			case T__28:
				enterOuterAlt(_localctx, 8);
				{
				setState(294);
				match(T__28);
				}
				break;
			case T__29:
				enterOuterAlt(_localctx, 9);
				{
				setState(295);
				match(T__29);
				}
				break;
			case T__30:
				enterOuterAlt(_localctx, 10);
				{
				setState(296);
				match(T__30);
				}
				break;
			case T__31:
				enterOuterAlt(_localctx, 11);
				{
				setState(297);
				match(T__31);
				}
				break;
			case T__32:
				enterOuterAlt(_localctx, 12);
				{
				setState(298);
				match(T__32);
				}
				break;
			case T__33:
				enterOuterAlt(_localctx, 13);
				{
				setState(299);
				match(T__33);
				}
				break;
			case T__34:
				enterOuterAlt(_localctx, 14);
				{
				setState(300);
				match(T__34);
				}
				break;
			case T__35:
				enterOuterAlt(_localctx, 15);
				{
				setState(301);
				match(T__35);
				}
				break;
			case T__36:
				enterOuterAlt(_localctx, 16);
				{
				setState(302);
				match(T__36);
				}
				break;
			case T__37:
				enterOuterAlt(_localctx, 17);
				{
				setState(303);
				match(T__37);
				}
				break;
			case T__38:
				enterOuterAlt(_localctx, 18);
				{
				setState(304);
				match(T__38);
				}
				break;
			case T__39:
				enterOuterAlt(_localctx, 19);
				{
				setState(305);
				match(T__39);
				}
				break;
			case T__40:
				enterOuterAlt(_localctx, 20);
				{
				setState(306);
				match(T__40);
				}
				break;
			case T__41:
				enterOuterAlt(_localctx, 21);
				{
				setState(307);
				match(T__41);
				}
				break;
			case T__42:
				enterOuterAlt(_localctx, 22);
				{
				setState(308);
				match(T__42);
				}
				break;
			case T__43:
				enterOuterAlt(_localctx, 23);
				{
				setState(309);
				match(T__43);
				setState(310);
				type_();
				setState(311);
				match(T__44);
				}
				break;
			case Ident:
				enterOuterAlt(_localctx, 24);
				{
				setState(313);
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
		enterRule(_localctx, 46, RULE_enumval_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(316);
			match(Ident);
			setState(319);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__20) {
				{
				setState(317);
				match(T__20);
				setState(318);
				match(IntegerConstant);
				}
			}

			setState(321);
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
		enterRule(_localctx, 48, RULE_metadata);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(327);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__17) {
				{
				setState(323);
				match(T__17);
				setState(324);
				commasep_metadata_item();
				setState(325);
				match(T__18);
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
		enterRule(_localctx, 50, RULE_scalar);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(329);
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
		enterRule(_localctx, 52, RULE_single_value);
		try {
			setState(333);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case BooleanConstant:
			case IntegerConstant:
			case FloatConstant:
				enterOuterAlt(_localctx, 1);
				{
				setState(331);
				scalar();
				}
				break;
			case StringConstant:
				enterOuterAlt(_localctx, 2);
				{
				setState(332);
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
		enterRule(_localctx, 54, RULE_value);
		try {
			setState(341);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case BooleanConstant:
			case IntegerConstant:
			case FloatConstant:
			case StringConstant:
				enterOuterAlt(_localctx, 1);
				{
				setState(335);
				single_value();
				}
				break;
			case T__6:
				enterOuterAlt(_localctx, 2);
				{
				setState(336);
				object();
				}
				break;
			case T__43:
				enterOuterAlt(_localctx, 3);
				{
				setState(337);
				match(T__43);
				setState(338);
				commasep_value();
				setState(339);
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
		"\u0004\u00013\u0158\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007\u001b"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0005\u0000<\b\u0000\n\u0000\f\u0000"+
		"?\t\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0005\u0000N\b\u0000\n\u0000\f\u0000Q\t\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0005\u0002`\b\u0002\n\u0002\f\u0002c\t\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0003\u0003"+
		"k\b\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0003\u0003s\b\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0004\u0003y\b\u0003\u000b\u0003\f\u0003z\u0001\u0003\u0001"+
		"\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0003\u0004\u0085\b\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0004\t\u00a0\b\t\u000b\t\f\t\u00a1\u0001\t\u0001\t\u0001\n"+
		"\u0001\n\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\u000b\u0005\u000b"+
		"\u00ad\b\u000b\n\u000b\f\u000b\u00b0\t\u000b\u0003\u000b\u00b2\b\u000b"+
		"\u0001\f\u0001\f\u0001\f\u0003\f\u00b7\b\f\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0003\f\u00bd\b\f\u0005\f\u00bf\b\f\n\f\f\f\u00c2\t\f\u0003\f\u00c4"+
		"\b\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0005\r\u00cd"+
		"\b\r\n\r\f\r\u00d0\t\r\u0003\r\u00d2\b\r\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0005\u000e\u00d7\b\u000e\n\u000e\f\u000e\u00da\t\u000e\u0003\u000e"+
		"\u00dc\b\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f"+
		"\u0005\u000f\u00e3\b\u000f\n\u000f\f\u000f\u00e6\t\u000f\u0003\u000f\u00e8"+
		"\b\u000f\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001"+
		"\u0010\u0005\u0010\u00f0\b\u0010\n\u0010\f\u0010\u00f3\t\u0010\u0003\u0010"+
		"\u00f5\b\u0010\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011"+
		"\u0001\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0013"+
		"\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013"+
		"\u0001\u0013\u0001\u0013\u0003\u0013\u010a\b\u0013\u0001\u0013\u0001\u0013"+
		"\u0001\u0013\u0001\u0013\u0001\u0013\u0003\u0013\u0111\b\u0013\u0001\u0014"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0015\u0001\u0015\u0001\u0015"+
		"\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0003\u0016\u013b\b\u0016\u0001\u0017"+
		"\u0001\u0017\u0001\u0017\u0003\u0017\u0140\b\u0017\u0001\u0017\u0001\u0017"+
		"\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0003\u0018\u0148\b\u0018"+
		"\u0001\u0019\u0001\u0019\u0001\u001a\u0001\u001a\u0003\u001a\u014e\b\u001a"+
		"\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b"+
		"\u0003\u001b\u0156\b\u001b\u0001\u001b\u0000\u0000\u001c\u0000\u0002\u0004"+
		"\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u001e \""+
		"$&(*,.0246\u0000\u0002\u0002\u0000//22\u0002\u0000..01\u0177\u0000=\u0001"+
		"\u0000\u0000\u0000\u0002T\u0001\u0000\u0000\u0000\u0004Y\u0001\u0000\u0000"+
		"\u0000\u0006j\u0001\u0000\u0000\u0000\b\u0084\u0001\u0000\u0000\u0000"+
		"\n\u008b\u0001\u0000\u0000\u0000\f\u008f\u0001\u0000\u0000\u0000\u000e"+
		"\u0093\u0001\u0000\u0000\u0000\u0010\u0097\u0001\u0000\u0000\u0000\u0012"+
		"\u009b\u0001\u0000\u0000\u0000\u0014\u00a5\u0001\u0000\u0000\u0000\u0016"+
		"\u00b1\u0001\u0000\u0000\u0000\u0018\u00c3\u0001\u0000\u0000\u0000\u001a"+
		"\u00d1\u0001\u0000\u0000\u0000\u001c\u00db\u0001\u0000\u0000\u0000\u001e"+
		"\u00e7\u0001\u0000\u0000\u0000 \u00f4\u0001\u0000\u0000\u0000\"\u00f6"+
		"\u0001\u0000\u0000\u0000$\u00fc\u0001\u0000\u0000\u0000&\u0100\u0001\u0000"+
		"\u0000\u0000(\u0112\u0001\u0000\u0000\u0000*\u0116\u0001\u0000\u0000\u0000"+
		",\u013a\u0001\u0000\u0000\u0000.\u013c\u0001\u0000\u0000\u00000\u0147"+
		"\u0001\u0000\u0000\u00002\u0149\u0001\u0000\u0000\u00004\u014d\u0001\u0000"+
		"\u0000\u00006\u0155\u0001\u0000\u0000\u000089\u0003\u0002\u0001\u0000"+
		"9:\u0006\u0000\uffff\uffff\u0000:<\u0001\u0000\u0000\u0000;8\u0001\u0000"+
		"\u0000\u0000<?\u0001\u0000\u0000\u0000=;\u0001\u0000\u0000\u0000=>\u0001"+
		"\u0000\u0000\u0000>O\u0001\u0000\u0000\u0000?=\u0001\u0000\u0000\u0000"+
		"@A\u0003\u0004\u0002\u0000AB\u0006\u0000\uffff\uffff\u0000BN\u0001\u0000"+
		"\u0000\u0000CD\u0003\u0006\u0003\u0000DE\u0006\u0000\uffff\uffff\u0000"+
		"EN\u0001\u0000\u0000\u0000FN\u0003\b\u0004\u0000GN\u0003\n\u0005\u0000"+
		"HN\u0003\f\u0006\u0000IN\u0003\u000e\u0007\u0000JN\u0003\u0010\b\u0000"+
		"KN\u0003\u0012\t\u0000LN\u0003\u0014\n\u0000M@\u0001\u0000\u0000\u0000"+
		"MC\u0001\u0000\u0000\u0000MF\u0001\u0000\u0000\u0000MG\u0001\u0000\u0000"+
		"\u0000MH\u0001\u0000\u0000\u0000MI\u0001\u0000\u0000\u0000MJ\u0001\u0000"+
		"\u0000\u0000MK\u0001\u0000\u0000\u0000ML\u0001\u0000\u0000\u0000NQ\u0001"+
		"\u0000\u0000\u0000OM\u0001\u0000\u0000\u0000OP\u0001\u0000\u0000\u0000"+
		"PR\u0001\u0000\u0000\u0000QO\u0001\u0000\u0000\u0000RS\u0005\u0000\u0000"+
		"\u0001S\u0001\u0001\u0000\u0000\u0000TU\u0005\u0001\u0000\u0000UV\u0005"+
		"2\u0000\u0000VW\u0006\u0001\uffff\uffff\u0000WX\u0005\u0002\u0000\u0000"+
		"X\u0003\u0001\u0000\u0000\u0000YZ\u0005\u0003\u0000\u0000Z[\u0005/\u0000"+
		"\u0000[a\u0006\u0002\uffff\uffff\u0000\\]\u0005\u0004\u0000\u0000]^\u0005"+
		"/\u0000\u0000^`\u0006\u0002\uffff\uffff\u0000_\\\u0001\u0000\u0000\u0000"+
		"`c\u0001\u0000\u0000\u0000a_\u0001\u0000\u0000\u0000ab\u0001\u0000\u0000"+
		"\u0000bd\u0001\u0000\u0000\u0000ca\u0001\u0000\u0000\u0000de\u0005\u0002"+
		"\u0000\u0000e\u0005\u0001\u0000\u0000\u0000fg\u0005\u0005\u0000\u0000"+
		"gk\u0006\u0003\uffff\uffff\u0000hi\u0005\u0006\u0000\u0000ik\u0006\u0003"+
		"\uffff\uffff\u0000jf\u0001\u0000\u0000\u0000jh\u0001\u0000\u0000\u0000"+
		"kl\u0001\u0000\u0000\u0000lm\u0005/\u0000\u0000mn\u0006\u0003\uffff\uffff"+
		"\u0000nr\u00030\u0018\u0000op\u0003$\u0012\u0000pq\u0006\u0003\uffff\uffff"+
		"\u0000qs\u0001\u0000\u0000\u0000ro\u0001\u0000\u0000\u0000rs\u0001\u0000"+
		"\u0000\u0000st\u0001\u0000\u0000\u0000tx\u0005\u0007\u0000\u0000uv\u0003"+
		"&\u0013\u0000vw\u0006\u0003\uffff\uffff\u0000wy\u0001\u0000\u0000\u0000"+
		"xu\u0001\u0000\u0000\u0000yz\u0001\u0000\u0000\u0000zx\u0001\u0000\u0000"+
		"\u0000z{\u0001\u0000\u0000\u0000{|\u0001\u0000\u0000\u0000|}\u0005\b\u0000"+
		"\u0000}\u0007\u0001\u0000\u0000\u0000~\u007f\u0005\t\u0000\u0000\u007f"+
		"\u0080\u0005/\u0000\u0000\u0080\u0081\u0005\n\u0000\u0000\u0081\u0085"+
		"\u0003,\u0016\u0000\u0082\u0083\u0005\u000b\u0000\u0000\u0083\u0085\u0005"+
		"/\u0000\u0000\u0084~\u0001\u0000\u0000\u0000\u0084\u0082\u0001\u0000\u0000"+
		"\u0000\u0085\u0086\u0001\u0000\u0000\u0000\u0086\u0087\u00030\u0018\u0000"+
		"\u0087\u0088\u0005\u0007\u0000\u0000\u0088\u0089\u0003\u0016\u000b\u0000"+
		"\u0089\u008a\u0005\b\u0000\u0000\u008a\t\u0001\u0000\u0000\u0000\u008b"+
		"\u008c\u0005\f\u0000\u0000\u008c\u008d\u0005/\u0000\u0000\u008d\u008e"+
		"\u0005\u0002\u0000\u0000\u008e\u000b\u0001\u0000\u0000\u0000\u008f\u0090"+
		"\u0005\r\u0000\u0000\u0090\u0091\u00052\u0000\u0000\u0091\u0092\u0005"+
		"\u0002\u0000\u0000\u0092\r\u0001\u0000\u0000\u0000\u0093\u0094\u0005\u000e"+
		"\u0000\u0000\u0094\u0095\u00052\u0000\u0000\u0095\u0096\u0005\u0002\u0000"+
		"\u0000\u0096\u000f\u0001\u0000\u0000\u0000\u0097\u0098\u0005\u000f\u0000"+
		"\u0000\u0098\u0099\u0007\u0000\u0000\u0000\u0099\u009a\u0005\u0002\u0000"+
		"\u0000\u009a\u0011\u0001\u0000\u0000\u0000\u009b\u009c\u0005\u0010\u0000"+
		"\u0000\u009c\u009d\u0005/\u0000\u0000\u009d\u009f\u0005\u0007\u0000\u0000"+
		"\u009e\u00a0\u0003*\u0015\u0000\u009f\u009e\u0001\u0000\u0000\u0000\u00a0"+
		"\u00a1\u0001\u0000\u0000\u0000\u00a1\u009f\u0001\u0000\u0000\u0000\u00a1"+
		"\u00a2\u0001\u0000\u0000\u0000\u00a2\u00a3\u0001\u0000\u0000\u0000\u00a3"+
		"\u00a4\u0005\b\u0000\u0000\u00a4\u0013\u0001\u0000\u0000\u0000\u00a5\u00a6"+
		"\u0005\u0007\u0000\u0000\u00a6\u00a7\u0003\u001a\r\u0000\u00a7\u00a8\u0005"+
		"\b\u0000\u0000\u00a8\u0015\u0001\u0000\u0000\u0000\u00a9\u00ae\u0003."+
		"\u0017\u0000\u00aa\u00ab\u0005\u0011\u0000\u0000\u00ab\u00ad\u0003.\u0017"+
		"\u0000\u00ac\u00aa\u0001\u0000\u0000\u0000\u00ad\u00b0\u0001\u0000\u0000"+
		"\u0000\u00ae\u00ac\u0001\u0000\u0000\u0000\u00ae\u00af\u0001\u0000\u0000"+
		"\u0000\u00af\u00b2\u0001\u0000\u0000\u0000\u00b0\u00ae\u0001\u0000\u0000"+
		"\u0000\u00b1\u00a9\u0001\u0000\u0000\u0000\u00b1\u00b2\u0001\u0000\u0000"+
		"\u0000\u00b2\u0017\u0001\u0000\u0000\u0000\u00b3\u00b6\u0005/\u0000\u0000"+
		"\u00b4\u00b5\u0005\n\u0000\u0000\u00b5\u00b7\u00034\u001a\u0000\u00b6"+
		"\u00b4\u0001\u0000\u0000\u0000\u00b6\u00b7\u0001\u0000\u0000\u0000\u00b7"+
		"\u00c0\u0001\u0000\u0000\u0000\u00b8\u00b9\u0005\u0011\u0000\u0000\u00b9"+
		"\u00bc\u0005/\u0000\u0000\u00ba\u00bb\u0005\n\u0000\u0000\u00bb\u00bd"+
		"\u00034\u001a\u0000\u00bc\u00ba\u0001\u0000\u0000\u0000\u00bc\u00bd\u0001"+
		"\u0000\u0000\u0000\u00bd\u00bf\u0001\u0000\u0000\u0000\u00be\u00b8\u0001"+
		"\u0000\u0000\u0000\u00bf\u00c2\u0001\u0000\u0000\u0000\u00c0\u00be\u0001"+
		"\u0000\u0000\u0000\u00c0\u00c1\u0001\u0000\u0000\u0000\u00c1\u00c4\u0001"+
		"\u0000\u0000\u0000\u00c2\u00c0\u0001\u0000\u0000\u0000\u00c3\u00b3\u0001"+
		"\u0000\u0000\u0000\u00c3\u00c4\u0001\u0000\u0000\u0000\u00c4\u0019\u0001"+
		"\u0000\u0000\u0000\u00c5\u00c6\u0005/\u0000\u0000\u00c6\u00c7\u0005\n"+
		"\u0000\u0000\u00c7\u00ce\u00036\u001b\u0000\u00c8\u00c9\u0005\u0011\u0000"+
		"\u0000\u00c9\u00ca\u0005/\u0000\u0000\u00ca\u00cb\u0005\n\u0000\u0000"+
		"\u00cb\u00cd\u00036\u001b\u0000\u00cc\u00c8\u0001\u0000\u0000\u0000\u00cd"+
		"\u00d0\u0001\u0000\u0000\u0000\u00ce\u00cc\u0001\u0000\u0000\u0000\u00ce"+
		"\u00cf\u0001\u0000\u0000\u0000\u00cf\u00d2\u0001\u0000\u0000\u0000\u00d0"+
		"\u00ce\u0001\u0000\u0000\u0000\u00d1\u00c5\u0001\u0000\u0000\u0000\u00d1"+
		"\u00d2\u0001\u0000\u0000\u0000\u00d2\u001b\u0001\u0000\u0000\u0000\u00d3"+
		"\u00d8\u00036\u001b\u0000\u00d4\u00d5\u0005\u0011\u0000\u0000\u00d5\u00d7"+
		"\u00036\u001b\u0000\u00d6\u00d4\u0001\u0000\u0000\u0000\u00d7\u00da\u0001"+
		"\u0000\u0000\u0000\u00d8\u00d6\u0001\u0000\u0000\u0000\u00d8\u00d9\u0001"+
		"\u0000\u0000\u0000\u00d9\u00dc\u0001\u0000\u0000\u0000\u00da\u00d8\u0001"+
		"\u0000\u0000\u0000\u00db\u00d3\u0001\u0000\u0000\u0000\u00db\u00dc\u0001"+
		"\u0000\u0000\u0000\u00dc\u001d\u0001\u0000\u0000\u0000\u00dd\u00de\u0005"+
		"/\u0000\u0000\u00de\u00e4\u0006\u000f\uffff\uffff\u0000\u00df\u00e0\u0005"+
		"\u0011\u0000\u0000\u00e0\u00e1\u0005/\u0000\u0000\u00e1\u00e3\u0006\u000f"+
		"\uffff\uffff\u0000\u00e2\u00df\u0001\u0000\u0000\u0000\u00e3\u00e6\u0001"+
		"\u0000\u0000\u0000\u00e4\u00e2\u0001\u0000\u0000\u0000\u00e4\u00e5\u0001"+
		"\u0000\u0000\u0000\u00e5\u00e8\u0001\u0000\u0000\u0000\u00e6\u00e4\u0001"+
		"\u0000\u0000\u0000\u00e7\u00dd\u0001\u0000\u0000\u0000\u00e7\u00e8\u0001"+
		"\u0000\u0000\u0000\u00e8\u001f\u0001\u0000\u0000\u0000\u00e9\u00ea\u0003"+
		"\"\u0011\u0000\u00ea\u00f1\u0006\u0010\uffff\uffff\u0000\u00eb\u00ec\u0005"+
		"\u0011\u0000\u0000\u00ec\u00ed\u0003\"\u0011\u0000\u00ed\u00ee\u0006\u0010"+
		"\uffff\uffff\u0000\u00ee\u00f0\u0001\u0000\u0000\u0000\u00ef\u00eb\u0001"+
		"\u0000\u0000\u0000\u00f0\u00f3\u0001\u0000\u0000\u0000\u00f1\u00ef\u0001"+
		"\u0000\u0000\u0000\u00f1\u00f2\u0001\u0000\u0000\u0000\u00f2\u00f5\u0001"+
		"\u0000\u0000\u0000\u00f3\u00f1\u0001\u0000\u0000\u0000\u00f4\u00e9\u0001"+
		"\u0000\u0000\u0000\u00f4\u00f5\u0001\u0000\u0000\u0000\u00f5!\u0001\u0000"+
		"\u0000\u0000\u00f6\u00f7\u0005/\u0000\u0000\u00f7\u00f8\u0005\u0012\u0000"+
		"\u0000\u00f8\u00f9\u0003\u001e\u000f\u0000\u00f9\u00fa\u0006\u0011\uffff"+
		"\uffff\u0000\u00fa\u00fb\u0005\u0013\u0000\u0000\u00fb#\u0001\u0000\u0000"+
		"\u0000\u00fc\u00fd\u0005\u0014\u0000\u0000\u00fd\u00fe\u0003 \u0010\u0000"+
		"\u00fe\u00ff\u0006\u0012\uffff\uffff\u0000\u00ff%\u0001\u0000\u0000\u0000"+
		"\u0100\u0101\u0005/\u0000\u0000\u0101\u0102\u0006\u0013\uffff\uffff\u0000"+
		"\u0102\u0103\u0005\n\u0000\u0000\u0103\u0104\u0003,\u0016\u0000\u0104"+
		"\u0109\u0006\u0013\uffff\uffff\u0000\u0105\u0106\u0005\u0015\u0000\u0000"+
		"\u0106\u0107\u00032\u0019\u0000\u0107\u0108\u0006\u0013\uffff\uffff\u0000"+
		"\u0108\u010a\u0001\u0000\u0000\u0000\u0109\u0105\u0001\u0000\u0000\u0000"+
		"\u0109\u010a\u0001\u0000\u0000\u0000\u010a\u010b\u0001\u0000\u0000\u0000"+
		"\u010b\u010c\u00030\u0018\u0000\u010c\u0110\u0005\u0002\u0000\u0000\u010d"+
		"\u010e\u0003(\u0014\u0000\u010e\u010f\u0006\u0013\uffff\uffff\u0000\u010f"+
		"\u0111\u0001\u0000\u0000\u0000\u0110\u010d\u0001\u0000\u0000\u0000\u0110"+
		"\u0111\u0001\u0000\u0000\u0000\u0111\'\u0001\u0000\u0000\u0000\u0112\u0113"+
		"\u0005\u0014\u0000\u0000\u0113\u0114\u0003\u001e\u000f\u0000\u0114\u0115"+
		"\u0006\u0014\uffff\uffff\u0000\u0115)\u0001\u0000\u0000\u0000\u0116\u0117"+
		"\u0005/\u0000\u0000\u0117\u0118\u0005\u0012\u0000\u0000\u0118\u0119\u0005"+
		"/\u0000\u0000\u0119\u011a\u0005\u0013\u0000\u0000\u011a\u011b\u0005\n"+
		"\u0000\u0000\u011b\u011c\u0005/\u0000\u0000\u011c\u011d\u00030\u0018\u0000"+
		"\u011d\u011e\u0005\u0002\u0000\u0000\u011e+\u0001\u0000\u0000\u0000\u011f"+
		"\u013b\u0005\u0016\u0000\u0000\u0120\u013b\u0005\u0017\u0000\u0000\u0121"+
		"\u013b\u0005\u0018\u0000\u0000\u0122\u013b\u0005\u0019\u0000\u0000\u0123"+
		"\u013b\u0005\u001a\u0000\u0000\u0124\u013b\u0005\u001b\u0000\u0000\u0125"+
		"\u013b\u0005\u001c\u0000\u0000\u0126\u013b\u0005\u001d\u0000\u0000\u0127"+
		"\u013b\u0005\u001e\u0000\u0000\u0128\u013b\u0005\u001f\u0000\u0000\u0129"+
		"\u013b\u0005 \u0000\u0000\u012a\u013b\u0005!\u0000\u0000\u012b\u013b\u0005"+
		"\"\u0000\u0000\u012c\u013b\u0005#\u0000\u0000\u012d\u013b\u0005$\u0000"+
		"\u0000\u012e\u013b\u0005%\u0000\u0000\u012f\u013b\u0005&\u0000\u0000\u0130"+
		"\u013b\u0005\'\u0000\u0000\u0131\u013b\u0005(\u0000\u0000\u0132\u013b"+
		"\u0005)\u0000\u0000\u0133\u013b\u0005*\u0000\u0000\u0134\u013b\u0005+"+
		"\u0000\u0000\u0135\u0136\u0005,\u0000\u0000\u0136\u0137\u0003,\u0016\u0000"+
		"\u0137\u0138\u0005-\u0000\u0000\u0138\u013b\u0001\u0000\u0000\u0000\u0139"+
		"\u013b\u0005/\u0000\u0000\u013a\u011f\u0001\u0000\u0000\u0000\u013a\u0120"+
		"\u0001\u0000\u0000\u0000\u013a\u0121\u0001\u0000\u0000\u0000\u013a\u0122"+
		"\u0001\u0000\u0000\u0000\u013a\u0123\u0001\u0000\u0000\u0000\u013a\u0124"+
		"\u0001\u0000\u0000\u0000\u013a\u0125\u0001\u0000\u0000\u0000\u013a\u0126"+
		"\u0001\u0000\u0000\u0000\u013a\u0127\u0001\u0000\u0000\u0000\u013a\u0128"+
		"\u0001\u0000\u0000\u0000\u013a\u0129\u0001\u0000\u0000\u0000\u013a\u012a"+
		"\u0001\u0000\u0000\u0000\u013a\u012b\u0001\u0000\u0000\u0000\u013a\u012c"+
		"\u0001\u0000\u0000\u0000\u013a\u012d\u0001\u0000\u0000\u0000\u013a\u012e"+
		"\u0001\u0000\u0000\u0000\u013a\u012f\u0001\u0000\u0000\u0000\u013a\u0130"+
		"\u0001\u0000\u0000\u0000\u013a\u0131\u0001\u0000\u0000\u0000\u013a\u0132"+
		"\u0001\u0000\u0000\u0000\u013a\u0133\u0001\u0000\u0000\u0000\u013a\u0134"+
		"\u0001\u0000\u0000\u0000\u013a\u0135\u0001\u0000\u0000\u0000\u013a\u0139"+
		"\u0001\u0000\u0000\u0000\u013b-\u0001\u0000\u0000\u0000\u013c\u013f\u0005"+
		"/\u0000\u0000\u013d\u013e\u0005\u0015\u0000\u0000\u013e\u0140\u00050\u0000"+
		"\u0000\u013f\u013d\u0001\u0000\u0000\u0000\u013f\u0140\u0001\u0000\u0000"+
		"\u0000\u0140\u0141\u0001\u0000\u0000\u0000\u0141\u0142\u00030\u0018\u0000"+
		"\u0142/\u0001\u0000\u0000\u0000\u0143\u0144\u0005\u0012\u0000\u0000\u0144"+
		"\u0145\u0003\u0018\f\u0000\u0145\u0146\u0005\u0013\u0000\u0000\u0146\u0148"+
		"\u0001\u0000\u0000\u0000\u0147\u0143\u0001\u0000\u0000\u0000\u0147\u0148"+
		"\u0001\u0000\u0000\u0000\u01481\u0001\u0000\u0000\u0000\u0149\u014a\u0007"+
		"\u0001\u0000\u0000\u014a3\u0001\u0000\u0000\u0000\u014b\u014e\u00032\u0019"+
		"\u0000\u014c\u014e\u00052\u0000\u0000\u014d\u014b\u0001\u0000\u0000\u0000"+
		"\u014d\u014c\u0001\u0000\u0000\u0000\u014e5\u0001\u0000\u0000\u0000\u014f"+
		"\u0156\u00034\u001a\u0000\u0150\u0156\u0003\u0014\n\u0000\u0151\u0152"+
		"\u0005,\u0000\u0000\u0152\u0153\u0003\u001c\u000e\u0000\u0153\u0154\u0005"+
		"-\u0000\u0000\u0154\u0156\u0001\u0000\u0000\u0000\u0155\u014f\u0001\u0000"+
		"\u0000\u0000\u0155\u0150\u0001\u0000\u0000\u0000\u0155\u0151\u0001\u0000"+
		"\u0000\u0000\u01567\u0001\u0000\u0000\u0000\u001e=MOajrz\u0084\u00a1\u00ae"+
		"\u00b1\u00b6\u00bc\u00c0\u00c3\u00ce\u00d1\u00d8\u00db\u00e4\u00e7\u00f1"+
		"\u00f4\u0109\u0110\u013a\u013f\u0147\u014d\u0155";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}