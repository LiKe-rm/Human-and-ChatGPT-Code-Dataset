// Generated from d:\Code\CodePerspective-java\src\main\java\com\hust\antlr\java\JavaParser.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class JavaParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		ABSTRACT=1, ASSERT=2, BOOLEAN=3, BREAK=4, BYTE=5, CASE=6, CATCH=7, CHAR=8, 
		CLASS=9, CONST=10, CONTINUE=11, DEFAULT=12, DO=13, DOUBLE=14, ELSE=15, 
		ENUM=16, EXTENDS=17, FINAL=18, FINALLY=19, FLOAT=20, FOR=21, IF=22, GOTO=23, 
		IMPLEMENTS=24, IMPORT=25, INSTANCEOF=26, INT=27, INTERFACE=28, LONG=29, 
		NATIVE=30, NEW=31, PACKAGE=32, PRIVATE=33, PROTECTED=34, PUBLIC=35, RETURN=36, 
		SHORT=37, STATIC=38, STRICTFP=39, SUPER=40, SWITCH=41, SYNCHRONIZED=42, 
		THIS=43, THROW=44, THROWS=45, TRANSIENT=46, TRY=47, VOID=48, VOLATILE=49, 
		WHILE=50, MODULE=51, OPEN=52, REQUIRES=53, EXPORTS=54, OPENS=55, TO=56, 
		USES=57, PROVIDES=58, WITH=59, TRANSITIVE=60, VAR=61, YIELD=62, RECORD=63, 
		SEALED=64, PERMITS=65, NON_SEALED=66, DECIMAL_LITERAL=67, HEX_LITERAL=68, 
		OCT_LITERAL=69, BINARY_LITERAL=70, FLOAT_LITERAL=71, HEX_FLOAT_LITERAL=72, 
		BOOL_LITERAL=73, CHAR_LITERAL=74, STRING_LITERAL=75, TEXT_BLOCK=76, NULL_LITERAL=77, 
		LPAREN=78, RPAREN=79, LBRACE=80, RBRACE=81, LBRACK=82, RBRACK=83, SEMI=84, 
		COMMA=85, DOT=86, ASSIGN=87, GT=88, LT=89, BANG=90, TILDE=91, QUESTION=92, 
		COLON=93, EQUAL=94, LE=95, GE=96, NOTEQUAL=97, AND=98, OR=99, INC=100, 
		DEC=101, ADD=102, SUB=103, MUL=104, DIV=105, BITAND=106, BITOR=107, CARET=108, 
		MOD=109, ADD_ASSIGN=110, SUB_ASSIGN=111, MUL_ASSIGN=112, DIV_ASSIGN=113, 
		AND_ASSIGN=114, OR_ASSIGN=115, XOR_ASSIGN=116, MOD_ASSIGN=117, LSHIFT_ASSIGN=118, 
		RSHIFT_ASSIGN=119, URSHIFT_ASSIGN=120, ARROW=121, COLONCOLON=122, AT=123, 
		ELLIPSIS=124, WS=125, ENTER=126, COMMENT=127, LINE_COMMENT=128, IDENTIFIER=129;
	public static final int
		RULE_compilationUnit = 0, RULE_packageDeclaration = 1, RULE_importDeclaration = 2, 
		RULE_typeDeclaration = 3, RULE_modifier = 4, RULE_classOrInterfaceModifier = 5, 
		RULE_variableModifier = 6, RULE_classDeclaration = 7, RULE_typeParameters = 8, 
		RULE_typeParameter = 9, RULE_typeBound = 10, RULE_enumDeclaration = 11, 
		RULE_enumConstants = 12, RULE_enumConstant = 13, RULE_enumBodyDeclarations = 14, 
		RULE_interfaceDeclaration = 15, RULE_classBody = 16, RULE_interfaceBody = 17, 
		RULE_classBodyDeclaration = 18, RULE_memberDeclaration = 19, RULE_methodDeclaration = 20, 
		RULE_methodBody = 21, RULE_typeTypeOrVoid = 22, RULE_genericMethodDeclaration = 23, 
		RULE_genericConstructorDeclaration = 24, RULE_constructorDeclaration = 25, 
		RULE_compactConstructorDeclaration = 26, RULE_fieldDeclaration = 27, RULE_interfaceBodyDeclaration = 28, 
		RULE_interfaceMemberDeclaration = 29, RULE_constDeclaration = 30, RULE_constantDeclarator = 31, 
		RULE_interfaceMethodDeclaration = 32, RULE_interfaceMethodModifier = 33, 
		RULE_genericInterfaceMethodDeclaration = 34, RULE_interfaceCommonBodyDeclaration = 35, 
		RULE_variableDeclarators = 36, RULE_variableDeclarator = 37, RULE_variableDeclaratorId = 38, 
		RULE_variableInitializer = 39, RULE_arrayInitializer = 40, RULE_classOrInterfaceType = 41, 
		RULE_typeArgument = 42, RULE_qualifiedNameList = 43, RULE_formalParameters = 44, 
		RULE_receiverParameter = 45, RULE_formalParameterList = 46, RULE_formalParameter = 47, 
		RULE_lastFormalParameter = 48, RULE_lambdaLVTIList = 49, RULE_lambdaLVTIParameter = 50, 
		RULE_qualifiedName = 51, RULE_literal = 52, RULE_integerLiteral = 53, 
		RULE_floatLiteral = 54, RULE_altAnnotationQualifiedName = 55, RULE_annotation = 56, 
		RULE_elementValuePairs = 57, RULE_elementValuePair = 58, RULE_elementValue = 59, 
		RULE_elementValueArrayInitializer = 60, RULE_annotationTypeDeclaration = 61, 
		RULE_annotationTypeBody = 62, RULE_annotationTypeElementDeclaration = 63, 
		RULE_annotationTypeElementRest = 64, RULE_annotationMethodOrConstantRest = 65, 
		RULE_annotationMethodRest = 66, RULE_annotationConstantRest = 67, RULE_defaultValue = 68, 
		RULE_moduleDeclaration = 69, RULE_moduleBody = 70, RULE_moduleDirective = 71, 
		RULE_requiresModifier = 72, RULE_recordDeclaration = 73, RULE_recordHeader = 74, 
		RULE_recordComponentList = 75, RULE_recordComponent = 76, RULE_recordBody = 77, 
		RULE_block = 78, RULE_blockStatement = 79, RULE_localVariableDeclaration = 80, 
		RULE_identifier = 81, RULE_typeIdentifier = 82, RULE_localTypeDeclaration = 83, 
		RULE_statement = 84, RULE_catchClause = 85, RULE_catchType = 86, RULE_finallyBlock = 87, 
		RULE_resourceSpecification = 88, RULE_resources = 89, RULE_resource = 90, 
		RULE_switchBlockStatementGroup = 91, RULE_switchLabel = 92, RULE_forControl = 93, 
		RULE_forInit = 94, RULE_enhancedForControl = 95, RULE_parExpression = 96, 
		RULE_expressionList = 97, RULE_methodCall = 98, RULE_expression = 99, 
		RULE_pattern = 100, RULE_lambdaExpression = 101, RULE_lambdaParameters = 102, 
		RULE_lambdaBody = 103, RULE_primary = 104, RULE_switchExpression = 105, 
		RULE_switchLabeledRule = 106, RULE_guardedPattern = 107, RULE_switchRuleOutcome = 108, 
		RULE_classType = 109, RULE_creator = 110, RULE_createdName = 111, RULE_innerCreator = 112, 
		RULE_arrayCreatorRest = 113, RULE_classCreatorRest = 114, RULE_explicitGenericInvocation = 115, 
		RULE_typeArgumentsOrDiamond = 116, RULE_nonWildcardTypeArgumentsOrDiamond = 117, 
		RULE_nonWildcardTypeArguments = 118, RULE_typeList = 119, RULE_typeType = 120, 
		RULE_primitiveType = 121, RULE_typeArguments = 122, RULE_superSuffix = 123, 
		RULE_explicitGenericInvocationSuffix = 124, RULE_arguments = 125;
	private static String[] makeRuleNames() {
		return new String[] {
			"compilationUnit", "packageDeclaration", "importDeclaration", "typeDeclaration", 
			"modifier", "classOrInterfaceModifier", "variableModifier", "classDeclaration", 
			"typeParameters", "typeParameter", "typeBound", "enumDeclaration", "enumConstants", 
			"enumConstant", "enumBodyDeclarations", "interfaceDeclaration", "classBody", 
			"interfaceBody", "classBodyDeclaration", "memberDeclaration", "methodDeclaration", 
			"methodBody", "typeTypeOrVoid", "genericMethodDeclaration", "genericConstructorDeclaration", 
			"constructorDeclaration", "compactConstructorDeclaration", "fieldDeclaration", 
			"interfaceBodyDeclaration", "interfaceMemberDeclaration", "constDeclaration", 
			"constantDeclarator", "interfaceMethodDeclaration", "interfaceMethodModifier", 
			"genericInterfaceMethodDeclaration", "interfaceCommonBodyDeclaration", 
			"variableDeclarators", "variableDeclarator", "variableDeclaratorId", 
			"variableInitializer", "arrayInitializer", "classOrInterfaceType", "typeArgument", 
			"qualifiedNameList", "formalParameters", "receiverParameter", "formalParameterList", 
			"formalParameter", "lastFormalParameter", "lambdaLVTIList", "lambdaLVTIParameter", 
			"qualifiedName", "literal", "integerLiteral", "floatLiteral", "altAnnotationQualifiedName", 
			"annotation", "elementValuePairs", "elementValuePair", "elementValue", 
			"elementValueArrayInitializer", "annotationTypeDeclaration", "annotationTypeBody", 
			"annotationTypeElementDeclaration", "annotationTypeElementRest", "annotationMethodOrConstantRest", 
			"annotationMethodRest", "annotationConstantRest", "defaultValue", "moduleDeclaration", 
			"moduleBody", "moduleDirective", "requiresModifier", "recordDeclaration", 
			"recordHeader", "recordComponentList", "recordComponent", "recordBody", 
			"block", "blockStatement", "localVariableDeclaration", "identifier", 
			"typeIdentifier", "localTypeDeclaration", "statement", "catchClause", 
			"catchType", "finallyBlock", "resourceSpecification", "resources", "resource", 
			"switchBlockStatementGroup", "switchLabel", "forControl", "forInit", 
			"enhancedForControl", "parExpression", "expressionList", "methodCall", 
			"expression", "pattern", "lambdaExpression", "lambdaParameters", "lambdaBody", 
			"primary", "switchExpression", "switchLabeledRule", "guardedPattern", 
			"switchRuleOutcome", "classType", "creator", "createdName", "innerCreator", 
			"arrayCreatorRest", "classCreatorRest", "explicitGenericInvocation", 
			"typeArgumentsOrDiamond", "nonWildcardTypeArgumentsOrDiamond", "nonWildcardTypeArguments", 
			"typeList", "typeType", "primitiveType", "typeArguments", "superSuffix", 
			"explicitGenericInvocationSuffix", "arguments"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'abstract'", "'assert'", "'boolean'", "'break'", "'byte'", "'case'", 
			"'catch'", "'char'", "'class'", "'const'", "'continue'", "'default'", 
			"'do'", "'double'", "'else'", "'enum'", "'extends'", "'final'", "'finally'", 
			"'float'", "'for'", "'if'", "'goto'", "'implements'", "'import'", "'instanceof'", 
			"'int'", "'interface'", "'long'", "'native'", "'new'", "'package'", "'private'", 
			"'protected'", "'public'", "'return'", "'short'", "'static'", "'strictfp'", 
			"'super'", "'switch'", "'synchronized'", "'this'", "'throw'", "'throws'", 
			"'transient'", "'try'", "'void'", "'volatile'", "'while'", "'module'", 
			"'open'", "'requires'", "'exports'", "'opens'", "'to'", "'uses'", "'provides'", 
			"'with'", "'transitive'", "'var'", "'yield'", "'record'", "'sealed'", 
			"'permits'", "'non-sealed'", null, null, null, null, null, null, null, 
			null, null, null, "'null'", "'('", "')'", "'{'", "'}'", "'['", "']'", 
			"';'", "','", "'.'", "'='", "'>'", "'<'", "'!'", "'~'", "'?'", "':'", 
			"'=='", "'<='", "'>='", "'!='", "'&&'", "'||'", "'++'", "'--'", "'+'", 
			"'-'", "'*'", "'/'", "'&'", "'|'", "'^'", "'%'", "'+='", "'-='", "'*='", 
			"'/='", "'&='", "'|='", "'^='", "'%='", "'<<='", "'>>='", "'>>>='", "'->'", 
			"'::'", "'@'", "'...'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "ABSTRACT", "ASSERT", "BOOLEAN", "BREAK", "BYTE", "CASE", "CATCH", 
			"CHAR", "CLASS", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE", 
			"ENUM", "EXTENDS", "FINAL", "FINALLY", "FLOAT", "FOR", "IF", "GOTO", 
			"IMPLEMENTS", "IMPORT", "INSTANCEOF", "INT", "INTERFACE", "LONG", "NATIVE", 
			"NEW", "PACKAGE", "PRIVATE", "PROTECTED", "PUBLIC", "RETURN", "SHORT", 
			"STATIC", "STRICTFP", "SUPER", "SWITCH", "SYNCHRONIZED", "THIS", "THROW", 
			"THROWS", "TRANSIENT", "TRY", "VOID", "VOLATILE", "WHILE", "MODULE", 
			"OPEN", "REQUIRES", "EXPORTS", "OPENS", "TO", "USES", "PROVIDES", "WITH", 
			"TRANSITIVE", "VAR", "YIELD", "RECORD", "SEALED", "PERMITS", "NON_SEALED", 
			"DECIMAL_LITERAL", "HEX_LITERAL", "OCT_LITERAL", "BINARY_LITERAL", "FLOAT_LITERAL", 
			"HEX_FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", 
			"TEXT_BLOCK", "NULL_LITERAL", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
			"LBRACK", "RBRACK", "SEMI", "COMMA", "DOT", "ASSIGN", "GT", "LT", "BANG", 
			"TILDE", "QUESTION", "COLON", "EQUAL", "LE", "GE", "NOTEQUAL", "AND", 
			"OR", "INC", "DEC", "ADD", "SUB", "MUL", "DIV", "BITAND", "BITOR", "CARET", 
			"MOD", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "AND_ASSIGN", 
			"OR_ASSIGN", "XOR_ASSIGN", "MOD_ASSIGN", "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", 
			"URSHIFT_ASSIGN", "ARROW", "COLONCOLON", "AT", "ELLIPSIS", "WS", "ENTER", 
			"COMMENT", "LINE_COMMENT", "IDENTIFIER"
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
	public String getGrammarFileName() { return "JavaParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public JavaParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class CompilationUnitContext extends ParserRuleContext {
		public PackageDeclarationContext packageDeclaration() {
			return getRuleContext(PackageDeclarationContext.class,0);
		}
		public List<ImportDeclarationContext> importDeclaration() {
			return getRuleContexts(ImportDeclarationContext.class);
		}
		public ImportDeclarationContext importDeclaration(int i) {
			return getRuleContext(ImportDeclarationContext.class,i);
		}
		public List<TypeDeclarationContext> typeDeclaration() {
			return getRuleContexts(TypeDeclarationContext.class);
		}
		public TypeDeclarationContext typeDeclaration(int i) {
			return getRuleContext(TypeDeclarationContext.class,i);
		}
		public ModuleDeclarationContext moduleDeclaration() {
			return getRuleContext(ModuleDeclarationContext.class,0);
		}
		public TerminalNode EOF() { return getToken(JavaParser.EOF, 0); }
		public CompilationUnitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compilationUnit; }
	}

	public final CompilationUnitContext compilationUnit() throws RecognitionException {
		CompilationUnitContext _localctx = new CompilationUnitContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_compilationUnit);
		int _la;
		try {
			setState(270);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(253);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
				case 1:
					{
					setState(252);
					packageDeclaration();
					}
					break;
				}
				setState(258);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==IMPORT) {
					{
					{
					setState(255);
					importDeclaration();
					}
					}
					setState(260);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(264);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << CLASS) | (1L << ENUM) | (1L << FINAL) | (1L << INTERFACE) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << STATIC) | (1L << STRICTFP) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (SEMI - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
					{
					{
					setState(261);
					typeDeclaration();
					}
					}
					setState(266);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(267);
				moduleDeclaration();
				setState(268);
				match(EOF);
				}
				break;
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

	public static class PackageDeclarationContext extends ParserRuleContext {
		public TerminalNode PACKAGE() { return getToken(JavaParser.PACKAGE, 0); }
		public QualifiedNameContext qualifiedName() {
			return getRuleContext(QualifiedNameContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public PackageDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_packageDeclaration; }
	}

	public final PackageDeclarationContext packageDeclaration() throws RecognitionException {
		PackageDeclarationContext _localctx = new PackageDeclarationContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_packageDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(275);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==AT || _la==IDENTIFIER) {
				{
				{
				setState(272);
				annotation();
				}
				}
				setState(277);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(278);
			match(PACKAGE);
			setState(279);
			qualifiedName();
			setState(280);
			match(SEMI);
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

	public static class ImportDeclarationContext extends ParserRuleContext {
		public TerminalNode IMPORT() { return getToken(JavaParser.IMPORT, 0); }
		public QualifiedNameContext qualifiedName() {
			return getRuleContext(QualifiedNameContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public TerminalNode STATIC() { return getToken(JavaParser.STATIC, 0); }
		public TerminalNode DOT() { return getToken(JavaParser.DOT, 0); }
		public TerminalNode MUL() { return getToken(JavaParser.MUL, 0); }
		public ImportDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_importDeclaration; }
	}

	public final ImportDeclarationContext importDeclaration() throws RecognitionException {
		ImportDeclarationContext _localctx = new ImportDeclarationContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_importDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(282);
			match(IMPORT);
			setState(284);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==STATIC) {
				{
				setState(283);
				match(STATIC);
				}
			}

			setState(286);
			qualifiedName();
			setState(289);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==DOT) {
				{
				setState(287);
				match(DOT);
				setState(288);
				match(MUL);
				}
			}

			setState(291);
			match(SEMI);
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

	public static class TypeDeclarationContext extends ParserRuleContext {
		public ClassDeclarationContext classDeclaration() {
			return getRuleContext(ClassDeclarationContext.class,0);
		}
		public EnumDeclarationContext enumDeclaration() {
			return getRuleContext(EnumDeclarationContext.class,0);
		}
		public InterfaceDeclarationContext interfaceDeclaration() {
			return getRuleContext(InterfaceDeclarationContext.class,0);
		}
		public AnnotationTypeDeclarationContext annotationTypeDeclaration() {
			return getRuleContext(AnnotationTypeDeclarationContext.class,0);
		}
		public RecordDeclarationContext recordDeclaration() {
			return getRuleContext(RecordDeclarationContext.class,0);
		}
		public List<ClassOrInterfaceModifierContext> classOrInterfaceModifier() {
			return getRuleContexts(ClassOrInterfaceModifierContext.class);
		}
		public ClassOrInterfaceModifierContext classOrInterfaceModifier(int i) {
			return getRuleContext(ClassOrInterfaceModifierContext.class,i);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public TypeDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeDeclaration; }
	}

	public final TypeDeclarationContext typeDeclaration() throws RecognitionException {
		TypeDeclarationContext _localctx = new TypeDeclarationContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_typeDeclaration);
		try {
			int _alt;
			setState(307);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case ABSTRACT:
			case CLASS:
			case ENUM:
			case FINAL:
			case INTERFACE:
			case PRIVATE:
			case PROTECTED:
			case PUBLIC:
			case STATIC:
			case STRICTFP:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case NON_SEALED:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(296);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,7,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(293);
						classOrInterfaceModifier();
						}
						} 
					}
					setState(298);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,7,_ctx);
				}
				setState(304);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case CLASS:
					{
					setState(299);
					classDeclaration();
					}
					break;
				case ENUM:
					{
					setState(300);
					enumDeclaration();
					}
					break;
				case INTERFACE:
					{
					setState(301);
					interfaceDeclaration();
					}
					break;
				case AT:
					{
					setState(302);
					annotationTypeDeclaration();
					}
					break;
				case RECORD:
					{
					setState(303);
					recordDeclaration();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				break;
			case SEMI:
				enterOuterAlt(_localctx, 2);
				{
				setState(306);
				match(SEMI);
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

	public static class ModifierContext extends ParserRuleContext {
		public ClassOrInterfaceModifierContext classOrInterfaceModifier() {
			return getRuleContext(ClassOrInterfaceModifierContext.class,0);
		}
		public TerminalNode NATIVE() { return getToken(JavaParser.NATIVE, 0); }
		public TerminalNode SYNCHRONIZED() { return getToken(JavaParser.SYNCHRONIZED, 0); }
		public TerminalNode TRANSIENT() { return getToken(JavaParser.TRANSIENT, 0); }
		public TerminalNode VOLATILE() { return getToken(JavaParser.VOLATILE, 0); }
		public ModifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_modifier; }
	}

	public final ModifierContext modifier() throws RecognitionException {
		ModifierContext _localctx = new ModifierContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_modifier);
		try {
			setState(314);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case ABSTRACT:
			case FINAL:
			case PRIVATE:
			case PROTECTED:
			case PUBLIC:
			case STATIC:
			case STRICTFP:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case NON_SEALED:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(309);
				classOrInterfaceModifier();
				}
				break;
			case NATIVE:
				enterOuterAlt(_localctx, 2);
				{
				setState(310);
				match(NATIVE);
				}
				break;
			case SYNCHRONIZED:
				enterOuterAlt(_localctx, 3);
				{
				setState(311);
				match(SYNCHRONIZED);
				}
				break;
			case TRANSIENT:
				enterOuterAlt(_localctx, 4);
				{
				setState(312);
				match(TRANSIENT);
				}
				break;
			case VOLATILE:
				enterOuterAlt(_localctx, 5);
				{
				setState(313);
				match(VOLATILE);
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

	public static class ClassOrInterfaceModifierContext extends ParserRuleContext {
		public AnnotationContext annotation() {
			return getRuleContext(AnnotationContext.class,0);
		}
		public TerminalNode PUBLIC() { return getToken(JavaParser.PUBLIC, 0); }
		public TerminalNode PROTECTED() { return getToken(JavaParser.PROTECTED, 0); }
		public TerminalNode PRIVATE() { return getToken(JavaParser.PRIVATE, 0); }
		public TerminalNode STATIC() { return getToken(JavaParser.STATIC, 0); }
		public TerminalNode ABSTRACT() { return getToken(JavaParser.ABSTRACT, 0); }
		public TerminalNode FINAL() { return getToken(JavaParser.FINAL, 0); }
		public TerminalNode STRICTFP() { return getToken(JavaParser.STRICTFP, 0); }
		public TerminalNode SEALED() { return getToken(JavaParser.SEALED, 0); }
		public TerminalNode NON_SEALED() { return getToken(JavaParser.NON_SEALED, 0); }
		public ClassOrInterfaceModifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classOrInterfaceModifier; }
	}

	public final ClassOrInterfaceModifierContext classOrInterfaceModifier() throws RecognitionException {
		ClassOrInterfaceModifierContext _localctx = new ClassOrInterfaceModifierContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_classOrInterfaceModifier);
		try {
			setState(326);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(316);
				annotation();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(317);
				match(PUBLIC);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(318);
				match(PROTECTED);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(319);
				match(PRIVATE);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(320);
				match(STATIC);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(321);
				match(ABSTRACT);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(322);
				match(FINAL);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(323);
				match(STRICTFP);
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(324);
				match(SEALED);
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(325);
				match(NON_SEALED);
				}
				break;
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

	public static class VariableModifierContext extends ParserRuleContext {
		public TerminalNode FINAL() { return getToken(JavaParser.FINAL, 0); }
		public AnnotationContext annotation() {
			return getRuleContext(AnnotationContext.class,0);
		}
		public VariableModifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableModifier; }
	}

	public final VariableModifierContext variableModifier() throws RecognitionException {
		VariableModifierContext _localctx = new VariableModifierContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_variableModifier);
		try {
			setState(330);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case FINAL:
				enterOuterAlt(_localctx, 1);
				{
				setState(328);
				match(FINAL);
				}
				break;
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				setState(329);
				annotation();
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

	public static class ClassDeclarationContext extends ParserRuleContext {
		public TerminalNode CLASS() { return getToken(JavaParser.CLASS, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public ClassBodyContext classBody() {
			return getRuleContext(ClassBodyContext.class,0);
		}
		public TypeParametersContext typeParameters() {
			return getRuleContext(TypeParametersContext.class,0);
		}
		public TerminalNode EXTENDS() { return getToken(JavaParser.EXTENDS, 0); }
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public TerminalNode IMPLEMENTS() { return getToken(JavaParser.IMPLEMENTS, 0); }
		public List<TypeListContext> typeList() {
			return getRuleContexts(TypeListContext.class);
		}
		public TypeListContext typeList(int i) {
			return getRuleContext(TypeListContext.class,i);
		}
		public TerminalNode PERMITS() { return getToken(JavaParser.PERMITS, 0); }
		public ClassDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classDeclaration; }
	}

	public final ClassDeclarationContext classDeclaration() throws RecognitionException {
		ClassDeclarationContext _localctx = new ClassDeclarationContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_classDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(332);
			match(CLASS);
			setState(333);
			identifier();
			setState(335);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LT) {
				{
				setState(334);
				typeParameters();
				}
			}

			setState(339);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==EXTENDS) {
				{
				setState(337);
				match(EXTENDS);
				setState(338);
				typeType();
				}
			}

			setState(343);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IMPLEMENTS) {
				{
				setState(341);
				match(IMPLEMENTS);
				setState(342);
				typeList();
				}
			}

			setState(347);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==PERMITS) {
				{
				setState(345);
				match(PERMITS);
				setState(346);
				typeList();
				}
			}

			setState(349);
			classBody();
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

	public static class TypeParametersContext extends ParserRuleContext {
		public TerminalNode LT() { return getToken(JavaParser.LT, 0); }
		public List<TypeParameterContext> typeParameter() {
			return getRuleContexts(TypeParameterContext.class);
		}
		public TypeParameterContext typeParameter(int i) {
			return getRuleContext(TypeParameterContext.class,i);
		}
		public TerminalNode GT() { return getToken(JavaParser.GT, 0); }
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public TypeParametersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeParameters; }
	}

	public final TypeParametersContext typeParameters() throws RecognitionException {
		TypeParametersContext _localctx = new TypeParametersContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_typeParameters);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(351);
			match(LT);
			setState(352);
			typeParameter();
			setState(357);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(353);
				match(COMMA);
				setState(354);
				typeParameter();
				}
				}
				setState(359);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(360);
			match(GT);
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

	public static class TypeParameterContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public TerminalNode EXTENDS() { return getToken(JavaParser.EXTENDS, 0); }
		public TypeBoundContext typeBound() {
			return getRuleContext(TypeBoundContext.class,0);
		}
		public TypeParameterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeParameter; }
	}

	public final TypeParameterContext typeParameter() throws RecognitionException {
		TypeParameterContext _localctx = new TypeParameterContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_typeParameter);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(365);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,18,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(362);
					annotation();
					}
					} 
				}
				setState(367);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,18,_ctx);
			}
			setState(368);
			identifier();
			setState(377);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==EXTENDS) {
				{
				setState(369);
				match(EXTENDS);
				setState(373);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,19,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(370);
						annotation();
						}
						} 
					}
					setState(375);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,19,_ctx);
				}
				setState(376);
				typeBound();
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

	public static class TypeBoundContext extends ParserRuleContext {
		public List<TypeTypeContext> typeType() {
			return getRuleContexts(TypeTypeContext.class);
		}
		public TypeTypeContext typeType(int i) {
			return getRuleContext(TypeTypeContext.class,i);
		}
		public List<TerminalNode> BITAND() { return getTokens(JavaParser.BITAND); }
		public TerminalNode BITAND(int i) {
			return getToken(JavaParser.BITAND, i);
		}
		public TypeBoundContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeBound; }
	}

	public final TypeBoundContext typeBound() throws RecognitionException {
		TypeBoundContext _localctx = new TypeBoundContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_typeBound);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(379);
			typeType();
			setState(384);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==BITAND) {
				{
				{
				setState(380);
				match(BITAND);
				setState(381);
				typeType();
				}
				}
				setState(386);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class EnumDeclarationContext extends ParserRuleContext {
		public TerminalNode ENUM() { return getToken(JavaParser.ENUM, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public TerminalNode IMPLEMENTS() { return getToken(JavaParser.IMPLEMENTS, 0); }
		public TypeListContext typeList() {
			return getRuleContext(TypeListContext.class,0);
		}
		public EnumConstantsContext enumConstants() {
			return getRuleContext(EnumConstantsContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(JavaParser.COMMA, 0); }
		public EnumBodyDeclarationsContext enumBodyDeclarations() {
			return getRuleContext(EnumBodyDeclarationsContext.class,0);
		}
		public EnumDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enumDeclaration; }
	}

	public final EnumDeclarationContext enumDeclaration() throws RecognitionException {
		EnumDeclarationContext _localctx = new EnumDeclarationContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_enumDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(387);
			match(ENUM);
			setState(388);
			identifier();
			setState(391);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IMPLEMENTS) {
				{
				setState(389);
				match(IMPLEMENTS);
				setState(390);
				typeList();
				}
			}

			setState(393);
			match(LBRACE);
			setState(395);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==AT || _la==IDENTIFIER) {
				{
				setState(394);
				enumConstants();
				}
			}

			setState(398);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COMMA) {
				{
				setState(397);
				match(COMMA);
				}
			}

			setState(401);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SEMI) {
				{
				setState(400);
				enumBodyDeclarations();
				}
			}

			setState(403);
			match(RBRACE);
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

	public static class EnumConstantsContext extends ParserRuleContext {
		public List<EnumConstantContext> enumConstant() {
			return getRuleContexts(EnumConstantContext.class);
		}
		public EnumConstantContext enumConstant(int i) {
			return getRuleContext(EnumConstantContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public EnumConstantsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enumConstants; }
	}

	public final EnumConstantsContext enumConstants() throws RecognitionException {
		EnumConstantsContext _localctx = new EnumConstantsContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_enumConstants);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(405);
			enumConstant();
			setState(410);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,26,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(406);
					match(COMMA);
					setState(407);
					enumConstant();
					}
					} 
				}
				setState(412);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,26,_ctx);
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

	public static class EnumConstantContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public ClassBodyContext classBody() {
			return getRuleContext(ClassBodyContext.class,0);
		}
		public EnumConstantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enumConstant; }
	}

	public final EnumConstantContext enumConstant() throws RecognitionException {
		EnumConstantContext _localctx = new EnumConstantContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_enumConstant);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(416);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,27,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(413);
					annotation();
					}
					} 
				}
				setState(418);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,27,_ctx);
			}
			setState(419);
			identifier();
			setState(421);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LPAREN) {
				{
				setState(420);
				arguments();
				}
			}

			setState(424);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LBRACE) {
				{
				setState(423);
				classBody();
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

	public static class EnumBodyDeclarationsContext extends ParserRuleContext {
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public List<ClassBodyDeclarationContext> classBodyDeclaration() {
			return getRuleContexts(ClassBodyDeclarationContext.class);
		}
		public ClassBodyDeclarationContext classBodyDeclaration(int i) {
			return getRuleContext(ClassBodyDeclarationContext.class,i);
		}
		public EnumBodyDeclarationsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enumBodyDeclarations; }
	}

	public final EnumBodyDeclarationsContext enumBodyDeclarations() throws RecognitionException {
		EnumBodyDeclarationsContext _localctx = new EnumBodyDeclarationsContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_enumBodyDeclarations);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(426);
			match(SEMI);
			setState(430);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << BOOLEAN) | (1L << BYTE) | (1L << CHAR) | (1L << CLASS) | (1L << DOUBLE) | (1L << ENUM) | (1L << FINAL) | (1L << FLOAT) | (1L << INT) | (1L << INTERFACE) | (1L << LONG) | (1L << NATIVE) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << SHORT) | (1L << STATIC) | (1L << STRICTFP) | (1L << SYNCHRONIZED) | (1L << TRANSIENT) | (1L << VOID) | (1L << VOLATILE) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (LBRACE - 64)) | (1L << (SEMI - 64)) | (1L << (LT - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
				{
				{
				setState(427);
				classBodyDeclaration();
				}
				}
				setState(432);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class InterfaceDeclarationContext extends ParserRuleContext {
		public TerminalNode INTERFACE() { return getToken(JavaParser.INTERFACE, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public InterfaceBodyContext interfaceBody() {
			return getRuleContext(InterfaceBodyContext.class,0);
		}
		public TypeParametersContext typeParameters() {
			return getRuleContext(TypeParametersContext.class,0);
		}
		public TerminalNode EXTENDS() { return getToken(JavaParser.EXTENDS, 0); }
		public List<TypeListContext> typeList() {
			return getRuleContexts(TypeListContext.class);
		}
		public TypeListContext typeList(int i) {
			return getRuleContext(TypeListContext.class,i);
		}
		public TerminalNode PERMITS() { return getToken(JavaParser.PERMITS, 0); }
		public InterfaceDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interfaceDeclaration; }
	}

	public final InterfaceDeclarationContext interfaceDeclaration() throws RecognitionException {
		InterfaceDeclarationContext _localctx = new InterfaceDeclarationContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_interfaceDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(433);
			match(INTERFACE);
			setState(434);
			identifier();
			setState(436);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LT) {
				{
				setState(435);
				typeParameters();
				}
			}

			setState(440);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==EXTENDS) {
				{
				setState(438);
				match(EXTENDS);
				setState(439);
				typeList();
				}
			}

			setState(444);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==PERMITS) {
				{
				setState(442);
				match(PERMITS);
				setState(443);
				typeList();
				}
			}

			setState(446);
			interfaceBody();
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

	public static class ClassBodyContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<ClassBodyDeclarationContext> classBodyDeclaration() {
			return getRuleContexts(ClassBodyDeclarationContext.class);
		}
		public ClassBodyDeclarationContext classBodyDeclaration(int i) {
			return getRuleContext(ClassBodyDeclarationContext.class,i);
		}
		public ClassBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classBody; }
	}

	public final ClassBodyContext classBody() throws RecognitionException {
		ClassBodyContext _localctx = new ClassBodyContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_classBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(448);
			match(LBRACE);
			setState(452);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << BOOLEAN) | (1L << BYTE) | (1L << CHAR) | (1L << CLASS) | (1L << DOUBLE) | (1L << ENUM) | (1L << FINAL) | (1L << FLOAT) | (1L << INT) | (1L << INTERFACE) | (1L << LONG) | (1L << NATIVE) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << SHORT) | (1L << STATIC) | (1L << STRICTFP) | (1L << SYNCHRONIZED) | (1L << TRANSIENT) | (1L << VOID) | (1L << VOLATILE) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (LBRACE - 64)) | (1L << (SEMI - 64)) | (1L << (LT - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
				{
				{
				setState(449);
				classBodyDeclaration();
				}
				}
				setState(454);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(455);
			match(RBRACE);
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

	public static class InterfaceBodyContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<InterfaceBodyDeclarationContext> interfaceBodyDeclaration() {
			return getRuleContexts(InterfaceBodyDeclarationContext.class);
		}
		public InterfaceBodyDeclarationContext interfaceBodyDeclaration(int i) {
			return getRuleContext(InterfaceBodyDeclarationContext.class,i);
		}
		public InterfaceBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interfaceBody; }
	}

	public final InterfaceBodyContext interfaceBody() throws RecognitionException {
		InterfaceBodyContext _localctx = new InterfaceBodyContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_interfaceBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(457);
			match(LBRACE);
			setState(461);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << BOOLEAN) | (1L << BYTE) | (1L << CHAR) | (1L << CLASS) | (1L << DEFAULT) | (1L << DOUBLE) | (1L << ENUM) | (1L << FINAL) | (1L << FLOAT) | (1L << INT) | (1L << INTERFACE) | (1L << LONG) | (1L << NATIVE) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << SHORT) | (1L << STATIC) | (1L << STRICTFP) | (1L << SYNCHRONIZED) | (1L << TRANSIENT) | (1L << VOID) | (1L << VOLATILE) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (SEMI - 64)) | (1L << (LT - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
				{
				{
				setState(458);
				interfaceBodyDeclaration();
				}
				}
				setState(463);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(464);
			match(RBRACE);
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

	public static class ClassBodyDeclarationContext extends ParserRuleContext {
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode STATIC() { return getToken(JavaParser.STATIC, 0); }
		public MemberDeclarationContext memberDeclaration() {
			return getRuleContext(MemberDeclarationContext.class,0);
		}
		public List<ModifierContext> modifier() {
			return getRuleContexts(ModifierContext.class);
		}
		public ModifierContext modifier(int i) {
			return getRuleContext(ModifierContext.class,i);
		}
		public ClassBodyDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classBodyDeclaration; }
	}

	public final ClassBodyDeclarationContext classBodyDeclaration() throws RecognitionException {
		ClassBodyDeclarationContext _localctx = new ClassBodyDeclarationContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_classBodyDeclaration);
		int _la;
		try {
			int _alt;
			setState(478);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,38,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(466);
				match(SEMI);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(468);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==STATIC) {
					{
					setState(467);
					match(STATIC);
					}
				}

				setState(470);
				block();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(474);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,37,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(471);
						modifier();
						}
						} 
					}
					setState(476);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,37,_ctx);
				}
				setState(477);
				memberDeclaration();
				}
				break;
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

	public static class MemberDeclarationContext extends ParserRuleContext {
		public RecordDeclarationContext recordDeclaration() {
			return getRuleContext(RecordDeclarationContext.class,0);
		}
		public MethodDeclarationContext methodDeclaration() {
			return getRuleContext(MethodDeclarationContext.class,0);
		}
		public GenericMethodDeclarationContext genericMethodDeclaration() {
			return getRuleContext(GenericMethodDeclarationContext.class,0);
		}
		public FieldDeclarationContext fieldDeclaration() {
			return getRuleContext(FieldDeclarationContext.class,0);
		}
		public ConstructorDeclarationContext constructorDeclaration() {
			return getRuleContext(ConstructorDeclarationContext.class,0);
		}
		public GenericConstructorDeclarationContext genericConstructorDeclaration() {
			return getRuleContext(GenericConstructorDeclarationContext.class,0);
		}
		public InterfaceDeclarationContext interfaceDeclaration() {
			return getRuleContext(InterfaceDeclarationContext.class,0);
		}
		public AnnotationTypeDeclarationContext annotationTypeDeclaration() {
			return getRuleContext(AnnotationTypeDeclarationContext.class,0);
		}
		public ClassDeclarationContext classDeclaration() {
			return getRuleContext(ClassDeclarationContext.class,0);
		}
		public EnumDeclarationContext enumDeclaration() {
			return getRuleContext(EnumDeclarationContext.class,0);
		}
		public MemberDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_memberDeclaration; }
	}

	public final MemberDeclarationContext memberDeclaration() throws RecognitionException {
		MemberDeclarationContext _localctx = new MemberDeclarationContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_memberDeclaration);
		try {
			setState(490);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,39,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(480);
				recordDeclaration();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(481);
				methodDeclaration();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(482);
				genericMethodDeclaration();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(483);
				fieldDeclaration();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(484);
				constructorDeclaration();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(485);
				genericConstructorDeclaration();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(486);
				interfaceDeclaration();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(487);
				annotationTypeDeclaration();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(488);
				classDeclaration();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(489);
				enumDeclaration();
				}
				break;
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

	public static class MethodDeclarationContext extends ParserRuleContext {
		public TypeTypeOrVoidContext typeTypeOrVoid() {
			return getRuleContext(TypeTypeOrVoidContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public FormalParametersContext formalParameters() {
			return getRuleContext(FormalParametersContext.class,0);
		}
		public MethodBodyContext methodBody() {
			return getRuleContext(MethodBodyContext.class,0);
		}
		public List<TerminalNode> LBRACK() { return getTokens(JavaParser.LBRACK); }
		public TerminalNode LBRACK(int i) {
			return getToken(JavaParser.LBRACK, i);
		}
		public List<TerminalNode> RBRACK() { return getTokens(JavaParser.RBRACK); }
		public TerminalNode RBRACK(int i) {
			return getToken(JavaParser.RBRACK, i);
		}
		public TerminalNode THROWS() { return getToken(JavaParser.THROWS, 0); }
		public QualifiedNameListContext qualifiedNameList() {
			return getRuleContext(QualifiedNameListContext.class,0);
		}
		public MethodDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_methodDeclaration; }
	}

	public final MethodDeclarationContext methodDeclaration() throws RecognitionException {
		MethodDeclarationContext _localctx = new MethodDeclarationContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_methodDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(492);
			typeTypeOrVoid();
			setState(493);
			identifier();
			setState(494);
			formalParameters();
			setState(499);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==LBRACK) {
				{
				{
				setState(495);
				match(LBRACK);
				setState(496);
				match(RBRACK);
				}
				}
				setState(501);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(504);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==THROWS) {
				{
				setState(502);
				match(THROWS);
				setState(503);
				qualifiedNameList();
				}
			}

			setState(506);
			methodBody();
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

	public static class MethodBodyContext extends ParserRuleContext {
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public MethodBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_methodBody; }
	}

	public final MethodBodyContext methodBody() throws RecognitionException {
		MethodBodyContext _localctx = new MethodBodyContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_methodBody);
		try {
			setState(510);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LBRACE:
				enterOuterAlt(_localctx, 1);
				{
				setState(508);
				block();
				}
				break;
			case SEMI:
				enterOuterAlt(_localctx, 2);
				{
				setState(509);
				match(SEMI);
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

	public static class TypeTypeOrVoidContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public TerminalNode VOID() { return getToken(JavaParser.VOID, 0); }
		public TypeTypeOrVoidContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeTypeOrVoid; }
	}

	public final TypeTypeOrVoidContext typeTypeOrVoid() throws RecognitionException {
		TypeTypeOrVoidContext _localctx = new TypeTypeOrVoidContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_typeTypeOrVoid);
		try {
			setState(514);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case DOUBLE:
			case FLOAT:
			case INT:
			case LONG:
			case SHORT:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(512);
				typeType();
				}
				break;
			case VOID:
				enterOuterAlt(_localctx, 2);
				{
				setState(513);
				match(VOID);
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

	public static class GenericMethodDeclarationContext extends ParserRuleContext {
		public TypeParametersContext typeParameters() {
			return getRuleContext(TypeParametersContext.class,0);
		}
		public MethodDeclarationContext methodDeclaration() {
			return getRuleContext(MethodDeclarationContext.class,0);
		}
		public GenericMethodDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_genericMethodDeclaration; }
	}

	public final GenericMethodDeclarationContext genericMethodDeclaration() throws RecognitionException {
		GenericMethodDeclarationContext _localctx = new GenericMethodDeclarationContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_genericMethodDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(516);
			typeParameters();
			setState(517);
			methodDeclaration();
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

	public static class GenericConstructorDeclarationContext extends ParserRuleContext {
		public TypeParametersContext typeParameters() {
			return getRuleContext(TypeParametersContext.class,0);
		}
		public ConstructorDeclarationContext constructorDeclaration() {
			return getRuleContext(ConstructorDeclarationContext.class,0);
		}
		public GenericConstructorDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_genericConstructorDeclaration; }
	}

	public final GenericConstructorDeclarationContext genericConstructorDeclaration() throws RecognitionException {
		GenericConstructorDeclarationContext _localctx = new GenericConstructorDeclarationContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_genericConstructorDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(519);
			typeParameters();
			setState(520);
			constructorDeclaration();
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

	public static class ConstructorDeclarationContext extends ParserRuleContext {
		public BlockContext constructorBody;
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public FormalParametersContext formalParameters() {
			return getRuleContext(FormalParametersContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode THROWS() { return getToken(JavaParser.THROWS, 0); }
		public QualifiedNameListContext qualifiedNameList() {
			return getRuleContext(QualifiedNameListContext.class,0);
		}
		public ConstructorDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constructorDeclaration; }
	}

	public final ConstructorDeclarationContext constructorDeclaration() throws RecognitionException {
		ConstructorDeclarationContext _localctx = new ConstructorDeclarationContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_constructorDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(522);
			identifier();
			setState(523);
			formalParameters();
			setState(526);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==THROWS) {
				{
				setState(524);
				match(THROWS);
				setState(525);
				qualifiedNameList();
				}
			}

			setState(528);
			((ConstructorDeclarationContext)_localctx).constructorBody = block();
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

	public static class CompactConstructorDeclarationContext extends ParserRuleContext {
		public BlockContext constructorBody;
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public List<ModifierContext> modifier() {
			return getRuleContexts(ModifierContext.class);
		}
		public ModifierContext modifier(int i) {
			return getRuleContext(ModifierContext.class,i);
		}
		public CompactConstructorDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compactConstructorDeclaration; }
	}

	public final CompactConstructorDeclarationContext compactConstructorDeclaration() throws RecognitionException {
		CompactConstructorDeclarationContext _localctx = new CompactConstructorDeclarationContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_compactConstructorDeclaration);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(533);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,45,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(530);
					modifier();
					}
					} 
				}
				setState(535);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,45,_ctx);
			}
			setState(536);
			identifier();
			setState(537);
			((CompactConstructorDeclarationContext)_localctx).constructorBody = block();
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

	public static class FieldDeclarationContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public VariableDeclaratorsContext variableDeclarators() {
			return getRuleContext(VariableDeclaratorsContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public FieldDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fieldDeclaration; }
	}

	public final FieldDeclarationContext fieldDeclaration() throws RecognitionException {
		FieldDeclarationContext _localctx = new FieldDeclarationContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_fieldDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(539);
			typeType();
			setState(540);
			variableDeclarators();
			setState(541);
			match(SEMI);
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

	public static class InterfaceBodyDeclarationContext extends ParserRuleContext {
		public InterfaceMemberDeclarationContext interfaceMemberDeclaration() {
			return getRuleContext(InterfaceMemberDeclarationContext.class,0);
		}
		public List<ModifierContext> modifier() {
			return getRuleContexts(ModifierContext.class);
		}
		public ModifierContext modifier(int i) {
			return getRuleContext(ModifierContext.class,i);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public InterfaceBodyDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interfaceBodyDeclaration; }
	}

	public final InterfaceBodyDeclarationContext interfaceBodyDeclaration() throws RecognitionException {
		InterfaceBodyDeclarationContext _localctx = new InterfaceBodyDeclarationContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_interfaceBodyDeclaration);
		try {
			int _alt;
			setState(551);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case ABSTRACT:
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case CLASS:
			case DEFAULT:
			case DOUBLE:
			case ENUM:
			case FINAL:
			case FLOAT:
			case INT:
			case INTERFACE:
			case LONG:
			case NATIVE:
			case PRIVATE:
			case PROTECTED:
			case PUBLIC:
			case SHORT:
			case STATIC:
			case STRICTFP:
			case SYNCHRONIZED:
			case TRANSIENT:
			case VOID:
			case VOLATILE:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case NON_SEALED:
			case LT:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(546);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,46,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(543);
						modifier();
						}
						} 
					}
					setState(548);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,46,_ctx);
				}
				setState(549);
				interfaceMemberDeclaration();
				}
				break;
			case SEMI:
				enterOuterAlt(_localctx, 2);
				{
				setState(550);
				match(SEMI);
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

	public static class InterfaceMemberDeclarationContext extends ParserRuleContext {
		public ConstDeclarationContext constDeclaration() {
			return getRuleContext(ConstDeclarationContext.class,0);
		}
		public InterfaceMethodDeclarationContext interfaceMethodDeclaration() {
			return getRuleContext(InterfaceMethodDeclarationContext.class,0);
		}
		public GenericInterfaceMethodDeclarationContext genericInterfaceMethodDeclaration() {
			return getRuleContext(GenericInterfaceMethodDeclarationContext.class,0);
		}
		public InterfaceDeclarationContext interfaceDeclaration() {
			return getRuleContext(InterfaceDeclarationContext.class,0);
		}
		public AnnotationTypeDeclarationContext annotationTypeDeclaration() {
			return getRuleContext(AnnotationTypeDeclarationContext.class,0);
		}
		public ClassDeclarationContext classDeclaration() {
			return getRuleContext(ClassDeclarationContext.class,0);
		}
		public EnumDeclarationContext enumDeclaration() {
			return getRuleContext(EnumDeclarationContext.class,0);
		}
		public RecordDeclarationContext recordDeclaration() {
			return getRuleContext(RecordDeclarationContext.class,0);
		}
		public InterfaceMemberDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interfaceMemberDeclaration; }
	}

	public final InterfaceMemberDeclarationContext interfaceMemberDeclaration() throws RecognitionException {
		InterfaceMemberDeclarationContext _localctx = new InterfaceMemberDeclarationContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_interfaceMemberDeclaration);
		try {
			setState(561);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,48,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(553);
				constDeclaration();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(554);
				interfaceMethodDeclaration();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(555);
				genericInterfaceMethodDeclaration();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(556);
				interfaceDeclaration();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(557);
				annotationTypeDeclaration();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(558);
				classDeclaration();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(559);
				enumDeclaration();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(560);
				recordDeclaration();
				}
				break;
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

	public static class ConstDeclarationContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public List<ConstantDeclaratorContext> constantDeclarator() {
			return getRuleContexts(ConstantDeclaratorContext.class);
		}
		public ConstantDeclaratorContext constantDeclarator(int i) {
			return getRuleContext(ConstantDeclaratorContext.class,i);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public ConstDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constDeclaration; }
	}

	public final ConstDeclarationContext constDeclaration() throws RecognitionException {
		ConstDeclarationContext _localctx = new ConstDeclarationContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_constDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(563);
			typeType();
			setState(564);
			constantDeclarator();
			setState(569);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(565);
				match(COMMA);
				setState(566);
				constantDeclarator();
				}
				}
				setState(571);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(572);
			match(SEMI);
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

	public static class ConstantDeclaratorContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(JavaParser.ASSIGN, 0); }
		public VariableInitializerContext variableInitializer() {
			return getRuleContext(VariableInitializerContext.class,0);
		}
		public List<TerminalNode> LBRACK() { return getTokens(JavaParser.LBRACK); }
		public TerminalNode LBRACK(int i) {
			return getToken(JavaParser.LBRACK, i);
		}
		public List<TerminalNode> RBRACK() { return getTokens(JavaParser.RBRACK); }
		public TerminalNode RBRACK(int i) {
			return getToken(JavaParser.RBRACK, i);
		}
		public ConstantDeclaratorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_constantDeclarator; }
	}

	public final ConstantDeclaratorContext constantDeclarator() throws RecognitionException {
		ConstantDeclaratorContext _localctx = new ConstantDeclaratorContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_constantDeclarator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(574);
			identifier();
			setState(579);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==LBRACK) {
				{
				{
				setState(575);
				match(LBRACK);
				setState(576);
				match(RBRACK);
				}
				}
				setState(581);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(582);
			match(ASSIGN);
			setState(583);
			variableInitializer();
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

	public static class InterfaceMethodDeclarationContext extends ParserRuleContext {
		public InterfaceCommonBodyDeclarationContext interfaceCommonBodyDeclaration() {
			return getRuleContext(InterfaceCommonBodyDeclarationContext.class,0);
		}
		public List<InterfaceMethodModifierContext> interfaceMethodModifier() {
			return getRuleContexts(InterfaceMethodModifierContext.class);
		}
		public InterfaceMethodModifierContext interfaceMethodModifier(int i) {
			return getRuleContext(InterfaceMethodModifierContext.class,i);
		}
		public InterfaceMethodDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interfaceMethodDeclaration; }
	}

	public final InterfaceMethodDeclarationContext interfaceMethodDeclaration() throws RecognitionException {
		InterfaceMethodDeclarationContext _localctx = new InterfaceMethodDeclarationContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_interfaceMethodDeclaration);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(588);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,51,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(585);
					interfaceMethodModifier();
					}
					} 
				}
				setState(590);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,51,_ctx);
			}
			setState(591);
			interfaceCommonBodyDeclaration();
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

	public static class InterfaceMethodModifierContext extends ParserRuleContext {
		public AnnotationContext annotation() {
			return getRuleContext(AnnotationContext.class,0);
		}
		public TerminalNode PUBLIC() { return getToken(JavaParser.PUBLIC, 0); }
		public TerminalNode ABSTRACT() { return getToken(JavaParser.ABSTRACT, 0); }
		public TerminalNode DEFAULT() { return getToken(JavaParser.DEFAULT, 0); }
		public TerminalNode STATIC() { return getToken(JavaParser.STATIC, 0); }
		public TerminalNode STRICTFP() { return getToken(JavaParser.STRICTFP, 0); }
		public InterfaceMethodModifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interfaceMethodModifier; }
	}

	public final InterfaceMethodModifierContext interfaceMethodModifier() throws RecognitionException {
		InterfaceMethodModifierContext _localctx = new InterfaceMethodModifierContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_interfaceMethodModifier);
		try {
			setState(599);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(593);
				annotation();
				}
				break;
			case PUBLIC:
				enterOuterAlt(_localctx, 2);
				{
				setState(594);
				match(PUBLIC);
				}
				break;
			case ABSTRACT:
				enterOuterAlt(_localctx, 3);
				{
				setState(595);
				match(ABSTRACT);
				}
				break;
			case DEFAULT:
				enterOuterAlt(_localctx, 4);
				{
				setState(596);
				match(DEFAULT);
				}
				break;
			case STATIC:
				enterOuterAlt(_localctx, 5);
				{
				setState(597);
				match(STATIC);
				}
				break;
			case STRICTFP:
				enterOuterAlt(_localctx, 6);
				{
				setState(598);
				match(STRICTFP);
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

	public static class GenericInterfaceMethodDeclarationContext extends ParserRuleContext {
		public TypeParametersContext typeParameters() {
			return getRuleContext(TypeParametersContext.class,0);
		}
		public InterfaceCommonBodyDeclarationContext interfaceCommonBodyDeclaration() {
			return getRuleContext(InterfaceCommonBodyDeclarationContext.class,0);
		}
		public List<InterfaceMethodModifierContext> interfaceMethodModifier() {
			return getRuleContexts(InterfaceMethodModifierContext.class);
		}
		public InterfaceMethodModifierContext interfaceMethodModifier(int i) {
			return getRuleContext(InterfaceMethodModifierContext.class,i);
		}
		public GenericInterfaceMethodDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_genericInterfaceMethodDeclaration; }
	}

	public final GenericInterfaceMethodDeclarationContext genericInterfaceMethodDeclaration() throws RecognitionException {
		GenericInterfaceMethodDeclarationContext _localctx = new GenericInterfaceMethodDeclarationContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_genericInterfaceMethodDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(604);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << DEFAULT) | (1L << PUBLIC) | (1L << STATIC) | (1L << STRICTFP) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
				{
				{
				setState(601);
				interfaceMethodModifier();
				}
				}
				setState(606);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(607);
			typeParameters();
			setState(608);
			interfaceCommonBodyDeclaration();
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

	public static class InterfaceCommonBodyDeclarationContext extends ParserRuleContext {
		public TypeTypeOrVoidContext typeTypeOrVoid() {
			return getRuleContext(TypeTypeOrVoidContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public FormalParametersContext formalParameters() {
			return getRuleContext(FormalParametersContext.class,0);
		}
		public MethodBodyContext methodBody() {
			return getRuleContext(MethodBodyContext.class,0);
		}
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public List<TerminalNode> LBRACK() { return getTokens(JavaParser.LBRACK); }
		public TerminalNode LBRACK(int i) {
			return getToken(JavaParser.LBRACK, i);
		}
		public List<TerminalNode> RBRACK() { return getTokens(JavaParser.RBRACK); }
		public TerminalNode RBRACK(int i) {
			return getToken(JavaParser.RBRACK, i);
		}
		public TerminalNode THROWS() { return getToken(JavaParser.THROWS, 0); }
		public QualifiedNameListContext qualifiedNameList() {
			return getRuleContext(QualifiedNameListContext.class,0);
		}
		public InterfaceCommonBodyDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_interfaceCommonBodyDeclaration; }
	}

	public final InterfaceCommonBodyDeclarationContext interfaceCommonBodyDeclaration() throws RecognitionException {
		InterfaceCommonBodyDeclarationContext _localctx = new InterfaceCommonBodyDeclarationContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_interfaceCommonBodyDeclaration);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(613);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,54,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(610);
					annotation();
					}
					} 
				}
				setState(615);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,54,_ctx);
			}
			setState(616);
			typeTypeOrVoid();
			setState(617);
			identifier();
			setState(618);
			formalParameters();
			setState(623);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==LBRACK) {
				{
				{
				setState(619);
				match(LBRACK);
				setState(620);
				match(RBRACK);
				}
				}
				setState(625);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(628);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==THROWS) {
				{
				setState(626);
				match(THROWS);
				setState(627);
				qualifiedNameList();
				}
			}

			setState(630);
			methodBody();
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

	public static class VariableDeclaratorsContext extends ParserRuleContext {
		public List<VariableDeclaratorContext> variableDeclarator() {
			return getRuleContexts(VariableDeclaratorContext.class);
		}
		public VariableDeclaratorContext variableDeclarator(int i) {
			return getRuleContext(VariableDeclaratorContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public VariableDeclaratorsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDeclarators; }
	}

	public final VariableDeclaratorsContext variableDeclarators() throws RecognitionException {
		VariableDeclaratorsContext _localctx = new VariableDeclaratorsContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_variableDeclarators);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(632);
			variableDeclarator();
			setState(637);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(633);
				match(COMMA);
				setState(634);
				variableDeclarator();
				}
				}
				setState(639);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class VariableDeclaratorContext extends ParserRuleContext {
		public VariableDeclaratorIdContext variableDeclaratorId() {
			return getRuleContext(VariableDeclaratorIdContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(JavaParser.ASSIGN, 0); }
		public VariableInitializerContext variableInitializer() {
			return getRuleContext(VariableInitializerContext.class,0);
		}
		public VariableDeclaratorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDeclarator; }
	}

	public final VariableDeclaratorContext variableDeclarator() throws RecognitionException {
		VariableDeclaratorContext _localctx = new VariableDeclaratorContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_variableDeclarator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(640);
			variableDeclaratorId();
			setState(643);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==ASSIGN) {
				{
				setState(641);
				match(ASSIGN);
				setState(642);
				variableInitializer();
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

	public static class VariableDeclaratorIdContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public List<TerminalNode> LBRACK() { return getTokens(JavaParser.LBRACK); }
		public TerminalNode LBRACK(int i) {
			return getToken(JavaParser.LBRACK, i);
		}
		public List<TerminalNode> RBRACK() { return getTokens(JavaParser.RBRACK); }
		public TerminalNode RBRACK(int i) {
			return getToken(JavaParser.RBRACK, i);
		}
		public VariableDeclaratorIdContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDeclaratorId; }
	}

	public final VariableDeclaratorIdContext variableDeclaratorId() throws RecognitionException {
		VariableDeclaratorIdContext _localctx = new VariableDeclaratorIdContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_variableDeclaratorId);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(645);
			identifier();
			setState(650);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==LBRACK) {
				{
				{
				setState(646);
				match(LBRACK);
				setState(647);
				match(RBRACK);
				}
				}
				setState(652);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class VariableInitializerContext extends ParserRuleContext {
		public ArrayInitializerContext arrayInitializer() {
			return getRuleContext(ArrayInitializerContext.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public VariableInitializerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableInitializer; }
	}

	public final VariableInitializerContext variableInitializer() throws RecognitionException {
		VariableInitializerContext _localctx = new VariableInitializerContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_variableInitializer);
		try {
			setState(655);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LBRACE:
				enterOuterAlt(_localctx, 1);
				{
				setState(653);
				arrayInitializer();
				}
				break;
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case DOUBLE:
			case FLOAT:
			case INT:
			case LONG:
			case NEW:
			case SHORT:
			case SUPER:
			case SWITCH:
			case THIS:
			case VOID:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case DECIMAL_LITERAL:
			case HEX_LITERAL:
			case OCT_LITERAL:
			case BINARY_LITERAL:
			case FLOAT_LITERAL:
			case HEX_FLOAT_LITERAL:
			case BOOL_LITERAL:
			case CHAR_LITERAL:
			case STRING_LITERAL:
			case TEXT_BLOCK:
			case NULL_LITERAL:
			case LPAREN:
			case LT:
			case BANG:
			case TILDE:
			case INC:
			case DEC:
			case ADD:
			case SUB:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				setState(654);
				expression(0);
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

	public static class ArrayInitializerContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<VariableInitializerContext> variableInitializer() {
			return getRuleContexts(VariableInitializerContext.class);
		}
		public VariableInitializerContext variableInitializer(int i) {
			return getRuleContext(VariableInitializerContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public ArrayInitializerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayInitializer; }
	}

	public final ArrayInitializerContext arrayInitializer() throws RecognitionException {
		ArrayInitializerContext _localctx = new ArrayInitializerContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_arrayInitializer);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(657);
			match(LBRACE);
			setState(669);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LBRACE - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
				{
				setState(658);
				variableInitializer();
				setState(663);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,61,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(659);
						match(COMMA);
						setState(660);
						variableInitializer();
						}
						} 
					}
					setState(665);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,61,_ctx);
				}
				setState(667);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==COMMA) {
					{
					setState(666);
					match(COMMA);
					}
				}

				}
			}

			setState(671);
			match(RBRACE);
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

	public static class ClassOrInterfaceTypeContext extends ParserRuleContext {
		public TypeIdentifierContext typeIdentifier() {
			return getRuleContext(TypeIdentifierContext.class,0);
		}
		public List<IdentifierContext> identifier() {
			return getRuleContexts(IdentifierContext.class);
		}
		public IdentifierContext identifier(int i) {
			return getRuleContext(IdentifierContext.class,i);
		}
		public List<TerminalNode> DOT() { return getTokens(JavaParser.DOT); }
		public TerminalNode DOT(int i) {
			return getToken(JavaParser.DOT, i);
		}
		public List<TypeArgumentsContext> typeArguments() {
			return getRuleContexts(TypeArgumentsContext.class);
		}
		public TypeArgumentsContext typeArguments(int i) {
			return getRuleContext(TypeArgumentsContext.class,i);
		}
		public ClassOrInterfaceTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classOrInterfaceType; }
	}

	public final ClassOrInterfaceTypeContext classOrInterfaceType() throws RecognitionException {
		ClassOrInterfaceTypeContext _localctx = new ClassOrInterfaceTypeContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_classOrInterfaceType);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(681);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,65,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(673);
					identifier();
					setState(675);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==LT) {
						{
						setState(674);
						typeArguments();
						}
					}

					setState(677);
					match(DOT);
					}
					} 
				}
				setState(683);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,65,_ctx);
			}
			setState(684);
			typeIdentifier();
			setState(686);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,66,_ctx) ) {
			case 1:
				{
				setState(685);
				typeArguments();
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

	public static class TypeArgumentContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public TerminalNode QUESTION() { return getToken(JavaParser.QUESTION, 0); }
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public TerminalNode EXTENDS() { return getToken(JavaParser.EXTENDS, 0); }
		public TerminalNode SUPER() { return getToken(JavaParser.SUPER, 0); }
		public TypeArgumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeArgument; }
	}

	public final TypeArgumentContext typeArgument() throws RecognitionException {
		TypeArgumentContext _localctx = new TypeArgumentContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_typeArgument);
		int _la;
		try {
			setState(700);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,69,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(688);
				typeType();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(692);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==AT || _la==IDENTIFIER) {
					{
					{
					setState(689);
					annotation();
					}
					}
					setState(694);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(695);
				match(QUESTION);
				setState(698);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==EXTENDS || _la==SUPER) {
					{
					setState(696);
					_la = _input.LA(1);
					if ( !(_la==EXTENDS || _la==SUPER) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(697);
					typeType();
					}
				}

				}
				break;
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

	public static class QualifiedNameListContext extends ParserRuleContext {
		public List<QualifiedNameContext> qualifiedName() {
			return getRuleContexts(QualifiedNameContext.class);
		}
		public QualifiedNameContext qualifiedName(int i) {
			return getRuleContext(QualifiedNameContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public QualifiedNameListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_qualifiedNameList; }
	}

	public final QualifiedNameListContext qualifiedNameList() throws RecognitionException {
		QualifiedNameListContext _localctx = new QualifiedNameListContext(_ctx, getState());
		enterRule(_localctx, 86, RULE_qualifiedNameList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(702);
			qualifiedName();
			setState(707);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(703);
				match(COMMA);
				setState(704);
				qualifiedName();
				}
				}
				setState(709);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class FormalParametersContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public ReceiverParameterContext receiverParameter() {
			return getRuleContext(ReceiverParameterContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(JavaParser.COMMA, 0); }
		public FormalParameterListContext formalParameterList() {
			return getRuleContext(FormalParameterListContext.class,0);
		}
		public FormalParametersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formalParameters; }
	}

	public final FormalParametersContext formalParameters() throws RecognitionException {
		FormalParametersContext _localctx = new FormalParametersContext(_ctx, getState());
		enterRule(_localctx, 88, RULE_formalParameters);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(710);
			match(LPAREN);
			setState(722);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,74,_ctx) ) {
			case 1:
				{
				setState(712);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (SHORT - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || _la==AT || _la==IDENTIFIER) {
					{
					setState(711);
					receiverParameter();
					}
				}

				}
				break;
			case 2:
				{
				setState(714);
				receiverParameter();
				setState(717);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==COMMA) {
					{
					setState(715);
					match(COMMA);
					setState(716);
					formalParameterList();
					}
				}

				}
				break;
			case 3:
				{
				setState(720);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FINAL - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (SHORT - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || _la==AT || _la==IDENTIFIER) {
					{
					setState(719);
					formalParameterList();
					}
				}

				}
				break;
			}
			setState(724);
			match(RPAREN);
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

	public static class ReceiverParameterContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public TerminalNode THIS() { return getToken(JavaParser.THIS, 0); }
		public List<IdentifierContext> identifier() {
			return getRuleContexts(IdentifierContext.class);
		}
		public IdentifierContext identifier(int i) {
			return getRuleContext(IdentifierContext.class,i);
		}
		public List<TerminalNode> DOT() { return getTokens(JavaParser.DOT); }
		public TerminalNode DOT(int i) {
			return getToken(JavaParser.DOT, i);
		}
		public ReceiverParameterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_receiverParameter; }
	}

	public final ReceiverParameterContext receiverParameter() throws RecognitionException {
		ReceiverParameterContext _localctx = new ReceiverParameterContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_receiverParameter);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(726);
			typeType();
			setState(732);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==IDENTIFIER) {
				{
				{
				setState(727);
				identifier();
				setState(728);
				match(DOT);
				}
				}
				setState(734);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(735);
			match(THIS);
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

	public static class FormalParameterListContext extends ParserRuleContext {
		public List<FormalParameterContext> formalParameter() {
			return getRuleContexts(FormalParameterContext.class);
		}
		public FormalParameterContext formalParameter(int i) {
			return getRuleContext(FormalParameterContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public LastFormalParameterContext lastFormalParameter() {
			return getRuleContext(LastFormalParameterContext.class,0);
		}
		public FormalParameterListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formalParameterList; }
	}

	public final FormalParameterListContext formalParameterList() throws RecognitionException {
		FormalParameterListContext _localctx = new FormalParameterListContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_formalParameterList);
		int _la;
		try {
			int _alt;
			setState(750);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,78,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(737);
				formalParameter();
				setState(742);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,76,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(738);
						match(COMMA);
						setState(739);
						formalParameter();
						}
						} 
					}
					setState(744);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,76,_ctx);
				}
				setState(747);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==COMMA) {
					{
					setState(745);
					match(COMMA);
					setState(746);
					lastFormalParameter();
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(749);
				lastFormalParameter();
				}
				break;
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

	public static class FormalParameterContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public VariableDeclaratorIdContext variableDeclaratorId() {
			return getRuleContext(VariableDeclaratorIdContext.class,0);
		}
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public FormalParameterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formalParameter; }
	}

	public final FormalParameterContext formalParameter() throws RecognitionException {
		FormalParameterContext _localctx = new FormalParameterContext(_ctx, getState());
		enterRule(_localctx, 94, RULE_formalParameter);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(755);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,79,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(752);
					variableModifier();
					}
					} 
				}
				setState(757);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,79,_ctx);
			}
			setState(758);
			typeType();
			setState(759);
			variableDeclaratorId();
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

	public static class LastFormalParameterContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public TerminalNode ELLIPSIS() { return getToken(JavaParser.ELLIPSIS, 0); }
		public VariableDeclaratorIdContext variableDeclaratorId() {
			return getRuleContext(VariableDeclaratorIdContext.class,0);
		}
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public LastFormalParameterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lastFormalParameter; }
	}

	public final LastFormalParameterContext lastFormalParameter() throws RecognitionException {
		LastFormalParameterContext _localctx = new LastFormalParameterContext(_ctx, getState());
		enterRule(_localctx, 96, RULE_lastFormalParameter);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(764);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,80,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(761);
					variableModifier();
					}
					} 
				}
				setState(766);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,80,_ctx);
			}
			setState(767);
			typeType();
			setState(771);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==AT || _la==IDENTIFIER) {
				{
				{
				setState(768);
				annotation();
				}
				}
				setState(773);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(774);
			match(ELLIPSIS);
			setState(775);
			variableDeclaratorId();
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

	public static class LambdaLVTIListContext extends ParserRuleContext {
		public List<LambdaLVTIParameterContext> lambdaLVTIParameter() {
			return getRuleContexts(LambdaLVTIParameterContext.class);
		}
		public LambdaLVTIParameterContext lambdaLVTIParameter(int i) {
			return getRuleContext(LambdaLVTIParameterContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public LambdaLVTIListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lambdaLVTIList; }
	}

	public final LambdaLVTIListContext lambdaLVTIList() throws RecognitionException {
		LambdaLVTIListContext _localctx = new LambdaLVTIListContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_lambdaLVTIList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(777);
			lambdaLVTIParameter();
			setState(782);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(778);
				match(COMMA);
				setState(779);
				lambdaLVTIParameter();
				}
				}
				setState(784);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class LambdaLVTIParameterContext extends ParserRuleContext {
		public TerminalNode VAR() { return getToken(JavaParser.VAR, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public LambdaLVTIParameterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lambdaLVTIParameter; }
	}

	public final LambdaLVTIParameterContext lambdaLVTIParameter() throws RecognitionException {
		LambdaLVTIParameterContext _localctx = new LambdaLVTIParameterContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_lambdaLVTIParameter);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(788);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,83,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(785);
					variableModifier();
					}
					} 
				}
				setState(790);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,83,_ctx);
			}
			setState(791);
			match(VAR);
			setState(792);
			identifier();
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

	public static class QualifiedNameContext extends ParserRuleContext {
		public List<IdentifierContext> identifier() {
			return getRuleContexts(IdentifierContext.class);
		}
		public IdentifierContext identifier(int i) {
			return getRuleContext(IdentifierContext.class,i);
		}
		public List<TerminalNode> DOT() { return getTokens(JavaParser.DOT); }
		public TerminalNode DOT(int i) {
			return getToken(JavaParser.DOT, i);
		}
		public QualifiedNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_qualifiedName; }
	}

	public final QualifiedNameContext qualifiedName() throws RecognitionException {
		QualifiedNameContext _localctx = new QualifiedNameContext(_ctx, getState());
		enterRule(_localctx, 102, RULE_qualifiedName);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(794);
			identifier();
			setState(799);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,84,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(795);
					match(DOT);
					setState(796);
					identifier();
					}
					} 
				}
				setState(801);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,84,_ctx);
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

	public static class LiteralContext extends ParserRuleContext {
		public IntegerLiteralContext integerLiteral() {
			return getRuleContext(IntegerLiteralContext.class,0);
		}
		public FloatLiteralContext floatLiteral() {
			return getRuleContext(FloatLiteralContext.class,0);
		}
		public TerminalNode CHAR_LITERAL() { return getToken(JavaParser.CHAR_LITERAL, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(JavaParser.STRING_LITERAL, 0); }
		public TerminalNode BOOL_LITERAL() { return getToken(JavaParser.BOOL_LITERAL, 0); }
		public TerminalNode NULL_LITERAL() { return getToken(JavaParser.NULL_LITERAL, 0); }
		public TerminalNode TEXT_BLOCK() { return getToken(JavaParser.TEXT_BLOCK, 0); }
		public LiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal; }
	}

	public final LiteralContext literal() throws RecognitionException {
		LiteralContext _localctx = new LiteralContext(_ctx, getState());
		enterRule(_localctx, 104, RULE_literal);
		try {
			setState(809);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case DECIMAL_LITERAL:
			case HEX_LITERAL:
			case OCT_LITERAL:
			case BINARY_LITERAL:
				enterOuterAlt(_localctx, 1);
				{
				setState(802);
				integerLiteral();
				}
				break;
			case FLOAT_LITERAL:
			case HEX_FLOAT_LITERAL:
				enterOuterAlt(_localctx, 2);
				{
				setState(803);
				floatLiteral();
				}
				break;
			case CHAR_LITERAL:
				enterOuterAlt(_localctx, 3);
				{
				setState(804);
				match(CHAR_LITERAL);
				}
				break;
			case STRING_LITERAL:
				enterOuterAlt(_localctx, 4);
				{
				setState(805);
				match(STRING_LITERAL);
				}
				break;
			case BOOL_LITERAL:
				enterOuterAlt(_localctx, 5);
				{
				setState(806);
				match(BOOL_LITERAL);
				}
				break;
			case NULL_LITERAL:
				enterOuterAlt(_localctx, 6);
				{
				setState(807);
				match(NULL_LITERAL);
				}
				break;
			case TEXT_BLOCK:
				enterOuterAlt(_localctx, 7);
				{
				setState(808);
				match(TEXT_BLOCK);
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

	public static class IntegerLiteralContext extends ParserRuleContext {
		public TerminalNode DECIMAL_LITERAL() { return getToken(JavaParser.DECIMAL_LITERAL, 0); }
		public TerminalNode HEX_LITERAL() { return getToken(JavaParser.HEX_LITERAL, 0); }
		public TerminalNode OCT_LITERAL() { return getToken(JavaParser.OCT_LITERAL, 0); }
		public TerminalNode BINARY_LITERAL() { return getToken(JavaParser.BINARY_LITERAL, 0); }
		public IntegerLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_integerLiteral; }
	}

	public final IntegerLiteralContext integerLiteral() throws RecognitionException {
		IntegerLiteralContext _localctx = new IntegerLiteralContext(_ctx, getState());
		enterRule(_localctx, 106, RULE_integerLiteral);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(811);
			_la = _input.LA(1);
			if ( !(((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)))) != 0)) ) {
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

	public static class FloatLiteralContext extends ParserRuleContext {
		public TerminalNode FLOAT_LITERAL() { return getToken(JavaParser.FLOAT_LITERAL, 0); }
		public TerminalNode HEX_FLOAT_LITERAL() { return getToken(JavaParser.HEX_FLOAT_LITERAL, 0); }
		public FloatLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_floatLiteral; }
	}

	public final FloatLiteralContext floatLiteral() throws RecognitionException {
		FloatLiteralContext _localctx = new FloatLiteralContext(_ctx, getState());
		enterRule(_localctx, 108, RULE_floatLiteral);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(813);
			_la = _input.LA(1);
			if ( !(_la==FLOAT_LITERAL || _la==HEX_FLOAT_LITERAL) ) {
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

	public static class AltAnnotationQualifiedNameContext extends ParserRuleContext {
		public TerminalNode AT() { return getToken(JavaParser.AT, 0); }
		public List<IdentifierContext> identifier() {
			return getRuleContexts(IdentifierContext.class);
		}
		public IdentifierContext identifier(int i) {
			return getRuleContext(IdentifierContext.class,i);
		}
		public List<TerminalNode> DOT() { return getTokens(JavaParser.DOT); }
		public TerminalNode DOT(int i) {
			return getToken(JavaParser.DOT, i);
		}
		public AltAnnotationQualifiedNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_altAnnotationQualifiedName; }
	}

	public final AltAnnotationQualifiedNameContext altAnnotationQualifiedName() throws RecognitionException {
		AltAnnotationQualifiedNameContext _localctx = new AltAnnotationQualifiedNameContext(_ctx, getState());
		enterRule(_localctx, 110, RULE_altAnnotationQualifiedName);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(820);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==IDENTIFIER) {
				{
				{
				setState(815);
				identifier();
				setState(816);
				match(DOT);
				}
				}
				setState(822);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(823);
			match(AT);
			setState(824);
			identifier();
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

	public static class AnnotationContext extends ParserRuleContext {
		public TerminalNode AT() { return getToken(JavaParser.AT, 0); }
		public QualifiedNameContext qualifiedName() {
			return getRuleContext(QualifiedNameContext.class,0);
		}
		public AltAnnotationQualifiedNameContext altAnnotationQualifiedName() {
			return getRuleContext(AltAnnotationQualifiedNameContext.class,0);
		}
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public ElementValuePairsContext elementValuePairs() {
			return getRuleContext(ElementValuePairsContext.class,0);
		}
		public ElementValueContext elementValue() {
			return getRuleContext(ElementValueContext.class,0);
		}
		public AnnotationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotation; }
	}

	public final AnnotationContext annotation() throws RecognitionException {
		AnnotationContext _localctx = new AnnotationContext(_ctx, getState());
		enterRule(_localctx, 112, RULE_annotation);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(829);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,87,_ctx) ) {
			case 1:
				{
				setState(826);
				match(AT);
				setState(827);
				qualifiedName();
				}
				break;
			case 2:
				{
				setState(828);
				altAnnotationQualifiedName();
				}
				break;
			}
			setState(837);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LPAREN) {
				{
				setState(831);
				match(LPAREN);
				setState(834);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,88,_ctx) ) {
				case 1:
					{
					setState(832);
					elementValuePairs();
					}
					break;
				case 2:
					{
					setState(833);
					elementValue();
					}
					break;
				}
				setState(836);
				match(RPAREN);
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

	public static class ElementValuePairsContext extends ParserRuleContext {
		public List<ElementValuePairContext> elementValuePair() {
			return getRuleContexts(ElementValuePairContext.class);
		}
		public ElementValuePairContext elementValuePair(int i) {
			return getRuleContext(ElementValuePairContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public ElementValuePairsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementValuePairs; }
	}

	public final ElementValuePairsContext elementValuePairs() throws RecognitionException {
		ElementValuePairsContext _localctx = new ElementValuePairsContext(_ctx, getState());
		enterRule(_localctx, 114, RULE_elementValuePairs);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(839);
			elementValuePair();
			setState(844);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(840);
				match(COMMA);
				setState(841);
				elementValuePair();
				}
				}
				setState(846);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class ElementValuePairContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(JavaParser.ASSIGN, 0); }
		public ElementValueContext elementValue() {
			return getRuleContext(ElementValueContext.class,0);
		}
		public ElementValuePairContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementValuePair; }
	}

	public final ElementValuePairContext elementValuePair() throws RecognitionException {
		ElementValuePairContext _localctx = new ElementValuePairContext(_ctx, getState());
		enterRule(_localctx, 116, RULE_elementValuePair);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(847);
			identifier();
			setState(848);
			match(ASSIGN);
			setState(849);
			elementValue();
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

	public static class ElementValueContext extends ParserRuleContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public AnnotationContext annotation() {
			return getRuleContext(AnnotationContext.class,0);
		}
		public ElementValueArrayInitializerContext elementValueArrayInitializer() {
			return getRuleContext(ElementValueArrayInitializerContext.class,0);
		}
		public ElementValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementValue; }
	}

	public final ElementValueContext elementValue() throws RecognitionException {
		ElementValueContext _localctx = new ElementValueContext(_ctx, getState());
		enterRule(_localctx, 118, RULE_elementValue);
		try {
			setState(854);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,91,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(851);
				expression(0);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(852);
				annotation();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(853);
				elementValueArrayInitializer();
				}
				break;
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

	public static class ElementValueArrayInitializerContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<ElementValueContext> elementValue() {
			return getRuleContexts(ElementValueContext.class);
		}
		public ElementValueContext elementValue(int i) {
			return getRuleContext(ElementValueContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public ElementValueArrayInitializerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementValueArrayInitializer; }
	}

	public final ElementValueArrayInitializerContext elementValueArrayInitializer() throws RecognitionException {
		ElementValueArrayInitializerContext _localctx = new ElementValueArrayInitializerContext(_ctx, getState());
		enterRule(_localctx, 120, RULE_elementValueArrayInitializer);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(856);
			match(LBRACE);
			setState(865);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LBRACE - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
				{
				setState(857);
				elementValue();
				setState(862);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,92,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(858);
						match(COMMA);
						setState(859);
						elementValue();
						}
						} 
					}
					setState(864);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,92,_ctx);
				}
				}
			}

			setState(868);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COMMA) {
				{
				setState(867);
				match(COMMA);
				}
			}

			setState(870);
			match(RBRACE);
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

	public static class AnnotationTypeDeclarationContext extends ParserRuleContext {
		public TerminalNode AT() { return getToken(JavaParser.AT, 0); }
		public TerminalNode INTERFACE() { return getToken(JavaParser.INTERFACE, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public AnnotationTypeBodyContext annotationTypeBody() {
			return getRuleContext(AnnotationTypeBodyContext.class,0);
		}
		public AnnotationTypeDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotationTypeDeclaration; }
	}

	public final AnnotationTypeDeclarationContext annotationTypeDeclaration() throws RecognitionException {
		AnnotationTypeDeclarationContext _localctx = new AnnotationTypeDeclarationContext(_ctx, getState());
		enterRule(_localctx, 122, RULE_annotationTypeDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(872);
			match(AT);
			setState(873);
			match(INTERFACE);
			setState(874);
			identifier();
			setState(875);
			annotationTypeBody();
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

	public static class AnnotationTypeBodyContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<AnnotationTypeElementDeclarationContext> annotationTypeElementDeclaration() {
			return getRuleContexts(AnnotationTypeElementDeclarationContext.class);
		}
		public AnnotationTypeElementDeclarationContext annotationTypeElementDeclaration(int i) {
			return getRuleContext(AnnotationTypeElementDeclarationContext.class,i);
		}
		public AnnotationTypeBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotationTypeBody; }
	}

	public final AnnotationTypeBodyContext annotationTypeBody() throws RecognitionException {
		AnnotationTypeBodyContext _localctx = new AnnotationTypeBodyContext(_ctx, getState());
		enterRule(_localctx, 124, RULE_annotationTypeBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(877);
			match(LBRACE);
			setState(881);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << BOOLEAN) | (1L << BYTE) | (1L << CHAR) | (1L << CLASS) | (1L << DOUBLE) | (1L << ENUM) | (1L << FINAL) | (1L << FLOAT) | (1L << INT) | (1L << INTERFACE) | (1L << LONG) | (1L << NATIVE) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << SHORT) | (1L << STATIC) | (1L << STRICTFP) | (1L << SYNCHRONIZED) | (1L << TRANSIENT) | (1L << VOLATILE) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (SEMI - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
				{
				{
				setState(878);
				annotationTypeElementDeclaration();
				}
				}
				setState(883);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(884);
			match(RBRACE);
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

	public static class AnnotationTypeElementDeclarationContext extends ParserRuleContext {
		public AnnotationTypeElementRestContext annotationTypeElementRest() {
			return getRuleContext(AnnotationTypeElementRestContext.class,0);
		}
		public List<ModifierContext> modifier() {
			return getRuleContexts(ModifierContext.class);
		}
		public ModifierContext modifier(int i) {
			return getRuleContext(ModifierContext.class,i);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public AnnotationTypeElementDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotationTypeElementDeclaration; }
	}

	public final AnnotationTypeElementDeclarationContext annotationTypeElementDeclaration() throws RecognitionException {
		AnnotationTypeElementDeclarationContext _localctx = new AnnotationTypeElementDeclarationContext(_ctx, getState());
		enterRule(_localctx, 126, RULE_annotationTypeElementDeclaration);
		try {
			int _alt;
			setState(894);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case ABSTRACT:
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case CLASS:
			case DOUBLE:
			case ENUM:
			case FINAL:
			case FLOAT:
			case INT:
			case INTERFACE:
			case LONG:
			case NATIVE:
			case PRIVATE:
			case PROTECTED:
			case PUBLIC:
			case SHORT:
			case STATIC:
			case STRICTFP:
			case SYNCHRONIZED:
			case TRANSIENT:
			case VOLATILE:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case NON_SEALED:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(889);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,96,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(886);
						modifier();
						}
						} 
					}
					setState(891);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,96,_ctx);
				}
				setState(892);
				annotationTypeElementRest();
				}
				break;
			case SEMI:
				enterOuterAlt(_localctx, 2);
				{
				setState(893);
				match(SEMI);
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

	public static class AnnotationTypeElementRestContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public AnnotationMethodOrConstantRestContext annotationMethodOrConstantRest() {
			return getRuleContext(AnnotationMethodOrConstantRestContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public ClassDeclarationContext classDeclaration() {
			return getRuleContext(ClassDeclarationContext.class,0);
		}
		public InterfaceDeclarationContext interfaceDeclaration() {
			return getRuleContext(InterfaceDeclarationContext.class,0);
		}
		public EnumDeclarationContext enumDeclaration() {
			return getRuleContext(EnumDeclarationContext.class,0);
		}
		public AnnotationTypeDeclarationContext annotationTypeDeclaration() {
			return getRuleContext(AnnotationTypeDeclarationContext.class,0);
		}
		public RecordDeclarationContext recordDeclaration() {
			return getRuleContext(RecordDeclarationContext.class,0);
		}
		public AnnotationTypeElementRestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotationTypeElementRest; }
	}

	public final AnnotationTypeElementRestContext annotationTypeElementRest() throws RecognitionException {
		AnnotationTypeElementRestContext _localctx = new AnnotationTypeElementRestContext(_ctx, getState());
		enterRule(_localctx, 128, RULE_annotationTypeElementRest);
		try {
			setState(920);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,103,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(896);
				typeType();
				setState(897);
				annotationMethodOrConstantRest();
				setState(898);
				match(SEMI);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(900);
				classDeclaration();
				setState(902);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,98,_ctx) ) {
				case 1:
					{
					setState(901);
					match(SEMI);
					}
					break;
				}
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(904);
				interfaceDeclaration();
				setState(906);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,99,_ctx) ) {
				case 1:
					{
					setState(905);
					match(SEMI);
					}
					break;
				}
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(908);
				enumDeclaration();
				setState(910);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,100,_ctx) ) {
				case 1:
					{
					setState(909);
					match(SEMI);
					}
					break;
				}
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(912);
				annotationTypeDeclaration();
				setState(914);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,101,_ctx) ) {
				case 1:
					{
					setState(913);
					match(SEMI);
					}
					break;
				}
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(916);
				recordDeclaration();
				setState(918);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,102,_ctx) ) {
				case 1:
					{
					setState(917);
					match(SEMI);
					}
					break;
				}
				}
				break;
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

	public static class AnnotationMethodOrConstantRestContext extends ParserRuleContext {
		public AnnotationMethodRestContext annotationMethodRest() {
			return getRuleContext(AnnotationMethodRestContext.class,0);
		}
		public AnnotationConstantRestContext annotationConstantRest() {
			return getRuleContext(AnnotationConstantRestContext.class,0);
		}
		public AnnotationMethodOrConstantRestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotationMethodOrConstantRest; }
	}

	public final AnnotationMethodOrConstantRestContext annotationMethodOrConstantRest() throws RecognitionException {
		AnnotationMethodOrConstantRestContext _localctx = new AnnotationMethodOrConstantRestContext(_ctx, getState());
		enterRule(_localctx, 130, RULE_annotationMethodOrConstantRest);
		try {
			setState(924);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,104,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(922);
				annotationMethodRest();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(923);
				annotationConstantRest();
				}
				break;
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

	public static class AnnotationMethodRestContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public DefaultValueContext defaultValue() {
			return getRuleContext(DefaultValueContext.class,0);
		}
		public AnnotationMethodRestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotationMethodRest; }
	}

	public final AnnotationMethodRestContext annotationMethodRest() throws RecognitionException {
		AnnotationMethodRestContext _localctx = new AnnotationMethodRestContext(_ctx, getState());
		enterRule(_localctx, 132, RULE_annotationMethodRest);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(926);
			identifier();
			setState(927);
			match(LPAREN);
			setState(928);
			match(RPAREN);
			setState(930);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==DEFAULT) {
				{
				setState(929);
				defaultValue();
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

	public static class AnnotationConstantRestContext extends ParserRuleContext {
		public VariableDeclaratorsContext variableDeclarators() {
			return getRuleContext(VariableDeclaratorsContext.class,0);
		}
		public AnnotationConstantRestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_annotationConstantRest; }
	}

	public final AnnotationConstantRestContext annotationConstantRest() throws RecognitionException {
		AnnotationConstantRestContext _localctx = new AnnotationConstantRestContext(_ctx, getState());
		enterRule(_localctx, 134, RULE_annotationConstantRest);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(932);
			variableDeclarators();
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

	public static class DefaultValueContext extends ParserRuleContext {
		public TerminalNode DEFAULT() { return getToken(JavaParser.DEFAULT, 0); }
		public ElementValueContext elementValue() {
			return getRuleContext(ElementValueContext.class,0);
		}
		public DefaultValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defaultValue; }
	}

	public final DefaultValueContext defaultValue() throws RecognitionException {
		DefaultValueContext _localctx = new DefaultValueContext(_ctx, getState());
		enterRule(_localctx, 136, RULE_defaultValue);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(934);
			match(DEFAULT);
			setState(935);
			elementValue();
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

	public static class ModuleDeclarationContext extends ParserRuleContext {
		public TerminalNode MODULE() { return getToken(JavaParser.MODULE, 0); }
		public QualifiedNameContext qualifiedName() {
			return getRuleContext(QualifiedNameContext.class,0);
		}
		public ModuleBodyContext moduleBody() {
			return getRuleContext(ModuleBodyContext.class,0);
		}
		public TerminalNode OPEN() { return getToken(JavaParser.OPEN, 0); }
		public ModuleDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_moduleDeclaration; }
	}

	public final ModuleDeclarationContext moduleDeclaration() throws RecognitionException {
		ModuleDeclarationContext _localctx = new ModuleDeclarationContext(_ctx, getState());
		enterRule(_localctx, 138, RULE_moduleDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(938);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==OPEN) {
				{
				setState(937);
				match(OPEN);
				}
			}

			setState(940);
			match(MODULE);
			setState(941);
			qualifiedName();
			setState(942);
			moduleBody();
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

	public static class ModuleBodyContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<ModuleDirectiveContext> moduleDirective() {
			return getRuleContexts(ModuleDirectiveContext.class);
		}
		public ModuleDirectiveContext moduleDirective(int i) {
			return getRuleContext(ModuleDirectiveContext.class,i);
		}
		public ModuleBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_moduleBody; }
	}

	public final ModuleBodyContext moduleBody() throws RecognitionException {
		ModuleBodyContext _localctx = new ModuleBodyContext(_ctx, getState());
		enterRule(_localctx, 140, RULE_moduleBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(944);
			match(LBRACE);
			setState(948);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << USES) | (1L << PROVIDES))) != 0)) {
				{
				{
				setState(945);
				moduleDirective();
				}
				}
				setState(950);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(951);
			match(RBRACE);
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

	public static class ModuleDirectiveContext extends ParserRuleContext {
		public TerminalNode REQUIRES() { return getToken(JavaParser.REQUIRES, 0); }
		public List<QualifiedNameContext> qualifiedName() {
			return getRuleContexts(QualifiedNameContext.class);
		}
		public QualifiedNameContext qualifiedName(int i) {
			return getRuleContext(QualifiedNameContext.class,i);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public List<RequiresModifierContext> requiresModifier() {
			return getRuleContexts(RequiresModifierContext.class);
		}
		public RequiresModifierContext requiresModifier(int i) {
			return getRuleContext(RequiresModifierContext.class,i);
		}
		public TerminalNode EXPORTS() { return getToken(JavaParser.EXPORTS, 0); }
		public TerminalNode TO() { return getToken(JavaParser.TO, 0); }
		public TerminalNode OPENS() { return getToken(JavaParser.OPENS, 0); }
		public TerminalNode USES() { return getToken(JavaParser.USES, 0); }
		public TerminalNode PROVIDES() { return getToken(JavaParser.PROVIDES, 0); }
		public TerminalNode WITH() { return getToken(JavaParser.WITH, 0); }
		public ModuleDirectiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_moduleDirective; }
	}

	public final ModuleDirectiveContext moduleDirective() throws RecognitionException {
		ModuleDirectiveContext _localctx = new ModuleDirectiveContext(_ctx, getState());
		enterRule(_localctx, 142, RULE_moduleDirective);
		int _la;
		try {
			int _alt;
			setState(989);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case REQUIRES:
				enterOuterAlt(_localctx, 1);
				{
				setState(953);
				match(REQUIRES);
				setState(957);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,108,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(954);
						requiresModifier();
						}
						} 
					}
					setState(959);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,108,_ctx);
				}
				setState(960);
				qualifiedName();
				setState(961);
				match(SEMI);
				}
				break;
			case EXPORTS:
				enterOuterAlt(_localctx, 2);
				{
				setState(963);
				match(EXPORTS);
				setState(964);
				qualifiedName();
				setState(967);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==TO) {
					{
					setState(965);
					match(TO);
					setState(966);
					qualifiedName();
					}
				}

				setState(969);
				match(SEMI);
				}
				break;
			case OPENS:
				enterOuterAlt(_localctx, 3);
				{
				setState(971);
				match(OPENS);
				setState(972);
				qualifiedName();
				setState(975);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==TO) {
					{
					setState(973);
					match(TO);
					setState(974);
					qualifiedName();
					}
				}

				setState(977);
				match(SEMI);
				}
				break;
			case USES:
				enterOuterAlt(_localctx, 4);
				{
				setState(979);
				match(USES);
				setState(980);
				qualifiedName();
				setState(981);
				match(SEMI);
				}
				break;
			case PROVIDES:
				enterOuterAlt(_localctx, 5);
				{
				setState(983);
				match(PROVIDES);
				setState(984);
				qualifiedName();
				setState(985);
				match(WITH);
				setState(986);
				qualifiedName();
				setState(987);
				match(SEMI);
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

	public static class RequiresModifierContext extends ParserRuleContext {
		public TerminalNode TRANSITIVE() { return getToken(JavaParser.TRANSITIVE, 0); }
		public TerminalNode STATIC() { return getToken(JavaParser.STATIC, 0); }
		public RequiresModifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_requiresModifier; }
	}

	public final RequiresModifierContext requiresModifier() throws RecognitionException {
		RequiresModifierContext _localctx = new RequiresModifierContext(_ctx, getState());
		enterRule(_localctx, 144, RULE_requiresModifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(991);
			_la = _input.LA(1);
			if ( !(_la==STATIC || _la==TRANSITIVE) ) {
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

	public static class RecordDeclarationContext extends ParserRuleContext {
		public TerminalNode RECORD() { return getToken(JavaParser.RECORD, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public RecordHeaderContext recordHeader() {
			return getRuleContext(RecordHeaderContext.class,0);
		}
		public RecordBodyContext recordBody() {
			return getRuleContext(RecordBodyContext.class,0);
		}
		public TypeParametersContext typeParameters() {
			return getRuleContext(TypeParametersContext.class,0);
		}
		public TerminalNode IMPLEMENTS() { return getToken(JavaParser.IMPLEMENTS, 0); }
		public TypeListContext typeList() {
			return getRuleContext(TypeListContext.class,0);
		}
		public RecordDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_recordDeclaration; }
	}

	public final RecordDeclarationContext recordDeclaration() throws RecognitionException {
		RecordDeclarationContext _localctx = new RecordDeclarationContext(_ctx, getState());
		enterRule(_localctx, 146, RULE_recordDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(993);
			match(RECORD);
			setState(994);
			identifier();
			setState(996);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LT) {
				{
				setState(995);
				typeParameters();
				}
			}

			setState(998);
			recordHeader();
			setState(1001);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IMPLEMENTS) {
				{
				setState(999);
				match(IMPLEMENTS);
				setState(1000);
				typeList();
				}
			}

			setState(1003);
			recordBody();
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

	public static class RecordHeaderContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public RecordComponentListContext recordComponentList() {
			return getRuleContext(RecordComponentListContext.class,0);
		}
		public RecordHeaderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_recordHeader; }
	}

	public final RecordHeaderContext recordHeader() throws RecognitionException {
		RecordHeaderContext _localctx = new RecordHeaderContext(_ctx, getState());
		enterRule(_localctx, 148, RULE_recordHeader);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1005);
			match(LPAREN);
			setState(1007);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (SHORT - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || _la==AT || _la==IDENTIFIER) {
				{
				setState(1006);
				recordComponentList();
				}
			}

			setState(1009);
			match(RPAREN);
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

	public static class RecordComponentListContext extends ParserRuleContext {
		public List<RecordComponentContext> recordComponent() {
			return getRuleContexts(RecordComponentContext.class);
		}
		public RecordComponentContext recordComponent(int i) {
			return getRuleContext(RecordComponentContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public RecordComponentListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_recordComponentList; }
	}

	public final RecordComponentListContext recordComponentList() throws RecognitionException {
		RecordComponentListContext _localctx = new RecordComponentListContext(_ctx, getState());
		enterRule(_localctx, 150, RULE_recordComponentList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1011);
			recordComponent();
			setState(1016);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(1012);
				match(COMMA);
				setState(1013);
				recordComponent();
				}
				}
				setState(1018);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class RecordComponentContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public RecordComponentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_recordComponent; }
	}

	public final RecordComponentContext recordComponent() throws RecognitionException {
		RecordComponentContext _localctx = new RecordComponentContext(_ctx, getState());
		enterRule(_localctx, 152, RULE_recordComponent);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1019);
			typeType();
			setState(1020);
			identifier();
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

	public static class RecordBodyContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<ClassBodyDeclarationContext> classBodyDeclaration() {
			return getRuleContexts(ClassBodyDeclarationContext.class);
		}
		public ClassBodyDeclarationContext classBodyDeclaration(int i) {
			return getRuleContext(ClassBodyDeclarationContext.class,i);
		}
		public List<CompactConstructorDeclarationContext> compactConstructorDeclaration() {
			return getRuleContexts(CompactConstructorDeclarationContext.class);
		}
		public CompactConstructorDeclarationContext compactConstructorDeclaration(int i) {
			return getRuleContext(CompactConstructorDeclarationContext.class,i);
		}
		public RecordBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_recordBody; }
	}

	public final RecordBodyContext recordBody() throws RecognitionException {
		RecordBodyContext _localctx = new RecordBodyContext(_ctx, getState());
		enterRule(_localctx, 154, RULE_recordBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1022);
			match(LBRACE);
			setState(1027);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << BOOLEAN) | (1L << BYTE) | (1L << CHAR) | (1L << CLASS) | (1L << DOUBLE) | (1L << ENUM) | (1L << FINAL) | (1L << FLOAT) | (1L << INT) | (1L << INTERFACE) | (1L << LONG) | (1L << NATIVE) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << SHORT) | (1L << STATIC) | (1L << STRICTFP) | (1L << SYNCHRONIZED) | (1L << TRANSIENT) | (1L << VOID) | (1L << VOLATILE) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (LBRACE - 64)) | (1L << (SEMI - 64)) | (1L << (LT - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
				{
				setState(1025);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,116,_ctx) ) {
				case 1:
					{
					setState(1023);
					classBodyDeclaration();
					}
					break;
				case 2:
					{
					setState(1024);
					compactConstructorDeclaration();
					}
					break;
				}
				}
				setState(1029);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(1030);
			match(RBRACE);
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

	public static class BlockContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<BlockStatementContext> blockStatement() {
			return getRuleContexts(BlockStatementContext.class);
		}
		public BlockStatementContext blockStatement(int i) {
			return getRuleContext(BlockStatementContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 156, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1032);
			match(LBRACE);
			setState(1036);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << ASSERT) | (1L << BOOLEAN) | (1L << BREAK) | (1L << BYTE) | (1L << CHAR) | (1L << CLASS) | (1L << CONTINUE) | (1L << DO) | (1L << DOUBLE) | (1L << FINAL) | (1L << FLOAT) | (1L << FOR) | (1L << IF) | (1L << INT) | (1L << INTERFACE) | (1L << LONG) | (1L << NEW) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << RETURN) | (1L << SHORT) | (1L << STATIC) | (1L << STRICTFP) | (1L << SUPER) | (1L << SWITCH) | (1L << SYNCHRONIZED) | (1L << THIS) | (1L << THROW) | (1L << TRY) | (1L << VOID) | (1L << WHILE) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (DECIMAL_LITERAL - 64)) | (1L << (HEX_LITERAL - 64)) | (1L << (OCT_LITERAL - 64)) | (1L << (BINARY_LITERAL - 64)) | (1L << (FLOAT_LITERAL - 64)) | (1L << (HEX_FLOAT_LITERAL - 64)) | (1L << (BOOL_LITERAL - 64)) | (1L << (CHAR_LITERAL - 64)) | (1L << (STRING_LITERAL - 64)) | (1L << (TEXT_BLOCK - 64)) | (1L << (NULL_LITERAL - 64)) | (1L << (LPAREN - 64)) | (1L << (LBRACE - 64)) | (1L << (SEMI - 64)) | (1L << (LT - 64)) | (1L << (BANG - 64)) | (1L << (TILDE - 64)) | (1L << (INC - 64)) | (1L << (DEC - 64)) | (1L << (ADD - 64)) | (1L << (SUB - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
				{
				{
				setState(1033);
				blockStatement();
				}
				}
				setState(1038);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(1039);
			match(RBRACE);
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

	public static class BlockStatementContext extends ParserRuleContext {
		public LocalVariableDeclarationContext localVariableDeclaration() {
			return getRuleContext(LocalVariableDeclarationContext.class,0);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public LocalTypeDeclarationContext localTypeDeclaration() {
			return getRuleContext(LocalTypeDeclarationContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public BlockStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_blockStatement; }
	}

	public final BlockStatementContext blockStatement() throws RecognitionException {
		BlockStatementContext _localctx = new BlockStatementContext(_ctx, getState());
		enterRule(_localctx, 158, RULE_blockStatement);
		try {
			setState(1046);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,119,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1041);
				localVariableDeclaration();
				setState(1042);
				match(SEMI);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1044);
				localTypeDeclaration();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1045);
				statement();
				}
				break;
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

	public static class LocalVariableDeclarationContext extends ParserRuleContext {
		public TerminalNode VAR() { return getToken(JavaParser.VAR, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(JavaParser.ASSIGN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public VariableDeclaratorsContext variableDeclarators() {
			return getRuleContext(VariableDeclaratorsContext.class,0);
		}
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public LocalVariableDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_localVariableDeclaration; }
	}

	public final LocalVariableDeclarationContext localVariableDeclaration() throws RecognitionException {
		LocalVariableDeclarationContext _localctx = new LocalVariableDeclarationContext(_ctx, getState());
		enterRule(_localctx, 160, RULE_localVariableDeclaration);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1051);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,120,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1048);
					variableModifier();
					}
					} 
				}
				setState(1053);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,120,_ctx);
			}
			setState(1062);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,121,_ctx) ) {
			case 1:
				{
				setState(1054);
				match(VAR);
				setState(1055);
				identifier();
				setState(1056);
				match(ASSIGN);
				setState(1057);
				expression(0);
				}
				break;
			case 2:
				{
				setState(1059);
				typeType();
				setState(1060);
				variableDeclarators();
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

	public static class IdentifierContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(JavaParser.IDENTIFIER, 0); }
		public TerminalNode MODULE() { return getToken(JavaParser.MODULE, 0); }
		public TerminalNode OPEN() { return getToken(JavaParser.OPEN, 0); }
		public TerminalNode REQUIRES() { return getToken(JavaParser.REQUIRES, 0); }
		public TerminalNode EXPORTS() { return getToken(JavaParser.EXPORTS, 0); }
		public TerminalNode OPENS() { return getToken(JavaParser.OPENS, 0); }
		public TerminalNode TO() { return getToken(JavaParser.TO, 0); }
		public TerminalNode USES() { return getToken(JavaParser.USES, 0); }
		public TerminalNode PROVIDES() { return getToken(JavaParser.PROVIDES, 0); }
		public TerminalNode WITH() { return getToken(JavaParser.WITH, 0); }
		public TerminalNode TRANSITIVE() { return getToken(JavaParser.TRANSITIVE, 0); }
		public TerminalNode YIELD() { return getToken(JavaParser.YIELD, 0); }
		public TerminalNode SEALED() { return getToken(JavaParser.SEALED, 0); }
		public TerminalNode PERMITS() { return getToken(JavaParser.PERMITS, 0); }
		public TerminalNode RECORD() { return getToken(JavaParser.RECORD, 0); }
		public TerminalNode VAR() { return getToken(JavaParser.VAR, 0); }
		public IdentifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identifier; }
	}

	public final IdentifierContext identifier() throws RecognitionException {
		IdentifierContext _localctx = new IdentifierContext(_ctx, getState());
		enterRule(_localctx, 162, RULE_identifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1064);
			_la = _input.LA(1);
			if ( !(((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==IDENTIFIER) ) {
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

	public static class TypeIdentifierContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(JavaParser.IDENTIFIER, 0); }
		public TerminalNode MODULE() { return getToken(JavaParser.MODULE, 0); }
		public TerminalNode OPEN() { return getToken(JavaParser.OPEN, 0); }
		public TerminalNode REQUIRES() { return getToken(JavaParser.REQUIRES, 0); }
		public TerminalNode EXPORTS() { return getToken(JavaParser.EXPORTS, 0); }
		public TerminalNode OPENS() { return getToken(JavaParser.OPENS, 0); }
		public TerminalNode TO() { return getToken(JavaParser.TO, 0); }
		public TerminalNode USES() { return getToken(JavaParser.USES, 0); }
		public TerminalNode PROVIDES() { return getToken(JavaParser.PROVIDES, 0); }
		public TerminalNode WITH() { return getToken(JavaParser.WITH, 0); }
		public TerminalNode TRANSITIVE() { return getToken(JavaParser.TRANSITIVE, 0); }
		public TerminalNode SEALED() { return getToken(JavaParser.SEALED, 0); }
		public TerminalNode PERMITS() { return getToken(JavaParser.PERMITS, 0); }
		public TerminalNode RECORD() { return getToken(JavaParser.RECORD, 0); }
		public TypeIdentifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeIdentifier; }
	}

	public final TypeIdentifierContext typeIdentifier() throws RecognitionException {
		TypeIdentifierContext _localctx = new TypeIdentifierContext(_ctx, getState());
		enterRule(_localctx, 164, RULE_typeIdentifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1066);
			_la = _input.LA(1);
			if ( !(((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==IDENTIFIER) ) {
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

	public static class LocalTypeDeclarationContext extends ParserRuleContext {
		public ClassDeclarationContext classDeclaration() {
			return getRuleContext(ClassDeclarationContext.class,0);
		}
		public InterfaceDeclarationContext interfaceDeclaration() {
			return getRuleContext(InterfaceDeclarationContext.class,0);
		}
		public RecordDeclarationContext recordDeclaration() {
			return getRuleContext(RecordDeclarationContext.class,0);
		}
		public List<ClassOrInterfaceModifierContext> classOrInterfaceModifier() {
			return getRuleContexts(ClassOrInterfaceModifierContext.class);
		}
		public ClassOrInterfaceModifierContext classOrInterfaceModifier(int i) {
			return getRuleContext(ClassOrInterfaceModifierContext.class,i);
		}
		public LocalTypeDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_localTypeDeclaration; }
	}

	public final LocalTypeDeclarationContext localTypeDeclaration() throws RecognitionException {
		LocalTypeDeclarationContext _localctx = new LocalTypeDeclarationContext(_ctx, getState());
		enterRule(_localctx, 166, RULE_localTypeDeclaration);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1071);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,122,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1068);
					classOrInterfaceModifier();
					}
					} 
				}
				setState(1073);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,122,_ctx);
			}
			setState(1077);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case CLASS:
				{
				setState(1074);
				classDeclaration();
				}
				break;
			case INTERFACE:
				{
				setState(1075);
				interfaceDeclaration();
				}
				break;
			case RECORD:
				{
				setState(1076);
				recordDeclaration();
				}
				break;
			default:
				throw new NoViableAltException(this);
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

	public static class StatementContext extends ParserRuleContext {
		public BlockContext blockLabel;
		public ExpressionContext statementExpression;
		public IdentifierContext identifierLabel;
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode ASSERT() { return getToken(JavaParser.ASSERT, 0); }
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public TerminalNode COLON() { return getToken(JavaParser.COLON, 0); }
		public TerminalNode IF() { return getToken(JavaParser.IF, 0); }
		public ParExpressionContext parExpression() {
			return getRuleContext(ParExpressionContext.class,0);
		}
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public TerminalNode ELSE() { return getToken(JavaParser.ELSE, 0); }
		public TerminalNode FOR() { return getToken(JavaParser.FOR, 0); }
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public ForControlContext forControl() {
			return getRuleContext(ForControlContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public TerminalNode WHILE() { return getToken(JavaParser.WHILE, 0); }
		public TerminalNode DO() { return getToken(JavaParser.DO, 0); }
		public TerminalNode TRY() { return getToken(JavaParser.TRY, 0); }
		public FinallyBlockContext finallyBlock() {
			return getRuleContext(FinallyBlockContext.class,0);
		}
		public List<CatchClauseContext> catchClause() {
			return getRuleContexts(CatchClauseContext.class);
		}
		public CatchClauseContext catchClause(int i) {
			return getRuleContext(CatchClauseContext.class,i);
		}
		public ResourceSpecificationContext resourceSpecification() {
			return getRuleContext(ResourceSpecificationContext.class,0);
		}
		public TerminalNode SWITCH() { return getToken(JavaParser.SWITCH, 0); }
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<SwitchBlockStatementGroupContext> switchBlockStatementGroup() {
			return getRuleContexts(SwitchBlockStatementGroupContext.class);
		}
		public SwitchBlockStatementGroupContext switchBlockStatementGroup(int i) {
			return getRuleContext(SwitchBlockStatementGroupContext.class,i);
		}
		public List<SwitchLabelContext> switchLabel() {
			return getRuleContexts(SwitchLabelContext.class);
		}
		public SwitchLabelContext switchLabel(int i) {
			return getRuleContext(SwitchLabelContext.class,i);
		}
		public TerminalNode SYNCHRONIZED() { return getToken(JavaParser.SYNCHRONIZED, 0); }
		public TerminalNode RETURN() { return getToken(JavaParser.RETURN, 0); }
		public TerminalNode THROW() { return getToken(JavaParser.THROW, 0); }
		public TerminalNode BREAK() { return getToken(JavaParser.BREAK, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode CONTINUE() { return getToken(JavaParser.CONTINUE, 0); }
		public TerminalNode YIELD() { return getToken(JavaParser.YIELD, 0); }
		public SwitchExpressionContext switchExpression() {
			return getRuleContext(SwitchExpressionContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 168, RULE_statement);
		int _la;
		try {
			int _alt;
			setState(1192);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,137,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1079);
				((StatementContext)_localctx).blockLabel = block();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1080);
				match(ASSERT);
				setState(1081);
				expression(0);
				setState(1084);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==COLON) {
					{
					setState(1082);
					match(COLON);
					setState(1083);
					expression(0);
					}
				}

				setState(1086);
				match(SEMI);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1088);
				match(IF);
				setState(1089);
				parExpression();
				setState(1090);
				statement();
				setState(1093);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,125,_ctx) ) {
				case 1:
					{
					setState(1091);
					match(ELSE);
					setState(1092);
					statement();
					}
					break;
				}
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1095);
				match(FOR);
				setState(1096);
				match(LPAREN);
				setState(1097);
				forControl();
				setState(1098);
				match(RPAREN);
				setState(1099);
				statement();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1101);
				match(WHILE);
				setState(1102);
				parExpression();
				setState(1103);
				statement();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(1105);
				match(DO);
				setState(1106);
				statement();
				setState(1107);
				match(WHILE);
				setState(1108);
				parExpression();
				setState(1109);
				match(SEMI);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(1111);
				match(TRY);
				setState(1112);
				block();
				setState(1122);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case CATCH:
					{
					setState(1114); 
					_errHandler.sync(this);
					_la = _input.LA(1);
					do {
						{
						{
						setState(1113);
						catchClause();
						}
						}
						setState(1116); 
						_errHandler.sync(this);
						_la = _input.LA(1);
					} while ( _la==CATCH );
					setState(1119);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==FINALLY) {
						{
						setState(1118);
						finallyBlock();
						}
					}

					}
					break;
				case FINALLY:
					{
					setState(1121);
					finallyBlock();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(1124);
				match(TRY);
				setState(1125);
				resourceSpecification();
				setState(1126);
				block();
				setState(1130);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==CATCH) {
					{
					{
					setState(1127);
					catchClause();
					}
					}
					setState(1132);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(1134);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==FINALLY) {
					{
					setState(1133);
					finallyBlock();
					}
				}

				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(1136);
				match(SWITCH);
				setState(1137);
				parExpression();
				setState(1138);
				match(LBRACE);
				setState(1142);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,131,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1139);
						switchBlockStatementGroup();
						}
						} 
					}
					setState(1144);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,131,_ctx);
				}
				setState(1148);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==CASE || _la==DEFAULT) {
					{
					{
					setState(1145);
					switchLabel();
					}
					}
					setState(1150);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(1151);
				match(RBRACE);
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(1153);
				match(SYNCHRONIZED);
				setState(1154);
				parExpression();
				setState(1155);
				block();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(1157);
				match(RETURN);
				setState(1159);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
					{
					setState(1158);
					expression(0);
					}
				}

				setState(1161);
				match(SEMI);
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(1162);
				match(THROW);
				setState(1163);
				expression(0);
				setState(1164);
				match(SEMI);
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(1166);
				match(BREAK);
				setState(1168);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==IDENTIFIER) {
					{
					setState(1167);
					identifier();
					}
				}

				setState(1170);
				match(SEMI);
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(1171);
				match(CONTINUE);
				setState(1173);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==IDENTIFIER) {
					{
					setState(1172);
					identifier();
					}
				}

				setState(1175);
				match(SEMI);
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(1176);
				match(YIELD);
				setState(1177);
				expression(0);
				setState(1178);
				match(SEMI);
				}
				break;
			case 16:
				enterOuterAlt(_localctx, 16);
				{
				setState(1180);
				match(SEMI);
				}
				break;
			case 17:
				enterOuterAlt(_localctx, 17);
				{
				setState(1181);
				((StatementContext)_localctx).statementExpression = expression(0);
				setState(1182);
				match(SEMI);
				}
				break;
			case 18:
				enterOuterAlt(_localctx, 18);
				{
				setState(1184);
				switchExpression();
				setState(1186);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,136,_ctx) ) {
				case 1:
					{
					setState(1185);
					match(SEMI);
					}
					break;
				}
				}
				break;
			case 19:
				enterOuterAlt(_localctx, 19);
				{
				setState(1188);
				((StatementContext)_localctx).identifierLabel = identifier();
				setState(1189);
				match(COLON);
				setState(1190);
				statement();
				}
				break;
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

	public static class CatchClauseContext extends ParserRuleContext {
		public TerminalNode CATCH() { return getToken(JavaParser.CATCH, 0); }
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public CatchTypeContext catchType() {
			return getRuleContext(CatchTypeContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public CatchClauseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_catchClause; }
	}

	public final CatchClauseContext catchClause() throws RecognitionException {
		CatchClauseContext _localctx = new CatchClauseContext(_ctx, getState());
		enterRule(_localctx, 170, RULE_catchClause);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1194);
			match(CATCH);
			setState(1195);
			match(LPAREN);
			setState(1199);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,138,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1196);
					variableModifier();
					}
					} 
				}
				setState(1201);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,138,_ctx);
			}
			setState(1202);
			catchType();
			setState(1203);
			identifier();
			setState(1204);
			match(RPAREN);
			setState(1205);
			block();
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

	public static class CatchTypeContext extends ParserRuleContext {
		public List<QualifiedNameContext> qualifiedName() {
			return getRuleContexts(QualifiedNameContext.class);
		}
		public QualifiedNameContext qualifiedName(int i) {
			return getRuleContext(QualifiedNameContext.class,i);
		}
		public List<TerminalNode> BITOR() { return getTokens(JavaParser.BITOR); }
		public TerminalNode BITOR(int i) {
			return getToken(JavaParser.BITOR, i);
		}
		public CatchTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_catchType; }
	}

	public final CatchTypeContext catchType() throws RecognitionException {
		CatchTypeContext _localctx = new CatchTypeContext(_ctx, getState());
		enterRule(_localctx, 172, RULE_catchType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1207);
			qualifiedName();
			setState(1212);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==BITOR) {
				{
				{
				setState(1208);
				match(BITOR);
				setState(1209);
				qualifiedName();
				}
				}
				setState(1214);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class FinallyBlockContext extends ParserRuleContext {
		public TerminalNode FINALLY() { return getToken(JavaParser.FINALLY, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public FinallyBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_finallyBlock; }
	}

	public final FinallyBlockContext finallyBlock() throws RecognitionException {
		FinallyBlockContext _localctx = new FinallyBlockContext(_ctx, getState());
		enterRule(_localctx, 174, RULE_finallyBlock);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1215);
			match(FINALLY);
			setState(1216);
			block();
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

	public static class ResourceSpecificationContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public ResourcesContext resources() {
			return getRuleContext(ResourcesContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public TerminalNode SEMI() { return getToken(JavaParser.SEMI, 0); }
		public ResourceSpecificationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_resourceSpecification; }
	}

	public final ResourceSpecificationContext resourceSpecification() throws RecognitionException {
		ResourceSpecificationContext _localctx = new ResourceSpecificationContext(_ctx, getState());
		enterRule(_localctx, 176, RULE_resourceSpecification);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1218);
			match(LPAREN);
			setState(1219);
			resources();
			setState(1221);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SEMI) {
				{
				setState(1220);
				match(SEMI);
				}
			}

			setState(1223);
			match(RPAREN);
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

	public static class ResourcesContext extends ParserRuleContext {
		public List<ResourceContext> resource() {
			return getRuleContexts(ResourceContext.class);
		}
		public ResourceContext resource(int i) {
			return getRuleContext(ResourceContext.class,i);
		}
		public List<TerminalNode> SEMI() { return getTokens(JavaParser.SEMI); }
		public TerminalNode SEMI(int i) {
			return getToken(JavaParser.SEMI, i);
		}
		public ResourcesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_resources; }
	}

	public final ResourcesContext resources() throws RecognitionException {
		ResourcesContext _localctx = new ResourcesContext(_ctx, getState());
		enterRule(_localctx, 178, RULE_resources);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1225);
			resource();
			setState(1230);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,141,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1226);
					match(SEMI);
					setState(1227);
					resource();
					}
					} 
				}
				setState(1232);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,141,_ctx);
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

	public static class ResourceContext extends ParserRuleContext {
		public TerminalNode ASSIGN() { return getToken(JavaParser.ASSIGN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public ClassOrInterfaceTypeContext classOrInterfaceType() {
			return getRuleContext(ClassOrInterfaceTypeContext.class,0);
		}
		public VariableDeclaratorIdContext variableDeclaratorId() {
			return getRuleContext(VariableDeclaratorIdContext.class,0);
		}
		public TerminalNode VAR() { return getToken(JavaParser.VAR, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public ResourceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_resource; }
	}

	public final ResourceContext resource() throws RecognitionException {
		ResourceContext _localctx = new ResourceContext(_ctx, getState());
		enterRule(_localctx, 180, RULE_resource);
		try {
			int _alt;
			setState(1250);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,144,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1236);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,142,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1233);
						variableModifier();
						}
						} 
					}
					setState(1238);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,142,_ctx);
				}
				setState(1244);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,143,_ctx) ) {
				case 1:
					{
					setState(1239);
					classOrInterfaceType();
					setState(1240);
					variableDeclaratorId();
					}
					break;
				case 2:
					{
					setState(1242);
					match(VAR);
					setState(1243);
					identifier();
					}
					break;
				}
				setState(1246);
				match(ASSIGN);
				setState(1247);
				expression(0);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1249);
				identifier();
				}
				break;
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

	public static class SwitchBlockStatementGroupContext extends ParserRuleContext {
		public List<SwitchLabelContext> switchLabel() {
			return getRuleContexts(SwitchLabelContext.class);
		}
		public SwitchLabelContext switchLabel(int i) {
			return getRuleContext(SwitchLabelContext.class,i);
		}
		public List<BlockStatementContext> blockStatement() {
			return getRuleContexts(BlockStatementContext.class);
		}
		public BlockStatementContext blockStatement(int i) {
			return getRuleContext(BlockStatementContext.class,i);
		}
		public SwitchBlockStatementGroupContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_switchBlockStatementGroup; }
	}

	public final SwitchBlockStatementGroupContext switchBlockStatementGroup() throws RecognitionException {
		SwitchBlockStatementGroupContext _localctx = new SwitchBlockStatementGroupContext(_ctx, getState());
		enterRule(_localctx, 182, RULE_switchBlockStatementGroup);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1253); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(1252);
				switchLabel();
				}
				}
				setState(1255); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==CASE || _la==DEFAULT );
			setState(1258); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(1257);
				blockStatement();
				}
				}
				setState(1260); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << ASSERT) | (1L << BOOLEAN) | (1L << BREAK) | (1L << BYTE) | (1L << CHAR) | (1L << CLASS) | (1L << CONTINUE) | (1L << DO) | (1L << DOUBLE) | (1L << FINAL) | (1L << FLOAT) | (1L << FOR) | (1L << IF) | (1L << INT) | (1L << INTERFACE) | (1L << LONG) | (1L << NEW) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << RETURN) | (1L << SHORT) | (1L << STATIC) | (1L << STRICTFP) | (1L << SUPER) | (1L << SWITCH) | (1L << SYNCHRONIZED) | (1L << THIS) | (1L << THROW) | (1L << TRY) | (1L << VOID) | (1L << WHILE) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (DECIMAL_LITERAL - 64)) | (1L << (HEX_LITERAL - 64)) | (1L << (OCT_LITERAL - 64)) | (1L << (BINARY_LITERAL - 64)) | (1L << (FLOAT_LITERAL - 64)) | (1L << (HEX_FLOAT_LITERAL - 64)) | (1L << (BOOL_LITERAL - 64)) | (1L << (CHAR_LITERAL - 64)) | (1L << (STRING_LITERAL - 64)) | (1L << (TEXT_BLOCK - 64)) | (1L << (NULL_LITERAL - 64)) | (1L << (LPAREN - 64)) | (1L << (LBRACE - 64)) | (1L << (SEMI - 64)) | (1L << (LT - 64)) | (1L << (BANG - 64)) | (1L << (TILDE - 64)) | (1L << (INC - 64)) | (1L << (DEC - 64)) | (1L << (ADD - 64)) | (1L << (SUB - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER );
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

	public static class SwitchLabelContext extends ParserRuleContext {
		public ExpressionContext constantExpression;
		public Token enumConstantName;
		public IdentifierContext varName;
		public TerminalNode CASE() { return getToken(JavaParser.CASE, 0); }
		public TerminalNode COLON() { return getToken(JavaParser.COLON, 0); }
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(JavaParser.IDENTIFIER, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode DEFAULT() { return getToken(JavaParser.DEFAULT, 0); }
		public SwitchLabelContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_switchLabel; }
	}

	public final SwitchLabelContext switchLabel() throws RecognitionException {
		SwitchLabelContext _localctx = new SwitchLabelContext(_ctx, getState());
		enterRule(_localctx, 184, RULE_switchLabel);
		try {
			setState(1273);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case CASE:
				enterOuterAlt(_localctx, 1);
				{
				setState(1262);
				match(CASE);
				setState(1268);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,147,_ctx) ) {
				case 1:
					{
					setState(1263);
					((SwitchLabelContext)_localctx).constantExpression = expression(0);
					}
					break;
				case 2:
					{
					setState(1264);
					((SwitchLabelContext)_localctx).enumConstantName = match(IDENTIFIER);
					}
					break;
				case 3:
					{
					setState(1265);
					typeType();
					setState(1266);
					((SwitchLabelContext)_localctx).varName = identifier();
					}
					break;
				}
				setState(1270);
				match(COLON);
				}
				break;
			case DEFAULT:
				enterOuterAlt(_localctx, 2);
				{
				setState(1271);
				match(DEFAULT);
				setState(1272);
				match(COLON);
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

	public static class ForControlContext extends ParserRuleContext {
		public ExpressionListContext forUpdate;
		public EnhancedForControlContext enhancedForControl() {
			return getRuleContext(EnhancedForControlContext.class,0);
		}
		public List<TerminalNode> SEMI() { return getTokens(JavaParser.SEMI); }
		public TerminalNode SEMI(int i) {
			return getToken(JavaParser.SEMI, i);
		}
		public ForInitContext forInit() {
			return getRuleContext(ForInitContext.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public ExpressionListContext expressionList() {
			return getRuleContext(ExpressionListContext.class,0);
		}
		public ForControlContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forControl; }
	}

	public final ForControlContext forControl() throws RecognitionException {
		ForControlContext _localctx = new ForControlContext(_ctx, getState());
		enterRule(_localctx, 186, RULE_forControl);
		int _la;
		try {
			setState(1287);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,152,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1275);
				enhancedForControl();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1277);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FINAL - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
					{
					setState(1276);
					forInit();
					}
				}

				setState(1279);
				match(SEMI);
				setState(1281);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
					{
					setState(1280);
					expression(0);
					}
				}

				setState(1283);
				match(SEMI);
				setState(1285);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
					{
					setState(1284);
					((ForControlContext)_localctx).forUpdate = expressionList();
					}
				}

				}
				break;
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

	public static class ForInitContext extends ParserRuleContext {
		public LocalVariableDeclarationContext localVariableDeclaration() {
			return getRuleContext(LocalVariableDeclarationContext.class,0);
		}
		public ExpressionListContext expressionList() {
			return getRuleContext(ExpressionListContext.class,0);
		}
		public ForInitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forInit; }
	}

	public final ForInitContext forInit() throws RecognitionException {
		ForInitContext _localctx = new ForInitContext(_ctx, getState());
		enterRule(_localctx, 188, RULE_forInit);
		try {
			setState(1291);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,153,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1289);
				localVariableDeclaration();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1290);
				expressionList();
				}
				break;
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

	public static class EnhancedForControlContext extends ParserRuleContext {
		public VariableDeclaratorIdContext variableDeclaratorId() {
			return getRuleContext(VariableDeclaratorIdContext.class,0);
		}
		public TerminalNode COLON() { return getToken(JavaParser.COLON, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public TerminalNode VAR() { return getToken(JavaParser.VAR, 0); }
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public EnhancedForControlContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enhancedForControl; }
	}

	public final EnhancedForControlContext enhancedForControl() throws RecognitionException {
		EnhancedForControlContext _localctx = new EnhancedForControlContext(_ctx, getState());
		enterRule(_localctx, 190, RULE_enhancedForControl);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1296);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,154,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1293);
					variableModifier();
					}
					} 
				}
				setState(1298);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,154,_ctx);
			}
			setState(1301);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,155,_ctx) ) {
			case 1:
				{
				setState(1299);
				typeType();
				}
				break;
			case 2:
				{
				setState(1300);
				match(VAR);
				}
				break;
			}
			setState(1303);
			variableDeclaratorId();
			setState(1304);
			match(COLON);
			setState(1305);
			expression(0);
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

	public static class ParExpressionContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public ParExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parExpression; }
	}

	public final ParExpressionContext parExpression() throws RecognitionException {
		ParExpressionContext _localctx = new ParExpressionContext(_ctx, getState());
		enterRule(_localctx, 192, RULE_parExpression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1307);
			match(LPAREN);
			setState(1308);
			expression(0);
			setState(1309);
			match(RPAREN);
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

	public static class ExpressionListContext extends ParserRuleContext {
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public ExpressionListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expressionList; }
	}

	public final ExpressionListContext expressionList() throws RecognitionException {
		ExpressionListContext _localctx = new ExpressionListContext(_ctx, getState());
		enterRule(_localctx, 194, RULE_expressionList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1311);
			expression(0);
			setState(1316);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(1312);
				match(COMMA);
				setState(1313);
				expression(0);
				}
				}
				setState(1318);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class MethodCallContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public ExpressionListContext expressionList() {
			return getRuleContext(ExpressionListContext.class,0);
		}
		public TerminalNode THIS() { return getToken(JavaParser.THIS, 0); }
		public TerminalNode SUPER() { return getToken(JavaParser.SUPER, 0); }
		public MethodCallContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_methodCall; }
	}

	public final MethodCallContext methodCall() throws RecognitionException {
		MethodCallContext _localctx = new MethodCallContext(_ctx, getState());
		enterRule(_localctx, 196, RULE_methodCall);
		int _la;
		try {
			setState(1338);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1319);
				identifier();
				setState(1320);
				match(LPAREN);
				setState(1322);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
					{
					setState(1321);
					expressionList();
					}
				}

				setState(1324);
				match(RPAREN);
				}
				break;
			case THIS:
				enterOuterAlt(_localctx, 2);
				{
				setState(1326);
				match(THIS);
				setState(1327);
				match(LPAREN);
				setState(1329);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
					{
					setState(1328);
					expressionList();
					}
				}

				setState(1331);
				match(RPAREN);
				}
				break;
			case SUPER:
				enterOuterAlt(_localctx, 3);
				{
				setState(1332);
				match(SUPER);
				setState(1333);
				match(LPAREN);
				setState(1335);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
					{
					setState(1334);
					expressionList();
					}
				}

				setState(1337);
				match(RPAREN);
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

	public static class ExpressionContext extends ParserRuleContext {
		public Token prefix;
		public Token bop;
		public Token postfix;
		public PrimaryContext primary() {
			return getRuleContext(PrimaryContext.class,0);
		}
		public MethodCallContext methodCall() {
			return getRuleContext(MethodCallContext.class,0);
		}
		public TerminalNode NEW() { return getToken(JavaParser.NEW, 0); }
		public CreatorContext creator() {
			return getRuleContext(CreatorContext.class,0);
		}
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public List<TypeTypeContext> typeType() {
			return getRuleContexts(TypeTypeContext.class);
		}
		public TypeTypeContext typeType(int i) {
			return getRuleContext(TypeTypeContext.class,i);
		}
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public List<TerminalNode> BITAND() { return getTokens(JavaParser.BITAND); }
		public TerminalNode BITAND(int i) {
			return getToken(JavaParser.BITAND, i);
		}
		public TerminalNode ADD() { return getToken(JavaParser.ADD, 0); }
		public TerminalNode SUB() { return getToken(JavaParser.SUB, 0); }
		public TerminalNode INC() { return getToken(JavaParser.INC, 0); }
		public TerminalNode DEC() { return getToken(JavaParser.DEC, 0); }
		public TerminalNode TILDE() { return getToken(JavaParser.TILDE, 0); }
		public TerminalNode BANG() { return getToken(JavaParser.BANG, 0); }
		public LambdaExpressionContext lambdaExpression() {
			return getRuleContext(LambdaExpressionContext.class,0);
		}
		public SwitchExpressionContext switchExpression() {
			return getRuleContext(SwitchExpressionContext.class,0);
		}
		public TerminalNode COLONCOLON() { return getToken(JavaParser.COLONCOLON, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TypeArgumentsContext typeArguments() {
			return getRuleContext(TypeArgumentsContext.class,0);
		}
		public ClassTypeContext classType() {
			return getRuleContext(ClassTypeContext.class,0);
		}
		public TerminalNode MUL() { return getToken(JavaParser.MUL, 0); }
		public TerminalNode DIV() { return getToken(JavaParser.DIV, 0); }
		public TerminalNode MOD() { return getToken(JavaParser.MOD, 0); }
		public List<TerminalNode> LT() { return getTokens(JavaParser.LT); }
		public TerminalNode LT(int i) {
			return getToken(JavaParser.LT, i);
		}
		public List<TerminalNode> GT() { return getTokens(JavaParser.GT); }
		public TerminalNode GT(int i) {
			return getToken(JavaParser.GT, i);
		}
		public TerminalNode LE() { return getToken(JavaParser.LE, 0); }
		public TerminalNode GE() { return getToken(JavaParser.GE, 0); }
		public TerminalNode EQUAL() { return getToken(JavaParser.EQUAL, 0); }
		public TerminalNode NOTEQUAL() { return getToken(JavaParser.NOTEQUAL, 0); }
		public TerminalNode CARET() { return getToken(JavaParser.CARET, 0); }
		public TerminalNode BITOR() { return getToken(JavaParser.BITOR, 0); }
		public TerminalNode AND() { return getToken(JavaParser.AND, 0); }
		public TerminalNode OR() { return getToken(JavaParser.OR, 0); }
		public TerminalNode COLON() { return getToken(JavaParser.COLON, 0); }
		public TerminalNode QUESTION() { return getToken(JavaParser.QUESTION, 0); }
		public TerminalNode ASSIGN() { return getToken(JavaParser.ASSIGN, 0); }
		public TerminalNode ADD_ASSIGN() { return getToken(JavaParser.ADD_ASSIGN, 0); }
		public TerminalNode SUB_ASSIGN() { return getToken(JavaParser.SUB_ASSIGN, 0); }
		public TerminalNode MUL_ASSIGN() { return getToken(JavaParser.MUL_ASSIGN, 0); }
		public TerminalNode DIV_ASSIGN() { return getToken(JavaParser.DIV_ASSIGN, 0); }
		public TerminalNode AND_ASSIGN() { return getToken(JavaParser.AND_ASSIGN, 0); }
		public TerminalNode OR_ASSIGN() { return getToken(JavaParser.OR_ASSIGN, 0); }
		public TerminalNode XOR_ASSIGN() { return getToken(JavaParser.XOR_ASSIGN, 0); }
		public TerminalNode RSHIFT_ASSIGN() { return getToken(JavaParser.RSHIFT_ASSIGN, 0); }
		public TerminalNode URSHIFT_ASSIGN() { return getToken(JavaParser.URSHIFT_ASSIGN, 0); }
		public TerminalNode LSHIFT_ASSIGN() { return getToken(JavaParser.LSHIFT_ASSIGN, 0); }
		public TerminalNode MOD_ASSIGN() { return getToken(JavaParser.MOD_ASSIGN, 0); }
		public TerminalNode DOT() { return getToken(JavaParser.DOT, 0); }
		public TerminalNode THIS() { return getToken(JavaParser.THIS, 0); }
		public InnerCreatorContext innerCreator() {
			return getRuleContext(InnerCreatorContext.class,0);
		}
		public TerminalNode SUPER() { return getToken(JavaParser.SUPER, 0); }
		public SuperSuffixContext superSuffix() {
			return getRuleContext(SuperSuffixContext.class,0);
		}
		public ExplicitGenericInvocationContext explicitGenericInvocation() {
			return getRuleContext(ExplicitGenericInvocationContext.class,0);
		}
		public NonWildcardTypeArgumentsContext nonWildcardTypeArguments() {
			return getRuleContext(NonWildcardTypeArgumentsContext.class,0);
		}
		public TerminalNode LBRACK() { return getToken(JavaParser.LBRACK, 0); }
		public TerminalNode RBRACK() { return getToken(JavaParser.RBRACK, 0); }
		public TerminalNode INSTANCEOF() { return getToken(JavaParser.INSTANCEOF, 0); }
		public PatternContext pattern() {
			return getRuleContext(PatternContext.class,0);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	}

	public final ExpressionContext expression() throws RecognitionException {
		return expression(0);
	}

	private ExpressionContext expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExpressionContext _localctx = new ExpressionContext(_ctx, _parentState);
		ExpressionContext _prevctx = _localctx;
		int _startState = 198;
		enterRecursionRule(_localctx, 198, RULE_expression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1385);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,166,_ctx) ) {
			case 1:
				{
				setState(1341);
				primary();
				}
				break;
			case 2:
				{
				setState(1342);
				methodCall();
				}
				break;
			case 3:
				{
				setState(1343);
				match(NEW);
				setState(1344);
				creator();
				}
				break;
			case 4:
				{
				setState(1345);
				match(LPAREN);
				setState(1349);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,161,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1346);
						annotation();
						}
						} 
					}
					setState(1351);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,161,_ctx);
				}
				setState(1352);
				typeType();
				setState(1357);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==BITAND) {
					{
					{
					setState(1353);
					match(BITAND);
					setState(1354);
					typeType();
					}
					}
					setState(1359);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(1360);
				match(RPAREN);
				setState(1361);
				expression(22);
				}
				break;
			case 5:
				{
				setState(1363);
				((ExpressionContext)_localctx).prefix = _input.LT(1);
				_la = _input.LA(1);
				if ( !(((((_la - 100)) & ~0x3f) == 0 && ((1L << (_la - 100)) & ((1L << (INC - 100)) | (1L << (DEC - 100)) | (1L << (ADD - 100)) | (1L << (SUB - 100)))) != 0)) ) {
					((ExpressionContext)_localctx).prefix = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(1364);
				expression(20);
				}
				break;
			case 6:
				{
				setState(1365);
				((ExpressionContext)_localctx).prefix = _input.LT(1);
				_la = _input.LA(1);
				if ( !(_la==BANG || _la==TILDE) ) {
					((ExpressionContext)_localctx).prefix = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(1366);
				expression(19);
				}
				break;
			case 7:
				{
				setState(1367);
				lambdaExpression();
				}
				break;
			case 8:
				{
				setState(1368);
				switchExpression();
				}
				break;
			case 9:
				{
				setState(1369);
				typeType();
				setState(1370);
				match(COLONCOLON);
				setState(1376);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case MODULE:
				case OPEN:
				case REQUIRES:
				case EXPORTS:
				case OPENS:
				case TO:
				case USES:
				case PROVIDES:
				case WITH:
				case TRANSITIVE:
				case VAR:
				case YIELD:
				case RECORD:
				case SEALED:
				case PERMITS:
				case LT:
				case IDENTIFIER:
					{
					setState(1372);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==LT) {
						{
						setState(1371);
						typeArguments();
						}
					}

					setState(1374);
					identifier();
					}
					break;
				case NEW:
					{
					setState(1375);
					match(NEW);
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				break;
			case 10:
				{
				setState(1378);
				classType();
				setState(1379);
				match(COLONCOLON);
				setState(1381);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==LT) {
					{
					setState(1380);
					typeArguments();
					}
				}

				setState(1383);
				match(NEW);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(1470);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,173,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(1468);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,172,_ctx) ) {
					case 1:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1387);
						if (!(precpred(_ctx, 18))) throw new FailedPredicateException(this, "precpred(_ctx, 18)");
						setState(1388);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !(((((_la - 104)) & ~0x3f) == 0 && ((1L << (_la - 104)) & ((1L << (MUL - 104)) | (1L << (DIV - 104)) | (1L << (MOD - 104)))) != 0)) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1389);
						expression(19);
						}
						break;
					case 2:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1390);
						if (!(precpred(_ctx, 17))) throw new FailedPredicateException(this, "precpred(_ctx, 17)");
						setState(1391);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==ADD || _la==SUB) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1392);
						expression(18);
						}
						break;
					case 3:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1393);
						if (!(precpred(_ctx, 16))) throw new FailedPredicateException(this, "precpred(_ctx, 16)");
						setState(1401);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,167,_ctx) ) {
						case 1:
							{
							setState(1394);
							match(LT);
							setState(1395);
							match(LT);
							}
							break;
						case 2:
							{
							setState(1396);
							match(GT);
							setState(1397);
							match(GT);
							setState(1398);
							match(GT);
							}
							break;
						case 3:
							{
							setState(1399);
							match(GT);
							setState(1400);
							match(GT);
							}
							break;
						}
						setState(1403);
						expression(17);
						}
						break;
					case 4:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1404);
						if (!(precpred(_ctx, 15))) throw new FailedPredicateException(this, "precpred(_ctx, 15)");
						setState(1405);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !(((((_la - 88)) & ~0x3f) == 0 && ((1L << (_la - 88)) & ((1L << (GT - 88)) | (1L << (LT - 88)) | (1L << (LE - 88)) | (1L << (GE - 88)))) != 0)) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1406);
						expression(16);
						}
						break;
					case 5:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1407);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(1408);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==EQUAL || _la==NOTEQUAL) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1409);
						expression(14);
						}
						break;
					case 6:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1410);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(1411);
						((ExpressionContext)_localctx).bop = match(BITAND);
						setState(1412);
						expression(13);
						}
						break;
					case 7:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1413);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(1414);
						((ExpressionContext)_localctx).bop = match(CARET);
						setState(1415);
						expression(12);
						}
						break;
					case 8:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1416);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(1417);
						((ExpressionContext)_localctx).bop = match(BITOR);
						setState(1418);
						expression(11);
						}
						break;
					case 9:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1419);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(1420);
						((ExpressionContext)_localctx).bop = match(AND);
						setState(1421);
						expression(10);
						}
						break;
					case 10:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1422);
						if (!(precpred(_ctx, 8))) throw new FailedPredicateException(this, "precpred(_ctx, 8)");
						setState(1423);
						((ExpressionContext)_localctx).bop = match(OR);
						setState(1424);
						expression(9);
						}
						break;
					case 11:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1425);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(1426);
						((ExpressionContext)_localctx).bop = match(QUESTION);
						setState(1427);
						expression(0);
						setState(1428);
						match(COLON);
						setState(1429);
						expression(7);
						}
						break;
					case 12:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1431);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(1432);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !(((((_la - 87)) & ~0x3f) == 0 && ((1L << (_la - 87)) & ((1L << (ASSIGN - 87)) | (1L << (ADD_ASSIGN - 87)) | (1L << (SUB_ASSIGN - 87)) | (1L << (MUL_ASSIGN - 87)) | (1L << (DIV_ASSIGN - 87)) | (1L << (AND_ASSIGN - 87)) | (1L << (OR_ASSIGN - 87)) | (1L << (XOR_ASSIGN - 87)) | (1L << (MOD_ASSIGN - 87)) | (1L << (LSHIFT_ASSIGN - 87)) | (1L << (RSHIFT_ASSIGN - 87)) | (1L << (URSHIFT_ASSIGN - 87)))) != 0)) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(1433);
						expression(6);
						}
						break;
					case 13:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1434);
						if (!(precpred(_ctx, 26))) throw new FailedPredicateException(this, "precpred(_ctx, 26)");
						setState(1435);
						((ExpressionContext)_localctx).bop = match(DOT);
						setState(1447);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,169,_ctx) ) {
						case 1:
							{
							setState(1436);
							identifier();
							}
							break;
						case 2:
							{
							setState(1437);
							methodCall();
							}
							break;
						case 3:
							{
							setState(1438);
							match(THIS);
							}
							break;
						case 4:
							{
							setState(1439);
							match(NEW);
							setState(1441);
							_errHandler.sync(this);
							_la = _input.LA(1);
							if (_la==LT) {
								{
								setState(1440);
								nonWildcardTypeArguments();
								}
							}

							setState(1443);
							innerCreator();
							}
							break;
						case 5:
							{
							setState(1444);
							match(SUPER);
							setState(1445);
							superSuffix();
							}
							break;
						case 6:
							{
							setState(1446);
							explicitGenericInvocation();
							}
							break;
						}
						}
						break;
					case 14:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1449);
						if (!(precpred(_ctx, 25))) throw new FailedPredicateException(this, "precpred(_ctx, 25)");
						setState(1450);
						match(LBRACK);
						setState(1451);
						expression(0);
						setState(1452);
						match(RBRACK);
						}
						break;
					case 15:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1454);
						if (!(precpred(_ctx, 21))) throw new FailedPredicateException(this, "precpred(_ctx, 21)");
						setState(1455);
						((ExpressionContext)_localctx).postfix = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==INC || _la==DEC) ) {
							((ExpressionContext)_localctx).postfix = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						}
						break;
					case 16:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1456);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(1457);
						((ExpressionContext)_localctx).bop = match(INSTANCEOF);
						setState(1460);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,170,_ctx) ) {
						case 1:
							{
							setState(1458);
							typeType();
							}
							break;
						case 2:
							{
							setState(1459);
							pattern();
							}
							break;
						}
						}
						break;
					case 17:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(1462);
						if (!(precpred(_ctx, 3))) throw new FailedPredicateException(this, "precpred(_ctx, 3)");
						setState(1463);
						match(COLONCOLON);
						setState(1465);
						_errHandler.sync(this);
						_la = _input.LA(1);
						if (_la==LT) {
							{
							setState(1464);
							typeArguments();
							}
						}

						setState(1467);
						identifier();
						}
						break;
					}
					} 
				}
				setState(1472);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,173,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class PatternContext extends ParserRuleContext {
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public PatternContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pattern; }
	}

	public final PatternContext pattern() throws RecognitionException {
		PatternContext _localctx = new PatternContext(_ctx, getState());
		enterRule(_localctx, 200, RULE_pattern);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1476);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,174,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1473);
					variableModifier();
					}
					} 
				}
				setState(1478);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,174,_ctx);
			}
			setState(1479);
			typeType();
			setState(1483);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,175,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1480);
					annotation();
					}
					} 
				}
				setState(1485);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,175,_ctx);
			}
			setState(1486);
			identifier();
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

	public static class LambdaExpressionContext extends ParserRuleContext {
		public LambdaParametersContext lambdaParameters() {
			return getRuleContext(LambdaParametersContext.class,0);
		}
		public TerminalNode ARROW() { return getToken(JavaParser.ARROW, 0); }
		public LambdaBodyContext lambdaBody() {
			return getRuleContext(LambdaBodyContext.class,0);
		}
		public LambdaExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lambdaExpression; }
	}

	public final LambdaExpressionContext lambdaExpression() throws RecognitionException {
		LambdaExpressionContext _localctx = new LambdaExpressionContext(_ctx, getState());
		enterRule(_localctx, 202, RULE_lambdaExpression);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1488);
			lambdaParameters();
			setState(1489);
			match(ARROW);
			setState(1490);
			lambdaBody();
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

	public static class LambdaParametersContext extends ParserRuleContext {
		public List<IdentifierContext> identifier() {
			return getRuleContexts(IdentifierContext.class);
		}
		public IdentifierContext identifier(int i) {
			return getRuleContext(IdentifierContext.class,i);
		}
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public FormalParameterListContext formalParameterList() {
			return getRuleContext(FormalParameterListContext.class,0);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public LambdaLVTIListContext lambdaLVTIList() {
			return getRuleContext(LambdaLVTIListContext.class,0);
		}
		public LambdaParametersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lambdaParameters; }
	}

	public final LambdaParametersContext lambdaParameters() throws RecognitionException {
		LambdaParametersContext _localctx = new LambdaParametersContext(_ctx, getState());
		enterRule(_localctx, 204, RULE_lambdaParameters);
		int _la;
		try {
			setState(1514);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,179,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1492);
				identifier();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1493);
				match(LPAREN);
				setState(1495);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FINAL - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (SHORT - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || _la==AT || _la==IDENTIFIER) {
					{
					setState(1494);
					formalParameterList();
					}
				}

				setState(1497);
				match(RPAREN);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1498);
				match(LPAREN);
				setState(1499);
				identifier();
				setState(1504);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==COMMA) {
					{
					{
					setState(1500);
					match(COMMA);
					setState(1501);
					identifier();
					}
					}
					setState(1506);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(1507);
				match(RPAREN);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1509);
				match(LPAREN);
				setState(1511);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 18)) & ~0x3f) == 0 && ((1L << (_la - 18)) & ((1L << (FINAL - 18)) | (1L << (MODULE - 18)) | (1L << (OPEN - 18)) | (1L << (REQUIRES - 18)) | (1L << (EXPORTS - 18)) | (1L << (OPENS - 18)) | (1L << (TO - 18)) | (1L << (USES - 18)) | (1L << (PROVIDES - 18)) | (1L << (WITH - 18)) | (1L << (TRANSITIVE - 18)) | (1L << (VAR - 18)) | (1L << (YIELD - 18)) | (1L << (RECORD - 18)) | (1L << (SEALED - 18)) | (1L << (PERMITS - 18)))) != 0) || _la==AT || _la==IDENTIFIER) {
					{
					setState(1510);
					lambdaLVTIList();
					}
				}

				setState(1513);
				match(RPAREN);
				}
				break;
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

	public static class LambdaBodyContext extends ParserRuleContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public LambdaBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lambdaBody; }
	}

	public final LambdaBodyContext lambdaBody() throws RecognitionException {
		LambdaBodyContext _localctx = new LambdaBodyContext(_ctx, getState());
		enterRule(_localctx, 206, RULE_lambdaBody);
		try {
			setState(1518);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case DOUBLE:
			case FLOAT:
			case INT:
			case LONG:
			case NEW:
			case SHORT:
			case SUPER:
			case SWITCH:
			case THIS:
			case VOID:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case DECIMAL_LITERAL:
			case HEX_LITERAL:
			case OCT_LITERAL:
			case BINARY_LITERAL:
			case FLOAT_LITERAL:
			case HEX_FLOAT_LITERAL:
			case BOOL_LITERAL:
			case CHAR_LITERAL:
			case STRING_LITERAL:
			case TEXT_BLOCK:
			case NULL_LITERAL:
			case LPAREN:
			case LT:
			case BANG:
			case TILDE:
			case INC:
			case DEC:
			case ADD:
			case SUB:
			case AT:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1516);
				expression(0);
				}
				break;
			case LBRACE:
				enterOuterAlt(_localctx, 2);
				{
				setState(1517);
				block();
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

	public static class PrimaryContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public TerminalNode THIS() { return getToken(JavaParser.THIS, 0); }
		public TerminalNode SUPER() { return getToken(JavaParser.SUPER, 0); }
		public LiteralContext literal() {
			return getRuleContext(LiteralContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TypeTypeOrVoidContext typeTypeOrVoid() {
			return getRuleContext(TypeTypeOrVoidContext.class,0);
		}
		public TerminalNode DOT() { return getToken(JavaParser.DOT, 0); }
		public TerminalNode CLASS() { return getToken(JavaParser.CLASS, 0); }
		public NonWildcardTypeArgumentsContext nonWildcardTypeArguments() {
			return getRuleContext(NonWildcardTypeArgumentsContext.class,0);
		}
		public ExplicitGenericInvocationSuffixContext explicitGenericInvocationSuffix() {
			return getRuleContext(ExplicitGenericInvocationSuffixContext.class,0);
		}
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public PrimaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primary; }
	}

	public final PrimaryContext primary() throws RecognitionException {
		PrimaryContext _localctx = new PrimaryContext(_ctx, getState());
		enterRule(_localctx, 208, RULE_primary);
		try {
			setState(1538);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,182,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1520);
				match(LPAREN);
				setState(1521);
				expression(0);
				setState(1522);
				match(RPAREN);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1524);
				match(THIS);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1525);
				match(SUPER);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1526);
				literal();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1527);
				identifier();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(1528);
				typeTypeOrVoid();
				setState(1529);
				match(DOT);
				setState(1530);
				match(CLASS);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(1532);
				nonWildcardTypeArguments();
				setState(1536);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case SUPER:
				case MODULE:
				case OPEN:
				case REQUIRES:
				case EXPORTS:
				case OPENS:
				case TO:
				case USES:
				case PROVIDES:
				case WITH:
				case TRANSITIVE:
				case VAR:
				case YIELD:
				case RECORD:
				case SEALED:
				case PERMITS:
				case IDENTIFIER:
					{
					setState(1533);
					explicitGenericInvocationSuffix();
					}
					break;
				case THIS:
					{
					setState(1534);
					match(THIS);
					setState(1535);
					arguments();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				break;
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

	public static class SwitchExpressionContext extends ParserRuleContext {
		public TerminalNode SWITCH() { return getToken(JavaParser.SWITCH, 0); }
		public ParExpressionContext parExpression() {
			return getRuleContext(ParExpressionContext.class,0);
		}
		public TerminalNode LBRACE() { return getToken(JavaParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(JavaParser.RBRACE, 0); }
		public List<SwitchLabeledRuleContext> switchLabeledRule() {
			return getRuleContexts(SwitchLabeledRuleContext.class);
		}
		public SwitchLabeledRuleContext switchLabeledRule(int i) {
			return getRuleContext(SwitchLabeledRuleContext.class,i);
		}
		public SwitchExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_switchExpression; }
	}

	public final SwitchExpressionContext switchExpression() throws RecognitionException {
		SwitchExpressionContext _localctx = new SwitchExpressionContext(_ctx, getState());
		enterRule(_localctx, 210, RULE_switchExpression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1540);
			match(SWITCH);
			setState(1541);
			parExpression();
			setState(1542);
			match(LBRACE);
			setState(1546);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==CASE || _la==DEFAULT) {
				{
				{
				setState(1543);
				switchLabeledRule();
				}
				}
				setState(1548);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(1549);
			match(RBRACE);
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

	public static class SwitchLabeledRuleContext extends ParserRuleContext {
		public TerminalNode CASE() { return getToken(JavaParser.CASE, 0); }
		public SwitchRuleOutcomeContext switchRuleOutcome() {
			return getRuleContext(SwitchRuleOutcomeContext.class,0);
		}
		public TerminalNode ARROW() { return getToken(JavaParser.ARROW, 0); }
		public TerminalNode COLON() { return getToken(JavaParser.COLON, 0); }
		public ExpressionListContext expressionList() {
			return getRuleContext(ExpressionListContext.class,0);
		}
		public TerminalNode NULL_LITERAL() { return getToken(JavaParser.NULL_LITERAL, 0); }
		public GuardedPatternContext guardedPattern() {
			return getRuleContext(GuardedPatternContext.class,0);
		}
		public TerminalNode DEFAULT() { return getToken(JavaParser.DEFAULT, 0); }
		public SwitchLabeledRuleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_switchLabeledRule; }
	}

	public final SwitchLabeledRuleContext switchLabeledRule() throws RecognitionException {
		SwitchLabeledRuleContext _localctx = new SwitchLabeledRuleContext(_ctx, getState());
		enterRule(_localctx, 212, RULE_switchLabeledRule);
		int _la;
		try {
			setState(1562);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case CASE:
				enterOuterAlt(_localctx, 1);
				{
				setState(1551);
				match(CASE);
				setState(1555);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,184,_ctx) ) {
				case 1:
					{
					setState(1552);
					expressionList();
					}
					break;
				case 2:
					{
					setState(1553);
					match(NULL_LITERAL);
					}
					break;
				case 3:
					{
					setState(1554);
					guardedPattern(0);
					}
					break;
				}
				setState(1557);
				_la = _input.LA(1);
				if ( !(_la==COLON || _la==ARROW) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(1558);
				switchRuleOutcome();
				}
				break;
			case DEFAULT:
				enterOuterAlt(_localctx, 2);
				{
				setState(1559);
				match(DEFAULT);
				setState(1560);
				_la = _input.LA(1);
				if ( !(_la==COLON || _la==ARROW) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(1561);
				switchRuleOutcome();
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

	public static class GuardedPatternContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public GuardedPatternContext guardedPattern() {
			return getRuleContext(GuardedPatternContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public TypeTypeContext typeType() {
			return getRuleContext(TypeTypeContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public List<VariableModifierContext> variableModifier() {
			return getRuleContexts(VariableModifierContext.class);
		}
		public VariableModifierContext variableModifier(int i) {
			return getRuleContext(VariableModifierContext.class,i);
		}
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public List<TerminalNode> AND() { return getTokens(JavaParser.AND); }
		public TerminalNode AND(int i) {
			return getToken(JavaParser.AND, i);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public GuardedPatternContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_guardedPattern; }
	}

	public final GuardedPatternContext guardedPattern() throws RecognitionException {
		return guardedPattern(0);
	}

	private GuardedPatternContext guardedPattern(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		GuardedPatternContext _localctx = new GuardedPatternContext(_ctx, _parentState);
		GuardedPatternContext _prevctx = _localctx;
		int _startState = 214;
		enterRecursionRule(_localctx, 214, RULE_guardedPattern, _p);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1590);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LPAREN:
				{
				setState(1565);
				match(LPAREN);
				setState(1566);
				guardedPattern(0);
				setState(1567);
				match(RPAREN);
				}
				break;
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case DOUBLE:
			case FINAL:
			case FLOAT:
			case INT:
			case LONG:
			case SHORT:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case AT:
			case IDENTIFIER:
				{
				setState(1572);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,186,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1569);
						variableModifier();
						}
						} 
					}
					setState(1574);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,186,_ctx);
				}
				setState(1575);
				typeType();
				setState(1579);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,187,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1576);
						annotation();
						}
						} 
					}
					setState(1581);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,187,_ctx);
				}
				setState(1582);
				identifier();
				setState(1587);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,188,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1583);
						match(AND);
						setState(1584);
						expression(0);
						}
						} 
					}
					setState(1589);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,188,_ctx);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			_ctx.stop = _input.LT(-1);
			setState(1597);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,190,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new GuardedPatternContext(_parentctx, _parentState);
					pushNewRecursionContext(_localctx, _startState, RULE_guardedPattern);
					setState(1592);
					if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
					setState(1593);
					match(AND);
					setState(1594);
					expression(0);
					}
					} 
				}
				setState(1599);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,190,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class SwitchRuleOutcomeContext extends ParserRuleContext {
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public List<BlockStatementContext> blockStatement() {
			return getRuleContexts(BlockStatementContext.class);
		}
		public BlockStatementContext blockStatement(int i) {
			return getRuleContext(BlockStatementContext.class,i);
		}
		public SwitchRuleOutcomeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_switchRuleOutcome; }
	}

	public final SwitchRuleOutcomeContext switchRuleOutcome() throws RecognitionException {
		SwitchRuleOutcomeContext _localctx = new SwitchRuleOutcomeContext(_ctx, getState());
		enterRule(_localctx, 216, RULE_switchRuleOutcome);
		int _la;
		try {
			setState(1607);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,192,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1600);
				block();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1604);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << ABSTRACT) | (1L << ASSERT) | (1L << BOOLEAN) | (1L << BREAK) | (1L << BYTE) | (1L << CHAR) | (1L << CLASS) | (1L << CONTINUE) | (1L << DO) | (1L << DOUBLE) | (1L << FINAL) | (1L << FLOAT) | (1L << FOR) | (1L << IF) | (1L << INT) | (1L << INTERFACE) | (1L << LONG) | (1L << NEW) | (1L << PRIVATE) | (1L << PROTECTED) | (1L << PUBLIC) | (1L << RETURN) | (1L << SHORT) | (1L << STATIC) | (1L << STRICTFP) | (1L << SUPER) | (1L << SWITCH) | (1L << SYNCHRONIZED) | (1L << THIS) | (1L << THROW) | (1L << TRY) | (1L << VOID) | (1L << WHILE) | (1L << MODULE) | (1L << OPEN) | (1L << REQUIRES) | (1L << EXPORTS) | (1L << OPENS) | (1L << TO) | (1L << USES) | (1L << PROVIDES) | (1L << WITH) | (1L << TRANSITIVE) | (1L << VAR) | (1L << YIELD) | (1L << RECORD))) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & ((1L << (SEALED - 64)) | (1L << (PERMITS - 64)) | (1L << (NON_SEALED - 64)) | (1L << (DECIMAL_LITERAL - 64)) | (1L << (HEX_LITERAL - 64)) | (1L << (OCT_LITERAL - 64)) | (1L << (BINARY_LITERAL - 64)) | (1L << (FLOAT_LITERAL - 64)) | (1L << (HEX_FLOAT_LITERAL - 64)) | (1L << (BOOL_LITERAL - 64)) | (1L << (CHAR_LITERAL - 64)) | (1L << (STRING_LITERAL - 64)) | (1L << (TEXT_BLOCK - 64)) | (1L << (NULL_LITERAL - 64)) | (1L << (LPAREN - 64)) | (1L << (LBRACE - 64)) | (1L << (SEMI - 64)) | (1L << (LT - 64)) | (1L << (BANG - 64)) | (1L << (TILDE - 64)) | (1L << (INC - 64)) | (1L << (DEC - 64)) | (1L << (ADD - 64)) | (1L << (SUB - 64)) | (1L << (AT - 64)))) != 0) || _la==IDENTIFIER) {
					{
					{
					setState(1601);
					blockStatement();
					}
					}
					setState(1606);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
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

	public static class ClassTypeContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public ClassOrInterfaceTypeContext classOrInterfaceType() {
			return getRuleContext(ClassOrInterfaceTypeContext.class,0);
		}
		public TerminalNode DOT() { return getToken(JavaParser.DOT, 0); }
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public TypeArgumentsContext typeArguments() {
			return getRuleContext(TypeArgumentsContext.class,0);
		}
		public ClassTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classType; }
	}

	public final ClassTypeContext classType() throws RecognitionException {
		ClassTypeContext _localctx = new ClassTypeContext(_ctx, getState());
		enterRule(_localctx, 218, RULE_classType);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1612);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,193,_ctx) ) {
			case 1:
				{
				setState(1609);
				classOrInterfaceType();
				setState(1610);
				match(DOT);
				}
				break;
			}
			setState(1617);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,194,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1614);
					annotation();
					}
					} 
				}
				setState(1619);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,194,_ctx);
			}
			setState(1620);
			identifier();
			setState(1622);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LT) {
				{
				setState(1621);
				typeArguments();
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

	public static class CreatorContext extends ParserRuleContext {
		public NonWildcardTypeArgumentsContext nonWildcardTypeArguments() {
			return getRuleContext(NonWildcardTypeArgumentsContext.class,0);
		}
		public CreatedNameContext createdName() {
			return getRuleContext(CreatedNameContext.class,0);
		}
		public ClassCreatorRestContext classCreatorRest() {
			return getRuleContext(ClassCreatorRestContext.class,0);
		}
		public ArrayCreatorRestContext arrayCreatorRest() {
			return getRuleContext(ArrayCreatorRestContext.class,0);
		}
		public CreatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_creator; }
	}

	public final CreatorContext creator() throws RecognitionException {
		CreatorContext _localctx = new CreatorContext(_ctx, getState());
		enterRule(_localctx, 220, RULE_creator);
		try {
			setState(1633);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LT:
				enterOuterAlt(_localctx, 1);
				{
				setState(1624);
				nonWildcardTypeArguments();
				setState(1625);
				createdName();
				setState(1626);
				classCreatorRest();
				}
				break;
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case DOUBLE:
			case FLOAT:
			case INT:
			case LONG:
			case SHORT:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				setState(1628);
				createdName();
				setState(1631);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case LBRACK:
					{
					setState(1629);
					arrayCreatorRest();
					}
					break;
				case LPAREN:
					{
					setState(1630);
					classCreatorRest();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
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

	public static class CreatedNameContext extends ParserRuleContext {
		public List<IdentifierContext> identifier() {
			return getRuleContexts(IdentifierContext.class);
		}
		public IdentifierContext identifier(int i) {
			return getRuleContext(IdentifierContext.class,i);
		}
		public List<TypeArgumentsOrDiamondContext> typeArgumentsOrDiamond() {
			return getRuleContexts(TypeArgumentsOrDiamondContext.class);
		}
		public TypeArgumentsOrDiamondContext typeArgumentsOrDiamond(int i) {
			return getRuleContext(TypeArgumentsOrDiamondContext.class,i);
		}
		public List<TerminalNode> DOT() { return getTokens(JavaParser.DOT); }
		public TerminalNode DOT(int i) {
			return getToken(JavaParser.DOT, i);
		}
		public PrimitiveTypeContext primitiveType() {
			return getRuleContext(PrimitiveTypeContext.class,0);
		}
		public CreatedNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_createdName; }
	}

	public final CreatedNameContext createdName() throws RecognitionException {
		CreatedNameContext _localctx = new CreatedNameContext(_ctx, getState());
		enterRule(_localctx, 222, RULE_createdName);
		int _la;
		try {
			setState(1650);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1635);
				identifier();
				setState(1637);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==LT) {
					{
					setState(1636);
					typeArgumentsOrDiamond();
					}
				}

				setState(1646);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==DOT) {
					{
					{
					setState(1639);
					match(DOT);
					setState(1640);
					identifier();
					setState(1642);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if (_la==LT) {
						{
						setState(1641);
						typeArgumentsOrDiamond();
						}
					}

					}
					}
					setState(1648);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case DOUBLE:
			case FLOAT:
			case INT:
			case LONG:
			case SHORT:
				enterOuterAlt(_localctx, 2);
				{
				setState(1649);
				primitiveType();
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

	public static class InnerCreatorContext extends ParserRuleContext {
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public ClassCreatorRestContext classCreatorRest() {
			return getRuleContext(ClassCreatorRestContext.class,0);
		}
		public NonWildcardTypeArgumentsOrDiamondContext nonWildcardTypeArgumentsOrDiamond() {
			return getRuleContext(NonWildcardTypeArgumentsOrDiamondContext.class,0);
		}
		public InnerCreatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_innerCreator; }
	}

	public final InnerCreatorContext innerCreator() throws RecognitionException {
		InnerCreatorContext _localctx = new InnerCreatorContext(_ctx, getState());
		enterRule(_localctx, 224, RULE_innerCreator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1652);
			identifier();
			setState(1654);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LT) {
				{
				setState(1653);
				nonWildcardTypeArgumentsOrDiamond();
				}
			}

			setState(1656);
			classCreatorRest();
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

	public static class ArrayCreatorRestContext extends ParserRuleContext {
		public List<TerminalNode> LBRACK() { return getTokens(JavaParser.LBRACK); }
		public TerminalNode LBRACK(int i) {
			return getToken(JavaParser.LBRACK, i);
		}
		public List<TerminalNode> RBRACK() { return getTokens(JavaParser.RBRACK); }
		public TerminalNode RBRACK(int i) {
			return getToken(JavaParser.RBRACK, i);
		}
		public ArrayInitializerContext arrayInitializer() {
			return getRuleContext(ArrayInitializerContext.class,0);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public ArrayCreatorRestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayCreatorRest; }
	}

	public final ArrayCreatorRestContext arrayCreatorRest() throws RecognitionException {
		ArrayCreatorRestContext _localctx = new ArrayCreatorRestContext(_ctx, getState());
		enterRule(_localctx, 226, RULE_arrayCreatorRest);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1658);
			match(LBRACK);
			setState(1686);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case RBRACK:
				{
				setState(1659);
				match(RBRACK);
				setState(1664);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==LBRACK) {
					{
					{
					setState(1660);
					match(LBRACK);
					setState(1661);
					match(RBRACK);
					}
					}
					setState(1666);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(1667);
				arrayInitializer();
				}
				break;
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case DOUBLE:
			case FLOAT:
			case INT:
			case LONG:
			case NEW:
			case SHORT:
			case SUPER:
			case SWITCH:
			case THIS:
			case VOID:
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case DECIMAL_LITERAL:
			case HEX_LITERAL:
			case OCT_LITERAL:
			case BINARY_LITERAL:
			case FLOAT_LITERAL:
			case HEX_FLOAT_LITERAL:
			case BOOL_LITERAL:
			case CHAR_LITERAL:
			case STRING_LITERAL:
			case TEXT_BLOCK:
			case NULL_LITERAL:
			case LPAREN:
			case LT:
			case BANG:
			case TILDE:
			case INC:
			case DEC:
			case ADD:
			case SUB:
			case AT:
			case IDENTIFIER:
				{
				setState(1668);
				expression(0);
				setState(1669);
				match(RBRACK);
				setState(1676);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,204,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1670);
						match(LBRACK);
						setState(1671);
						expression(0);
						setState(1672);
						match(RBRACK);
						}
						} 
					}
					setState(1678);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,204,_ctx);
				}
				setState(1683);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,205,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1679);
						match(LBRACK);
						setState(1680);
						match(RBRACK);
						}
						} 
					}
					setState(1685);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,205,_ctx);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
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

	public static class ClassCreatorRestContext extends ParserRuleContext {
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public ClassBodyContext classBody() {
			return getRuleContext(ClassBodyContext.class,0);
		}
		public ClassCreatorRestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classCreatorRest; }
	}

	public final ClassCreatorRestContext classCreatorRest() throws RecognitionException {
		ClassCreatorRestContext _localctx = new ClassCreatorRestContext(_ctx, getState());
		enterRule(_localctx, 228, RULE_classCreatorRest);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1688);
			arguments();
			setState(1690);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,207,_ctx) ) {
			case 1:
				{
				setState(1689);
				classBody();
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

	public static class ExplicitGenericInvocationContext extends ParserRuleContext {
		public NonWildcardTypeArgumentsContext nonWildcardTypeArguments() {
			return getRuleContext(NonWildcardTypeArgumentsContext.class,0);
		}
		public ExplicitGenericInvocationSuffixContext explicitGenericInvocationSuffix() {
			return getRuleContext(ExplicitGenericInvocationSuffixContext.class,0);
		}
		public ExplicitGenericInvocationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_explicitGenericInvocation; }
	}

	public final ExplicitGenericInvocationContext explicitGenericInvocation() throws RecognitionException {
		ExplicitGenericInvocationContext _localctx = new ExplicitGenericInvocationContext(_ctx, getState());
		enterRule(_localctx, 230, RULE_explicitGenericInvocation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1692);
			nonWildcardTypeArguments();
			setState(1693);
			explicitGenericInvocationSuffix();
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

	public static class TypeArgumentsOrDiamondContext extends ParserRuleContext {
		public TerminalNode LT() { return getToken(JavaParser.LT, 0); }
		public TerminalNode GT() { return getToken(JavaParser.GT, 0); }
		public TypeArgumentsContext typeArguments() {
			return getRuleContext(TypeArgumentsContext.class,0);
		}
		public TypeArgumentsOrDiamondContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeArgumentsOrDiamond; }
	}

	public final TypeArgumentsOrDiamondContext typeArgumentsOrDiamond() throws RecognitionException {
		TypeArgumentsOrDiamondContext _localctx = new TypeArgumentsOrDiamondContext(_ctx, getState());
		enterRule(_localctx, 232, RULE_typeArgumentsOrDiamond);
		try {
			setState(1698);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,208,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1695);
				match(LT);
				setState(1696);
				match(GT);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1697);
				typeArguments();
				}
				break;
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

	public static class NonWildcardTypeArgumentsOrDiamondContext extends ParserRuleContext {
		public TerminalNode LT() { return getToken(JavaParser.LT, 0); }
		public TerminalNode GT() { return getToken(JavaParser.GT, 0); }
		public NonWildcardTypeArgumentsContext nonWildcardTypeArguments() {
			return getRuleContext(NonWildcardTypeArgumentsContext.class,0);
		}
		public NonWildcardTypeArgumentsOrDiamondContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nonWildcardTypeArgumentsOrDiamond; }
	}

	public final NonWildcardTypeArgumentsOrDiamondContext nonWildcardTypeArgumentsOrDiamond() throws RecognitionException {
		NonWildcardTypeArgumentsOrDiamondContext _localctx = new NonWildcardTypeArgumentsOrDiamondContext(_ctx, getState());
		enterRule(_localctx, 234, RULE_nonWildcardTypeArgumentsOrDiamond);
		try {
			setState(1703);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,209,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1700);
				match(LT);
				setState(1701);
				match(GT);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1702);
				nonWildcardTypeArguments();
				}
				break;
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

	public static class NonWildcardTypeArgumentsContext extends ParserRuleContext {
		public TerminalNode LT() { return getToken(JavaParser.LT, 0); }
		public TypeListContext typeList() {
			return getRuleContext(TypeListContext.class,0);
		}
		public TerminalNode GT() { return getToken(JavaParser.GT, 0); }
		public NonWildcardTypeArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nonWildcardTypeArguments; }
	}

	public final NonWildcardTypeArgumentsContext nonWildcardTypeArguments() throws RecognitionException {
		NonWildcardTypeArgumentsContext _localctx = new NonWildcardTypeArgumentsContext(_ctx, getState());
		enterRule(_localctx, 236, RULE_nonWildcardTypeArguments);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1705);
			match(LT);
			setState(1706);
			typeList();
			setState(1707);
			match(GT);
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

	public static class TypeListContext extends ParserRuleContext {
		public List<TypeTypeContext> typeType() {
			return getRuleContexts(TypeTypeContext.class);
		}
		public TypeTypeContext typeType(int i) {
			return getRuleContext(TypeTypeContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public TypeListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeList; }
	}

	public final TypeListContext typeList() throws RecognitionException {
		TypeListContext _localctx = new TypeListContext(_ctx, getState());
		enterRule(_localctx, 238, RULE_typeList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1709);
			typeType();
			setState(1714);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(1710);
				match(COMMA);
				setState(1711);
				typeType();
				}
				}
				setState(1716);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class TypeTypeContext extends ParserRuleContext {
		public ClassOrInterfaceTypeContext classOrInterfaceType() {
			return getRuleContext(ClassOrInterfaceTypeContext.class,0);
		}
		public PrimitiveTypeContext primitiveType() {
			return getRuleContext(PrimitiveTypeContext.class,0);
		}
		public List<AnnotationContext> annotation() {
			return getRuleContexts(AnnotationContext.class);
		}
		public AnnotationContext annotation(int i) {
			return getRuleContext(AnnotationContext.class,i);
		}
		public List<TerminalNode> LBRACK() { return getTokens(JavaParser.LBRACK); }
		public TerminalNode LBRACK(int i) {
			return getToken(JavaParser.LBRACK, i);
		}
		public List<TerminalNode> RBRACK() { return getTokens(JavaParser.RBRACK); }
		public TerminalNode RBRACK(int i) {
			return getToken(JavaParser.RBRACK, i);
		}
		public TypeTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeType; }
	}

	public final TypeTypeContext typeType() throws RecognitionException {
		TypeTypeContext _localctx = new TypeTypeContext(_ctx, getState());
		enterRule(_localctx, 240, RULE_typeType);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(1720);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,211,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1717);
					annotation();
					}
					} 
				}
				setState(1722);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,211,_ctx);
			}
			setState(1725);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case IDENTIFIER:
				{
				setState(1723);
				classOrInterfaceType();
				}
				break;
			case BOOLEAN:
			case BYTE:
			case CHAR:
			case DOUBLE:
			case FLOAT:
			case INT:
			case LONG:
			case SHORT:
				{
				setState(1724);
				primitiveType();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(1737);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,214,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(1730);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (((((_la - 51)) & ~0x3f) == 0 && ((1L << (_la - 51)) & ((1L << (MODULE - 51)) | (1L << (OPEN - 51)) | (1L << (REQUIRES - 51)) | (1L << (EXPORTS - 51)) | (1L << (OPENS - 51)) | (1L << (TO - 51)) | (1L << (USES - 51)) | (1L << (PROVIDES - 51)) | (1L << (WITH - 51)) | (1L << (TRANSITIVE - 51)) | (1L << (VAR - 51)) | (1L << (YIELD - 51)) | (1L << (RECORD - 51)) | (1L << (SEALED - 51)) | (1L << (PERMITS - 51)))) != 0) || _la==AT || _la==IDENTIFIER) {
						{
						{
						setState(1727);
						annotation();
						}
						}
						setState(1732);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					setState(1733);
					match(LBRACK);
					setState(1734);
					match(RBRACK);
					}
					} 
				}
				setState(1739);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,214,_ctx);
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

	public static class PrimitiveTypeContext extends ParserRuleContext {
		public TerminalNode BOOLEAN() { return getToken(JavaParser.BOOLEAN, 0); }
		public TerminalNode CHAR() { return getToken(JavaParser.CHAR, 0); }
		public TerminalNode BYTE() { return getToken(JavaParser.BYTE, 0); }
		public TerminalNode SHORT() { return getToken(JavaParser.SHORT, 0); }
		public TerminalNode INT() { return getToken(JavaParser.INT, 0); }
		public TerminalNode LONG() { return getToken(JavaParser.LONG, 0); }
		public TerminalNode FLOAT() { return getToken(JavaParser.FLOAT, 0); }
		public TerminalNode DOUBLE() { return getToken(JavaParser.DOUBLE, 0); }
		public PrimitiveTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primitiveType; }
	}

	public final PrimitiveTypeContext primitiveType() throws RecognitionException {
		PrimitiveTypeContext _localctx = new PrimitiveTypeContext(_ctx, getState());
		enterRule(_localctx, 242, RULE_primitiveType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1740);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << BOOLEAN) | (1L << BYTE) | (1L << CHAR) | (1L << DOUBLE) | (1L << FLOAT) | (1L << INT) | (1L << LONG) | (1L << SHORT))) != 0)) ) {
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

	public static class TypeArgumentsContext extends ParserRuleContext {
		public TerminalNode LT() { return getToken(JavaParser.LT, 0); }
		public List<TypeArgumentContext> typeArgument() {
			return getRuleContexts(TypeArgumentContext.class);
		}
		public TypeArgumentContext typeArgument(int i) {
			return getRuleContext(TypeArgumentContext.class,i);
		}
		public TerminalNode GT() { return getToken(JavaParser.GT, 0); }
		public List<TerminalNode> COMMA() { return getTokens(JavaParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(JavaParser.COMMA, i);
		}
		public TypeArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeArguments; }
	}

	public final TypeArgumentsContext typeArguments() throws RecognitionException {
		TypeArgumentsContext _localctx = new TypeArgumentsContext(_ctx, getState());
		enterRule(_localctx, 244, RULE_typeArguments);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1742);
			match(LT);
			setState(1743);
			typeArgument();
			setState(1748);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(1744);
				match(COMMA);
				setState(1745);
				typeArgument();
				}
				}
				setState(1750);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(1751);
			match(GT);
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

	public static class SuperSuffixContext extends ParserRuleContext {
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public TerminalNode DOT() { return getToken(JavaParser.DOT, 0); }
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public TypeArgumentsContext typeArguments() {
			return getRuleContext(TypeArgumentsContext.class,0);
		}
		public SuperSuffixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_superSuffix; }
	}

	public final SuperSuffixContext superSuffix() throws RecognitionException {
		SuperSuffixContext _localctx = new SuperSuffixContext(_ctx, getState());
		enterRule(_localctx, 246, RULE_superSuffix);
		int _la;
		try {
			setState(1762);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LPAREN:
				enterOuterAlt(_localctx, 1);
				{
				setState(1753);
				arguments();
				}
				break;
			case DOT:
				enterOuterAlt(_localctx, 2);
				{
				setState(1754);
				match(DOT);
				setState(1756);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==LT) {
					{
					setState(1755);
					typeArguments();
					}
				}

				setState(1758);
				identifier();
				setState(1760);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,217,_ctx) ) {
				case 1:
					{
					setState(1759);
					arguments();
					}
					break;
				}
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

	public static class ExplicitGenericInvocationSuffixContext extends ParserRuleContext {
		public TerminalNode SUPER() { return getToken(JavaParser.SUPER, 0); }
		public SuperSuffixContext superSuffix() {
			return getRuleContext(SuperSuffixContext.class,0);
		}
		public IdentifierContext identifier() {
			return getRuleContext(IdentifierContext.class,0);
		}
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public ExplicitGenericInvocationSuffixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_explicitGenericInvocationSuffix; }
	}

	public final ExplicitGenericInvocationSuffixContext explicitGenericInvocationSuffix() throws RecognitionException {
		ExplicitGenericInvocationSuffixContext _localctx = new ExplicitGenericInvocationSuffixContext(_ctx, getState());
		enterRule(_localctx, 248, RULE_explicitGenericInvocationSuffix);
		try {
			setState(1769);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SUPER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1764);
				match(SUPER);
				setState(1765);
				superSuffix();
				}
				break;
			case MODULE:
			case OPEN:
			case REQUIRES:
			case EXPORTS:
			case OPENS:
			case TO:
			case USES:
			case PROVIDES:
			case WITH:
			case TRANSITIVE:
			case VAR:
			case YIELD:
			case RECORD:
			case SEALED:
			case PERMITS:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				setState(1766);
				identifier();
				setState(1767);
				arguments();
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

	public static class ArgumentsContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(JavaParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(JavaParser.RPAREN, 0); }
		public ExpressionListContext expressionList() {
			return getRuleContext(ExpressionListContext.class,0);
		}
		public ArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arguments; }
	}

	public final ArgumentsContext arguments() throws RecognitionException {
		ArgumentsContext _localctx = new ArgumentsContext(_ctx, getState());
		enterRule(_localctx, 250, RULE_arguments);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1771);
			match(LPAREN);
			setState(1773);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 3)) & ~0x3f) == 0 && ((1L << (_la - 3)) & ((1L << (BOOLEAN - 3)) | (1L << (BYTE - 3)) | (1L << (CHAR - 3)) | (1L << (DOUBLE - 3)) | (1L << (FLOAT - 3)) | (1L << (INT - 3)) | (1L << (LONG - 3)) | (1L << (NEW - 3)) | (1L << (SHORT - 3)) | (1L << (SUPER - 3)) | (1L << (SWITCH - 3)) | (1L << (THIS - 3)) | (1L << (VOID - 3)) | (1L << (MODULE - 3)) | (1L << (OPEN - 3)) | (1L << (REQUIRES - 3)) | (1L << (EXPORTS - 3)) | (1L << (OPENS - 3)) | (1L << (TO - 3)) | (1L << (USES - 3)) | (1L << (PROVIDES - 3)) | (1L << (WITH - 3)) | (1L << (TRANSITIVE - 3)) | (1L << (VAR - 3)) | (1L << (YIELD - 3)) | (1L << (RECORD - 3)) | (1L << (SEALED - 3)) | (1L << (PERMITS - 3)))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (DECIMAL_LITERAL - 67)) | (1L << (HEX_LITERAL - 67)) | (1L << (OCT_LITERAL - 67)) | (1L << (BINARY_LITERAL - 67)) | (1L << (FLOAT_LITERAL - 67)) | (1L << (HEX_FLOAT_LITERAL - 67)) | (1L << (BOOL_LITERAL - 67)) | (1L << (CHAR_LITERAL - 67)) | (1L << (STRING_LITERAL - 67)) | (1L << (TEXT_BLOCK - 67)) | (1L << (NULL_LITERAL - 67)) | (1L << (LPAREN - 67)) | (1L << (LT - 67)) | (1L << (BANG - 67)) | (1L << (TILDE - 67)) | (1L << (INC - 67)) | (1L << (DEC - 67)) | (1L << (ADD - 67)) | (1L << (SUB - 67)) | (1L << (AT - 67)) | (1L << (IDENTIFIER - 67)))) != 0)) {
				{
				setState(1772);
				expressionList();
				}
			}

			setState(1775);
			match(RPAREN);
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

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 99:
			return expression_sempred((ExpressionContext)_localctx, predIndex);
		case 107:
			return guardedPattern_sempred((GuardedPatternContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expression_sempred(ExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 18);
		case 1:
			return precpred(_ctx, 17);
		case 2:
			return precpred(_ctx, 16);
		case 3:
			return precpred(_ctx, 15);
		case 4:
			return precpred(_ctx, 13);
		case 5:
			return precpred(_ctx, 12);
		case 6:
			return precpred(_ctx, 11);
		case 7:
			return precpred(_ctx, 10);
		case 8:
			return precpred(_ctx, 9);
		case 9:
			return precpred(_ctx, 8);
		case 10:
			return precpred(_ctx, 7);
		case 11:
			return precpred(_ctx, 6);
		case 12:
			return precpred(_ctx, 26);
		case 13:
			return precpred(_ctx, 25);
		case 14:
			return precpred(_ctx, 21);
		case 15:
			return precpred(_ctx, 14);
		case 16:
			return precpred(_ctx, 3);
		}
		return true;
	}
	private boolean guardedPattern_sempred(GuardedPatternContext _localctx, int predIndex) {
		switch (predIndex) {
		case 17:
			return precpred(_ctx, 1);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\u0083\u06f4\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t="+
		"\4>\t>\4?\t?\4@\t@\4A\tA\4B\tB\4C\tC\4D\tD\4E\tE\4F\tF\4G\tG\4H\tH\4I"+
		"\tI\4J\tJ\4K\tK\4L\tL\4M\tM\4N\tN\4O\tO\4P\tP\4Q\tQ\4R\tR\4S\tS\4T\tT"+
		"\4U\tU\4V\tV\4W\tW\4X\tX\4Y\tY\4Z\tZ\4[\t[\4\\\t\\\4]\t]\4^\t^\4_\t_\4"+
		"`\t`\4a\ta\4b\tb\4c\tc\4d\td\4e\te\4f\tf\4g\tg\4h\th\4i\ti\4j\tj\4k\t"+
		"k\4l\tl\4m\tm\4n\tn\4o\to\4p\tp\4q\tq\4r\tr\4s\ts\4t\tt\4u\tu\4v\tv\4"+
		"w\tw\4x\tx\4y\ty\4z\tz\4{\t{\4|\t|\4}\t}\4~\t~\4\177\t\177\3\2\5\2\u0100"+
		"\n\2\3\2\7\2\u0103\n\2\f\2\16\2\u0106\13\2\3\2\7\2\u0109\n\2\f\2\16\2"+
		"\u010c\13\2\3\2\3\2\3\2\5\2\u0111\n\2\3\3\7\3\u0114\n\3\f\3\16\3\u0117"+
		"\13\3\3\3\3\3\3\3\3\3\3\4\3\4\5\4\u011f\n\4\3\4\3\4\3\4\5\4\u0124\n\4"+
		"\3\4\3\4\3\5\7\5\u0129\n\5\f\5\16\5\u012c\13\5\3\5\3\5\3\5\3\5\3\5\5\5"+
		"\u0133\n\5\3\5\5\5\u0136\n\5\3\6\3\6\3\6\3\6\3\6\5\6\u013d\n\6\3\7\3\7"+
		"\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\5\7\u0149\n\7\3\b\3\b\5\b\u014d\n\b\3"+
		"\t\3\t\3\t\5\t\u0152\n\t\3\t\3\t\5\t\u0156\n\t\3\t\3\t\5\t\u015a\n\t\3"+
		"\t\3\t\5\t\u015e\n\t\3\t\3\t\3\n\3\n\3\n\3\n\7\n\u0166\n\n\f\n\16\n\u0169"+
		"\13\n\3\n\3\n\3\13\7\13\u016e\n\13\f\13\16\13\u0171\13\13\3\13\3\13\3"+
		"\13\7\13\u0176\n\13\f\13\16\13\u0179\13\13\3\13\5\13\u017c\n\13\3\f\3"+
		"\f\3\f\7\f\u0181\n\f\f\f\16\f\u0184\13\f\3\r\3\r\3\r\3\r\5\r\u018a\n\r"+
		"\3\r\3\r\5\r\u018e\n\r\3\r\5\r\u0191\n\r\3\r\5\r\u0194\n\r\3\r\3\r\3\16"+
		"\3\16\3\16\7\16\u019b\n\16\f\16\16\16\u019e\13\16\3\17\7\17\u01a1\n\17"+
		"\f\17\16\17\u01a4\13\17\3\17\3\17\5\17\u01a8\n\17\3\17\5\17\u01ab\n\17"+
		"\3\20\3\20\7\20\u01af\n\20\f\20\16\20\u01b2\13\20\3\21\3\21\3\21\5\21"+
		"\u01b7\n\21\3\21\3\21\5\21\u01bb\n\21\3\21\3\21\5\21\u01bf\n\21\3\21\3"+
		"\21\3\22\3\22\7\22\u01c5\n\22\f\22\16\22\u01c8\13\22\3\22\3\22\3\23\3"+
		"\23\7\23\u01ce\n\23\f\23\16\23\u01d1\13\23\3\23\3\23\3\24\3\24\5\24\u01d7"+
		"\n\24\3\24\3\24\7\24\u01db\n\24\f\24\16\24\u01de\13\24\3\24\5\24\u01e1"+
		"\n\24\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\5\25\u01ed\n\25"+
		"\3\26\3\26\3\26\3\26\3\26\7\26\u01f4\n\26\f\26\16\26\u01f7\13\26\3\26"+
		"\3\26\5\26\u01fb\n\26\3\26\3\26\3\27\3\27\5\27\u0201\n\27\3\30\3\30\5"+
		"\30\u0205\n\30\3\31\3\31\3\31\3\32\3\32\3\32\3\33\3\33\3\33\3\33\5\33"+
		"\u0211\n\33\3\33\3\33\3\34\7\34\u0216\n\34\f\34\16\34\u0219\13\34\3\34"+
		"\3\34\3\34\3\35\3\35\3\35\3\35\3\36\7\36\u0223\n\36\f\36\16\36\u0226\13"+
		"\36\3\36\3\36\5\36\u022a\n\36\3\37\3\37\3\37\3\37\3\37\3\37\3\37\3\37"+
		"\5\37\u0234\n\37\3 \3 \3 \3 \7 \u023a\n \f \16 \u023d\13 \3 \3 \3!\3!"+
		"\3!\7!\u0244\n!\f!\16!\u0247\13!\3!\3!\3!\3\"\7\"\u024d\n\"\f\"\16\"\u0250"+
		"\13\"\3\"\3\"\3#\3#\3#\3#\3#\3#\5#\u025a\n#\3$\7$\u025d\n$\f$\16$\u0260"+
		"\13$\3$\3$\3$\3%\7%\u0266\n%\f%\16%\u0269\13%\3%\3%\3%\3%\3%\7%\u0270"+
		"\n%\f%\16%\u0273\13%\3%\3%\5%\u0277\n%\3%\3%\3&\3&\3&\7&\u027e\n&\f&\16"+
		"&\u0281\13&\3\'\3\'\3\'\5\'\u0286\n\'\3(\3(\3(\7(\u028b\n(\f(\16(\u028e"+
		"\13(\3)\3)\5)\u0292\n)\3*\3*\3*\3*\7*\u0298\n*\f*\16*\u029b\13*\3*\5*"+
		"\u029e\n*\5*\u02a0\n*\3*\3*\3+\3+\5+\u02a6\n+\3+\3+\7+\u02aa\n+\f+\16"+
		"+\u02ad\13+\3+\3+\5+\u02b1\n+\3,\3,\7,\u02b5\n,\f,\16,\u02b8\13,\3,\3"+
		",\3,\5,\u02bd\n,\5,\u02bf\n,\3-\3-\3-\7-\u02c4\n-\f-\16-\u02c7\13-\3."+
		"\3.\5.\u02cb\n.\3.\3.\3.\5.\u02d0\n.\3.\5.\u02d3\n.\5.\u02d5\n.\3.\3."+
		"\3/\3/\3/\3/\7/\u02dd\n/\f/\16/\u02e0\13/\3/\3/\3\60\3\60\3\60\7\60\u02e7"+
		"\n\60\f\60\16\60\u02ea\13\60\3\60\3\60\5\60\u02ee\n\60\3\60\5\60\u02f1"+
		"\n\60\3\61\7\61\u02f4\n\61\f\61\16\61\u02f7\13\61\3\61\3\61\3\61\3\62"+
		"\7\62\u02fd\n\62\f\62\16\62\u0300\13\62\3\62\3\62\7\62\u0304\n\62\f\62"+
		"\16\62\u0307\13\62\3\62\3\62\3\62\3\63\3\63\3\63\7\63\u030f\n\63\f\63"+
		"\16\63\u0312\13\63\3\64\7\64\u0315\n\64\f\64\16\64\u0318\13\64\3\64\3"+
		"\64\3\64\3\65\3\65\3\65\7\65\u0320\n\65\f\65\16\65\u0323\13\65\3\66\3"+
		"\66\3\66\3\66\3\66\3\66\3\66\5\66\u032c\n\66\3\67\3\67\38\38\39\39\39"+
		"\79\u0335\n9\f9\169\u0338\139\39\39\39\3:\3:\3:\5:\u0340\n:\3:\3:\3:\5"+
		":\u0345\n:\3:\5:\u0348\n:\3;\3;\3;\7;\u034d\n;\f;\16;\u0350\13;\3<\3<"+
		"\3<\3<\3=\3=\3=\5=\u0359\n=\3>\3>\3>\3>\7>\u035f\n>\f>\16>\u0362\13>\5"+
		">\u0364\n>\3>\5>\u0367\n>\3>\3>\3?\3?\3?\3?\3?\3@\3@\7@\u0372\n@\f@\16"+
		"@\u0375\13@\3@\3@\3A\7A\u037a\nA\fA\16A\u037d\13A\3A\3A\5A\u0381\nA\3"+
		"B\3B\3B\3B\3B\3B\5B\u0389\nB\3B\3B\5B\u038d\nB\3B\3B\5B\u0391\nB\3B\3"+
		"B\5B\u0395\nB\3B\3B\5B\u0399\nB\5B\u039b\nB\3C\3C\5C\u039f\nC\3D\3D\3"+
		"D\3D\5D\u03a5\nD\3E\3E\3F\3F\3F\3G\5G\u03ad\nG\3G\3G\3G\3G\3H\3H\7H\u03b5"+
		"\nH\fH\16H\u03b8\13H\3H\3H\3I\3I\7I\u03be\nI\fI\16I\u03c1\13I\3I\3I\3"+
		"I\3I\3I\3I\3I\5I\u03ca\nI\3I\3I\3I\3I\3I\3I\5I\u03d2\nI\3I\3I\3I\3I\3"+
		"I\3I\3I\3I\3I\3I\3I\3I\5I\u03e0\nI\3J\3J\3K\3K\3K\5K\u03e7\nK\3K\3K\3"+
		"K\5K\u03ec\nK\3K\3K\3L\3L\5L\u03f2\nL\3L\3L\3M\3M\3M\7M\u03f9\nM\fM\16"+
		"M\u03fc\13M\3N\3N\3N\3O\3O\3O\7O\u0404\nO\fO\16O\u0407\13O\3O\3O\3P\3"+
		"P\7P\u040d\nP\fP\16P\u0410\13P\3P\3P\3Q\3Q\3Q\3Q\3Q\5Q\u0419\nQ\3R\7R"+
		"\u041c\nR\fR\16R\u041f\13R\3R\3R\3R\3R\3R\3R\3R\3R\5R\u0429\nR\3S\3S\3"+
		"T\3T\3U\7U\u0430\nU\fU\16U\u0433\13U\3U\3U\3U\5U\u0438\nU\3V\3V\3V\3V"+
		"\3V\5V\u043f\nV\3V\3V\3V\3V\3V\3V\3V\5V\u0448\nV\3V\3V\3V\3V\3V\3V\3V"+
		"\3V\3V\3V\3V\3V\3V\3V\3V\3V\3V\3V\3V\6V\u045d\nV\rV\16V\u045e\3V\5V\u0462"+
		"\nV\3V\5V\u0465\nV\3V\3V\3V\3V\7V\u046b\nV\fV\16V\u046e\13V\3V\5V\u0471"+
		"\nV\3V\3V\3V\3V\7V\u0477\nV\fV\16V\u047a\13V\3V\7V\u047d\nV\fV\16V\u0480"+
		"\13V\3V\3V\3V\3V\3V\3V\3V\3V\5V\u048a\nV\3V\3V\3V\3V\3V\3V\3V\5V\u0493"+
		"\nV\3V\3V\3V\5V\u0498\nV\3V\3V\3V\3V\3V\3V\3V\3V\3V\3V\3V\5V\u04a5\nV"+
		"\3V\3V\3V\3V\5V\u04ab\nV\3W\3W\3W\7W\u04b0\nW\fW\16W\u04b3\13W\3W\3W\3"+
		"W\3W\3W\3X\3X\3X\7X\u04bd\nX\fX\16X\u04c0\13X\3Y\3Y\3Y\3Z\3Z\3Z\5Z\u04c8"+
		"\nZ\3Z\3Z\3[\3[\3[\7[\u04cf\n[\f[\16[\u04d2\13[\3\\\7\\\u04d5\n\\\f\\"+
		"\16\\\u04d8\13\\\3\\\3\\\3\\\3\\\3\\\5\\\u04df\n\\\3\\\3\\\3\\\3\\\5\\"+
		"\u04e5\n\\\3]\6]\u04e8\n]\r]\16]\u04e9\3]\6]\u04ed\n]\r]\16]\u04ee\3^"+
		"\3^\3^\3^\3^\3^\5^\u04f7\n^\3^\3^\3^\5^\u04fc\n^\3_\3_\5_\u0500\n_\3_"+
		"\3_\5_\u0504\n_\3_\3_\5_\u0508\n_\5_\u050a\n_\3`\3`\5`\u050e\n`\3a\7a"+
		"\u0511\na\fa\16a\u0514\13a\3a\3a\5a\u0518\na\3a\3a\3a\3a\3b\3b\3b\3b\3"+
		"c\3c\3c\7c\u0525\nc\fc\16c\u0528\13c\3d\3d\3d\5d\u052d\nd\3d\3d\3d\3d"+
		"\3d\5d\u0534\nd\3d\3d\3d\3d\5d\u053a\nd\3d\5d\u053d\nd\3e\3e\3e\3e\3e"+
		"\3e\3e\7e\u0546\ne\fe\16e\u0549\13e\3e\3e\3e\7e\u054e\ne\fe\16e\u0551"+
		"\13e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\5e\u055f\ne\3e\3e\5e\u0563\n"+
		"e\3e\3e\3e\5e\u0568\ne\3e\3e\5e\u056c\ne\3e\3e\3e\3e\3e\3e\3e\3e\3e\3"+
		"e\3e\3e\3e\3e\5e\u057c\ne\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3"+
		"e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3"+
		"e\5e\u05a4\ne\3e\3e\3e\3e\5e\u05aa\ne\3e\3e\3e\3e\3e\3e\3e\3e\3e\3e\3"+
		"e\5e\u05b7\ne\3e\3e\3e\5e\u05bc\ne\3e\7e\u05bf\ne\fe\16e\u05c2\13e\3f"+
		"\7f\u05c5\nf\ff\16f\u05c8\13f\3f\3f\7f\u05cc\nf\ff\16f\u05cf\13f\3f\3"+
		"f\3g\3g\3g\3g\3h\3h\3h\5h\u05da\nh\3h\3h\3h\3h\3h\7h\u05e1\nh\fh\16h\u05e4"+
		"\13h\3h\3h\3h\3h\5h\u05ea\nh\3h\5h\u05ed\nh\3i\3i\5i\u05f1\ni\3j\3j\3"+
		"j\3j\3j\3j\3j\3j\3j\3j\3j\3j\3j\3j\3j\3j\5j\u0603\nj\5j\u0605\nj\3k\3"+
		"k\3k\3k\7k\u060b\nk\fk\16k\u060e\13k\3k\3k\3l\3l\3l\3l\5l\u0616\nl\3l"+
		"\3l\3l\3l\3l\5l\u061d\nl\3m\3m\3m\3m\3m\3m\7m\u0625\nm\fm\16m\u0628\13"+
		"m\3m\3m\7m\u062c\nm\fm\16m\u062f\13m\3m\3m\3m\7m\u0634\nm\fm\16m\u0637"+
		"\13m\5m\u0639\nm\3m\3m\3m\7m\u063e\nm\fm\16m\u0641\13m\3n\3n\7n\u0645"+
		"\nn\fn\16n\u0648\13n\5n\u064a\nn\3o\3o\3o\5o\u064f\no\3o\7o\u0652\no\f"+
		"o\16o\u0655\13o\3o\3o\5o\u0659\no\3p\3p\3p\3p\3p\3p\3p\5p\u0662\np\5p"+
		"\u0664\np\3q\3q\5q\u0668\nq\3q\3q\3q\5q\u066d\nq\7q\u066f\nq\fq\16q\u0672"+
		"\13q\3q\5q\u0675\nq\3r\3r\5r\u0679\nr\3r\3r\3s\3s\3s\3s\7s\u0681\ns\f"+
		"s\16s\u0684\13s\3s\3s\3s\3s\3s\3s\3s\7s\u068d\ns\fs\16s\u0690\13s\3s\3"+
		"s\7s\u0694\ns\fs\16s\u0697\13s\5s\u0699\ns\3t\3t\5t\u069d\nt\3u\3u\3u"+
		"\3v\3v\3v\5v\u06a5\nv\3w\3w\3w\5w\u06aa\nw\3x\3x\3x\3x\3y\3y\3y\7y\u06b3"+
		"\ny\fy\16y\u06b6\13y\3z\7z\u06b9\nz\fz\16z\u06bc\13z\3z\3z\5z\u06c0\n"+
		"z\3z\7z\u06c3\nz\fz\16z\u06c6\13z\3z\3z\7z\u06ca\nz\fz\16z\u06cd\13z\3"+
		"{\3{\3|\3|\3|\3|\7|\u06d5\n|\f|\16|\u06d8\13|\3|\3|\3}\3}\3}\5}\u06df"+
		"\n}\3}\3}\5}\u06e3\n}\5}\u06e5\n}\3~\3~\3~\3~\3~\5~\u06ec\n~\3\177\3\177"+
		"\5\177\u06f0\n\177\3\177\3\177\3\177\2\4\u00c8\u00d8\u0080\2\4\6\b\n\f"+
		"\16\20\22\24\26\30\32\34\36 \"$&(*,.\60\62\64\668:<>@BDFHJLNPRTVXZ\\^"+
		"`bdfhjlnprtvxz|~\u0080\u0082\u0084\u0086\u0088\u008a\u008c\u008e\u0090"+
		"\u0092\u0094\u0096\u0098\u009a\u009c\u009e\u00a0\u00a2\u00a4\u00a6\u00a8"+
		"\u00aa\u00ac\u00ae\u00b0\u00b2\u00b4\u00b6\u00b8\u00ba\u00bc\u00be\u00c0"+
		"\u00c2\u00c4\u00c6\u00c8\u00ca\u00cc\u00ce\u00d0\u00d2\u00d4\u00d6\u00d8"+
		"\u00da\u00dc\u00de\u00e0\u00e2\u00e4\u00e6\u00e8\u00ea\u00ec\u00ee\u00f0"+
		"\u00f2\u00f4\u00f6\u00f8\u00fa\u00fc\2\22\4\2\23\23**\3\2EH\3\2IJ\4\2"+
		"((>>\4\2\65C\u0083\u0083\5\2\65>AC\u0083\u0083\3\2fi\3\2\\]\4\2jkoo\3"+
		"\2hi\4\2Z[ab\4\2``cc\4\2YYpz\3\2fg\4\2__{{\n\2\5\5\7\7\n\n\20\20\26\26"+
		"\35\35\37\37\'\'\2\u07bb\2\u0110\3\2\2\2\4\u0115\3\2\2\2\6\u011c\3\2\2"+
		"\2\b\u0135\3\2\2\2\n\u013c\3\2\2\2\f\u0148\3\2\2\2\16\u014c\3\2\2\2\20"+
		"\u014e\3\2\2\2\22\u0161\3\2\2\2\24\u016f\3\2\2\2\26\u017d\3\2\2\2\30\u0185"+
		"\3\2\2\2\32\u0197\3\2\2\2\34\u01a2\3\2\2\2\36\u01ac\3\2\2\2 \u01b3\3\2"+
		"\2\2\"\u01c2\3\2\2\2$\u01cb\3\2\2\2&\u01e0\3\2\2\2(\u01ec\3\2\2\2*\u01ee"+
		"\3\2\2\2,\u0200\3\2\2\2.\u0204\3\2\2\2\60\u0206\3\2\2\2\62\u0209\3\2\2"+
		"\2\64\u020c\3\2\2\2\66\u0217\3\2\2\28\u021d\3\2\2\2:\u0229\3\2\2\2<\u0233"+
		"\3\2\2\2>\u0235\3\2\2\2@\u0240\3\2\2\2B\u024e\3\2\2\2D\u0259\3\2\2\2F"+
		"\u025e\3\2\2\2H\u0267\3\2\2\2J\u027a\3\2\2\2L\u0282\3\2\2\2N\u0287\3\2"+
		"\2\2P\u0291\3\2\2\2R\u0293\3\2\2\2T\u02ab\3\2\2\2V\u02be\3\2\2\2X\u02c0"+
		"\3\2\2\2Z\u02c8\3\2\2\2\\\u02d8\3\2\2\2^\u02f0\3\2\2\2`\u02f5\3\2\2\2"+
		"b\u02fe\3\2\2\2d\u030b\3\2\2\2f\u0316\3\2\2\2h\u031c\3\2\2\2j\u032b\3"+
		"\2\2\2l\u032d\3\2\2\2n\u032f\3\2\2\2p\u0336\3\2\2\2r\u033f\3\2\2\2t\u0349"+
		"\3\2\2\2v\u0351\3\2\2\2x\u0358\3\2\2\2z\u035a\3\2\2\2|\u036a\3\2\2\2~"+
		"\u036f\3\2\2\2\u0080\u0380\3\2\2\2\u0082\u039a\3\2\2\2\u0084\u039e\3\2"+
		"\2\2\u0086\u03a0\3\2\2\2\u0088\u03a6\3\2\2\2\u008a\u03a8\3\2\2\2\u008c"+
		"\u03ac\3\2\2\2\u008e\u03b2\3\2\2\2\u0090\u03df\3\2\2\2\u0092\u03e1\3\2"+
		"\2\2\u0094\u03e3\3\2\2\2\u0096\u03ef\3\2\2\2\u0098\u03f5\3\2\2\2\u009a"+
		"\u03fd\3\2\2\2\u009c\u0400\3\2\2\2\u009e\u040a\3\2\2\2\u00a0\u0418\3\2"+
		"\2\2\u00a2\u041d\3\2\2\2\u00a4\u042a\3\2\2\2\u00a6\u042c\3\2\2\2\u00a8"+
		"\u0431\3\2\2\2\u00aa\u04aa\3\2\2\2\u00ac\u04ac\3\2\2\2\u00ae\u04b9\3\2"+
		"\2\2\u00b0\u04c1\3\2\2\2\u00b2\u04c4\3\2\2\2\u00b4\u04cb\3\2\2\2\u00b6"+
		"\u04e4\3\2\2\2\u00b8\u04e7\3\2\2\2\u00ba\u04fb\3\2\2\2\u00bc\u0509\3\2"+
		"\2\2\u00be\u050d\3\2\2\2\u00c0\u0512\3\2\2\2\u00c2\u051d\3\2\2\2\u00c4"+
		"\u0521\3\2\2\2\u00c6\u053c\3\2\2\2\u00c8\u056b\3\2\2\2\u00ca\u05c6\3\2"+
		"\2\2\u00cc\u05d2\3\2\2\2\u00ce\u05ec\3\2\2\2\u00d0\u05f0\3\2\2\2\u00d2"+
		"\u0604\3\2\2\2\u00d4\u0606\3\2\2\2\u00d6\u061c\3\2\2\2\u00d8\u0638\3\2"+
		"\2\2\u00da\u0649\3\2\2\2\u00dc\u064e\3\2\2\2\u00de\u0663\3\2\2\2\u00e0"+
		"\u0674\3\2\2\2\u00e2\u0676\3\2\2\2\u00e4\u067c\3\2\2\2\u00e6\u069a\3\2"+
		"\2\2\u00e8\u069e\3\2\2\2\u00ea\u06a4\3\2\2\2\u00ec\u06a9\3\2\2\2\u00ee"+
		"\u06ab\3\2\2\2\u00f0\u06af\3\2\2\2\u00f2\u06ba\3\2\2\2\u00f4\u06ce\3\2"+
		"\2\2\u00f6\u06d0\3\2\2\2\u00f8\u06e4\3\2\2\2\u00fa\u06eb\3\2\2\2\u00fc"+
		"\u06ed\3\2\2\2\u00fe\u0100\5\4\3\2\u00ff\u00fe\3\2\2\2\u00ff\u0100\3\2"+
		"\2\2\u0100\u0104\3\2\2\2\u0101\u0103\5\6\4\2\u0102\u0101\3\2\2\2\u0103"+
		"\u0106\3\2\2\2\u0104\u0102\3\2\2\2\u0104\u0105\3\2\2\2\u0105\u010a\3\2"+
		"\2\2\u0106\u0104\3\2\2\2\u0107\u0109\5\b\5\2\u0108\u0107\3\2\2\2\u0109"+
		"\u010c\3\2\2\2\u010a\u0108\3\2\2\2\u010a\u010b\3\2\2\2\u010b\u0111\3\2"+
		"\2\2\u010c\u010a\3\2\2\2\u010d\u010e\5\u008cG\2\u010e\u010f\7\2\2\3\u010f"+
		"\u0111\3\2\2\2\u0110\u00ff\3\2\2\2\u0110\u010d\3\2\2\2\u0111\3\3\2\2\2"+
		"\u0112\u0114\5r:\2\u0113\u0112\3\2\2\2\u0114\u0117\3\2\2\2\u0115\u0113"+
		"\3\2\2\2\u0115\u0116\3\2\2\2\u0116\u0118\3\2\2\2\u0117\u0115\3\2\2\2\u0118"+
		"\u0119\7\"\2\2\u0119\u011a\5h\65\2\u011a\u011b\7V\2\2\u011b\5\3\2\2\2"+
		"\u011c\u011e\7\33\2\2\u011d\u011f\7(\2\2\u011e\u011d\3\2\2\2\u011e\u011f"+
		"\3\2\2\2\u011f\u0120\3\2\2\2\u0120\u0123\5h\65\2\u0121\u0122\7X\2\2\u0122"+
		"\u0124\7j\2\2\u0123\u0121\3\2\2\2\u0123\u0124\3\2\2\2\u0124\u0125\3\2"+
		"\2\2\u0125\u0126\7V\2\2\u0126\7\3\2\2\2\u0127\u0129\5\f\7\2\u0128\u0127"+
		"\3\2\2\2\u0129\u012c\3\2\2\2\u012a\u0128\3\2\2\2\u012a\u012b\3\2\2\2\u012b"+
		"\u0132\3\2\2\2\u012c\u012a\3\2\2\2\u012d\u0133\5\20\t\2\u012e\u0133\5"+
		"\30\r\2\u012f\u0133\5 \21\2\u0130\u0133\5|?\2\u0131\u0133\5\u0094K\2\u0132"+
		"\u012d\3\2\2\2\u0132\u012e\3\2\2\2\u0132\u012f\3\2\2\2\u0132\u0130\3\2"+
		"\2\2\u0132\u0131\3\2\2\2\u0133\u0136\3\2\2\2\u0134\u0136\7V\2\2\u0135"+
		"\u012a\3\2\2\2\u0135\u0134\3\2\2\2\u0136\t\3\2\2\2\u0137\u013d\5\f\7\2"+
		"\u0138\u013d\7 \2\2\u0139\u013d\7,\2\2\u013a\u013d\7\60\2\2\u013b\u013d"+
		"\7\63\2\2\u013c\u0137\3\2\2\2\u013c\u0138\3\2\2\2\u013c\u0139\3\2\2\2"+
		"\u013c\u013a\3\2\2\2\u013c\u013b\3\2\2\2\u013d\13\3\2\2\2\u013e\u0149"+
		"\5r:\2\u013f\u0149\7%\2\2\u0140\u0149\7$\2\2\u0141\u0149\7#\2\2\u0142"+
		"\u0149\7(\2\2\u0143\u0149\7\3\2\2\u0144\u0149\7\24\2\2\u0145\u0149\7)"+
		"\2\2\u0146\u0149\7B\2\2\u0147\u0149\7D\2\2\u0148\u013e\3\2\2\2\u0148\u013f"+
		"\3\2\2\2\u0148\u0140\3\2\2\2\u0148\u0141\3\2\2\2\u0148\u0142\3\2\2\2\u0148"+
		"\u0143\3\2\2\2\u0148\u0144\3\2\2\2\u0148\u0145\3\2\2\2\u0148\u0146\3\2"+
		"\2\2\u0148\u0147\3\2\2\2\u0149\r\3\2\2\2\u014a\u014d\7\24\2\2\u014b\u014d"+
		"\5r:\2\u014c\u014a\3\2\2\2\u014c\u014b\3\2\2\2\u014d\17\3\2\2\2\u014e"+
		"\u014f\7\13\2\2\u014f\u0151\5\u00a4S\2\u0150\u0152\5\22\n\2\u0151\u0150"+
		"\3\2\2\2\u0151\u0152\3\2\2\2\u0152\u0155\3\2\2\2\u0153\u0154\7\23\2\2"+
		"\u0154\u0156\5\u00f2z\2\u0155\u0153\3\2\2\2\u0155\u0156\3\2\2\2\u0156"+
		"\u0159\3\2\2\2\u0157\u0158\7\32\2\2\u0158\u015a\5\u00f0y\2\u0159\u0157"+
		"\3\2\2\2\u0159\u015a\3\2\2\2\u015a\u015d\3\2\2\2\u015b\u015c\7C\2\2\u015c"+
		"\u015e\5\u00f0y\2\u015d\u015b\3\2\2\2\u015d\u015e\3\2\2\2\u015e\u015f"+
		"\3\2\2\2\u015f\u0160\5\"\22\2\u0160\21\3\2\2\2\u0161\u0162\7[\2\2\u0162"+
		"\u0167\5\24\13\2\u0163\u0164\7W\2\2\u0164\u0166\5\24\13\2\u0165\u0163"+
		"\3\2\2\2\u0166\u0169\3\2\2\2\u0167\u0165\3\2\2\2\u0167\u0168\3\2\2\2\u0168"+
		"\u016a\3\2\2\2\u0169\u0167\3\2\2\2\u016a\u016b\7Z\2\2\u016b\23\3\2\2\2"+
		"\u016c\u016e\5r:\2\u016d\u016c\3\2\2\2\u016e\u0171\3\2\2\2\u016f\u016d"+
		"\3\2\2\2\u016f\u0170\3\2\2\2\u0170\u0172\3\2\2\2\u0171\u016f\3\2\2\2\u0172"+
		"\u017b\5\u00a4S\2\u0173\u0177\7\23\2\2\u0174\u0176\5r:\2\u0175\u0174\3"+
		"\2\2\2\u0176\u0179\3\2\2\2\u0177\u0175\3\2\2\2\u0177\u0178\3\2\2\2\u0178"+
		"\u017a\3\2\2\2\u0179\u0177\3\2\2\2\u017a\u017c\5\26\f\2\u017b\u0173\3"+
		"\2\2\2\u017b\u017c\3\2\2\2\u017c\25\3\2\2\2\u017d\u0182\5\u00f2z\2\u017e"+
		"\u017f\7l\2\2\u017f\u0181\5\u00f2z\2\u0180\u017e\3\2\2\2\u0181\u0184\3"+
		"\2\2\2\u0182\u0180\3\2\2\2\u0182\u0183\3\2\2\2\u0183\27\3\2\2\2\u0184"+
		"\u0182\3\2\2\2\u0185\u0186\7\22\2\2\u0186\u0189\5\u00a4S\2\u0187\u0188"+
		"\7\32\2\2\u0188\u018a\5\u00f0y\2\u0189\u0187\3\2\2\2\u0189\u018a\3\2\2"+
		"\2\u018a\u018b\3\2\2\2\u018b\u018d\7R\2\2\u018c\u018e\5\32\16\2\u018d"+
		"\u018c\3\2\2\2\u018d\u018e\3\2\2\2\u018e\u0190\3\2\2\2\u018f\u0191\7W"+
		"\2\2\u0190\u018f\3\2\2\2\u0190\u0191\3\2\2\2\u0191\u0193\3\2\2\2\u0192"+
		"\u0194\5\36\20\2\u0193\u0192\3\2\2\2\u0193\u0194\3\2\2\2\u0194\u0195\3"+
		"\2\2\2\u0195\u0196\7S\2\2\u0196\31\3\2\2\2\u0197\u019c\5\34\17\2\u0198"+
		"\u0199\7W\2\2\u0199\u019b\5\34\17\2\u019a\u0198\3\2\2\2\u019b\u019e\3"+
		"\2\2\2\u019c\u019a\3\2\2\2\u019c\u019d\3\2\2\2\u019d\33\3\2\2\2\u019e"+
		"\u019c\3\2\2\2\u019f\u01a1\5r:\2\u01a0\u019f\3\2\2\2\u01a1\u01a4\3\2\2"+
		"\2\u01a2\u01a0\3\2\2\2\u01a2\u01a3\3\2\2\2\u01a3\u01a5\3\2\2\2\u01a4\u01a2"+
		"\3\2\2\2\u01a5\u01a7\5\u00a4S\2\u01a6\u01a8\5\u00fc\177\2\u01a7\u01a6"+
		"\3\2\2\2\u01a7\u01a8\3\2\2\2\u01a8\u01aa\3\2\2\2\u01a9\u01ab\5\"\22\2"+
		"\u01aa\u01a9\3\2\2\2\u01aa\u01ab\3\2\2\2\u01ab\35\3\2\2\2\u01ac\u01b0"+
		"\7V\2\2\u01ad\u01af\5&\24\2\u01ae\u01ad\3\2\2\2\u01af\u01b2\3\2\2\2\u01b0"+
		"\u01ae\3\2\2\2\u01b0\u01b1\3\2\2\2\u01b1\37\3\2\2\2\u01b2\u01b0\3\2\2"+
		"\2\u01b3\u01b4\7\36\2\2\u01b4\u01b6\5\u00a4S\2\u01b5\u01b7\5\22\n\2\u01b6"+
		"\u01b5\3\2\2\2\u01b6\u01b7\3\2\2\2\u01b7\u01ba\3\2\2\2\u01b8\u01b9\7\23"+
		"\2\2\u01b9\u01bb\5\u00f0y\2\u01ba\u01b8\3\2\2\2\u01ba\u01bb\3\2\2\2\u01bb"+
		"\u01be\3\2\2\2\u01bc\u01bd\7C\2\2\u01bd\u01bf\5\u00f0y\2\u01be\u01bc\3"+
		"\2\2\2\u01be\u01bf\3\2\2\2\u01bf\u01c0\3\2\2\2\u01c0\u01c1\5$\23\2\u01c1"+
		"!\3\2\2\2\u01c2\u01c6\7R\2\2\u01c3\u01c5\5&\24\2\u01c4\u01c3\3\2\2\2\u01c5"+
		"\u01c8\3\2\2\2\u01c6\u01c4\3\2\2\2\u01c6\u01c7\3\2\2\2\u01c7\u01c9\3\2"+
		"\2\2\u01c8\u01c6\3\2\2\2\u01c9\u01ca\7S\2\2\u01ca#\3\2\2\2\u01cb\u01cf"+
		"\7R\2\2\u01cc\u01ce\5:\36\2\u01cd\u01cc\3\2\2\2\u01ce\u01d1\3\2\2\2\u01cf"+
		"\u01cd\3\2\2\2\u01cf\u01d0\3\2\2\2\u01d0\u01d2\3\2\2\2\u01d1\u01cf\3\2"+
		"\2\2\u01d2\u01d3\7S\2\2\u01d3%\3\2\2\2\u01d4\u01e1\7V\2\2\u01d5\u01d7"+
		"\7(\2\2\u01d6\u01d5\3\2\2\2\u01d6\u01d7\3\2\2\2\u01d7\u01d8\3\2\2\2\u01d8"+
		"\u01e1\5\u009eP\2\u01d9\u01db\5\n\6\2\u01da\u01d9\3\2\2\2\u01db\u01de"+
		"\3\2\2\2\u01dc\u01da\3\2\2\2\u01dc\u01dd\3\2\2\2\u01dd\u01df\3\2\2\2\u01de"+
		"\u01dc\3\2\2\2\u01df\u01e1\5(\25\2\u01e0\u01d4\3\2\2\2\u01e0\u01d6\3\2"+
		"\2\2\u01e0\u01dc\3\2\2\2\u01e1\'\3\2\2\2\u01e2\u01ed\5\u0094K\2\u01e3"+
		"\u01ed\5*\26\2\u01e4\u01ed\5\60\31\2\u01e5\u01ed\58\35\2\u01e6\u01ed\5"+
		"\64\33\2\u01e7\u01ed\5\62\32\2\u01e8\u01ed\5 \21\2\u01e9\u01ed\5|?\2\u01ea"+
		"\u01ed\5\20\t\2\u01eb\u01ed\5\30\r\2\u01ec\u01e2\3\2\2\2\u01ec\u01e3\3"+
		"\2\2\2\u01ec\u01e4\3\2\2\2\u01ec\u01e5\3\2\2\2\u01ec\u01e6\3\2\2\2\u01ec"+
		"\u01e7\3\2\2\2\u01ec\u01e8\3\2\2\2\u01ec\u01e9\3\2\2\2\u01ec\u01ea\3\2"+
		"\2\2\u01ec\u01eb\3\2\2\2\u01ed)\3\2\2\2\u01ee\u01ef\5.\30\2\u01ef\u01f0"+
		"\5\u00a4S\2\u01f0\u01f5\5Z.\2\u01f1\u01f2\7T\2\2\u01f2\u01f4\7U\2\2\u01f3"+
		"\u01f1\3\2\2\2\u01f4\u01f7\3\2\2\2\u01f5\u01f3\3\2\2\2\u01f5\u01f6\3\2"+
		"\2\2\u01f6\u01fa\3\2\2\2\u01f7\u01f5\3\2\2\2\u01f8\u01f9\7/\2\2\u01f9"+
		"\u01fb\5X-\2\u01fa\u01f8\3\2\2\2\u01fa\u01fb\3\2\2\2\u01fb\u01fc\3\2\2"+
		"\2\u01fc\u01fd\5,\27\2\u01fd+\3\2\2\2\u01fe\u0201\5\u009eP\2\u01ff\u0201"+
		"\7V\2\2\u0200\u01fe\3\2\2\2\u0200\u01ff\3\2\2\2\u0201-\3\2\2\2\u0202\u0205"+
		"\5\u00f2z\2\u0203\u0205\7\62\2\2\u0204\u0202\3\2\2\2\u0204\u0203\3\2\2"+
		"\2\u0205/\3\2\2\2\u0206\u0207\5\22\n\2\u0207\u0208\5*\26\2\u0208\61\3"+
		"\2\2\2\u0209\u020a\5\22\n\2\u020a\u020b\5\64\33\2\u020b\63\3\2\2\2\u020c"+
		"\u020d\5\u00a4S\2\u020d\u0210\5Z.\2\u020e\u020f\7/\2\2\u020f\u0211\5X"+
		"-\2\u0210\u020e\3\2\2\2\u0210\u0211\3\2\2\2\u0211\u0212\3\2\2\2\u0212"+
		"\u0213\5\u009eP\2\u0213\65\3\2\2\2\u0214\u0216\5\n\6\2\u0215\u0214\3\2"+
		"\2\2\u0216\u0219\3\2\2\2\u0217\u0215\3\2\2\2\u0217\u0218\3\2\2\2\u0218"+
		"\u021a\3\2\2\2\u0219\u0217\3\2\2\2\u021a\u021b\5\u00a4S\2\u021b\u021c"+
		"\5\u009eP\2\u021c\67\3\2\2\2\u021d\u021e\5\u00f2z\2\u021e\u021f\5J&\2"+
		"\u021f\u0220\7V\2\2\u02209\3\2\2\2\u0221\u0223\5\n\6\2\u0222\u0221\3\2"+
		"\2\2\u0223\u0226\3\2\2\2\u0224\u0222\3\2\2\2\u0224\u0225\3\2\2\2\u0225"+
		"\u0227\3\2\2\2\u0226\u0224\3\2\2\2\u0227\u022a\5<\37\2\u0228\u022a\7V"+
		"\2\2\u0229\u0224\3\2\2\2\u0229\u0228\3\2\2\2\u022a;\3\2\2\2\u022b\u0234"+
		"\5> \2\u022c\u0234\5B\"\2\u022d\u0234\5F$\2\u022e\u0234\5 \21\2\u022f"+
		"\u0234\5|?\2\u0230\u0234\5\20\t\2\u0231\u0234\5\30\r\2\u0232\u0234\5\u0094"+
		"K\2\u0233\u022b\3\2\2\2\u0233\u022c\3\2\2\2\u0233\u022d\3\2\2\2\u0233"+
		"\u022e\3\2\2\2\u0233\u022f\3\2\2\2\u0233\u0230\3\2\2\2\u0233\u0231\3\2"+
		"\2\2\u0233\u0232\3\2\2\2\u0234=\3\2\2\2\u0235\u0236\5\u00f2z\2\u0236\u023b"+
		"\5@!\2\u0237\u0238\7W\2\2\u0238\u023a\5@!\2\u0239\u0237\3\2\2\2\u023a"+
		"\u023d\3\2\2\2\u023b\u0239\3\2\2\2\u023b\u023c\3\2\2\2\u023c\u023e\3\2"+
		"\2\2\u023d\u023b\3\2\2\2\u023e\u023f\7V\2\2\u023f?\3\2\2\2\u0240\u0245"+
		"\5\u00a4S\2\u0241\u0242\7T\2\2\u0242\u0244\7U\2\2\u0243\u0241\3\2\2\2"+
		"\u0244\u0247\3\2\2\2\u0245\u0243\3\2\2\2\u0245\u0246\3\2\2\2\u0246\u0248"+
		"\3\2\2\2\u0247\u0245\3\2\2\2\u0248\u0249\7Y\2\2\u0249\u024a\5P)\2\u024a"+
		"A\3\2\2\2\u024b\u024d\5D#\2\u024c\u024b\3\2\2\2\u024d\u0250\3\2\2\2\u024e"+
		"\u024c\3\2\2\2\u024e\u024f\3\2\2\2\u024f\u0251\3\2\2\2\u0250\u024e\3\2"+
		"\2\2\u0251\u0252\5H%\2\u0252C\3\2\2\2\u0253\u025a\5r:\2\u0254\u025a\7"+
		"%\2\2\u0255\u025a\7\3\2\2\u0256\u025a\7\16\2\2\u0257\u025a\7(\2\2\u0258"+
		"\u025a\7)\2\2\u0259\u0253\3\2\2\2\u0259\u0254\3\2\2\2\u0259\u0255\3\2"+
		"\2\2\u0259\u0256\3\2\2\2\u0259\u0257\3\2\2\2\u0259\u0258\3\2\2\2\u025a"+
		"E\3\2\2\2\u025b\u025d\5D#\2\u025c\u025b\3\2\2\2\u025d\u0260\3\2\2\2\u025e"+
		"\u025c\3\2\2\2\u025e\u025f\3\2\2\2\u025f\u0261\3\2\2\2\u0260\u025e\3\2"+
		"\2\2\u0261\u0262\5\22\n\2\u0262\u0263\5H%\2\u0263G\3\2\2\2\u0264\u0266"+
		"\5r:\2\u0265\u0264\3\2\2\2\u0266\u0269\3\2\2\2\u0267\u0265\3\2\2\2\u0267"+
		"\u0268\3\2\2\2\u0268\u026a\3\2\2\2\u0269\u0267\3\2\2\2\u026a\u026b\5."+
		"\30\2\u026b\u026c\5\u00a4S\2\u026c\u0271\5Z.\2\u026d\u026e\7T\2\2\u026e"+
		"\u0270\7U\2\2\u026f\u026d\3\2\2\2\u0270\u0273\3\2\2\2\u0271\u026f\3\2"+
		"\2\2\u0271\u0272\3\2\2\2\u0272\u0276\3\2\2\2\u0273\u0271\3\2\2\2\u0274"+
		"\u0275\7/\2\2\u0275\u0277\5X-\2\u0276\u0274\3\2\2\2\u0276\u0277\3\2\2"+
		"\2\u0277\u0278\3\2\2\2\u0278\u0279\5,\27\2\u0279I\3\2\2\2\u027a\u027f"+
		"\5L\'\2\u027b\u027c\7W\2\2\u027c\u027e\5L\'\2\u027d\u027b\3\2\2\2\u027e"+
		"\u0281\3\2\2\2\u027f\u027d\3\2\2\2\u027f\u0280\3\2\2\2\u0280K\3\2\2\2"+
		"\u0281\u027f\3\2\2\2\u0282\u0285\5N(\2\u0283\u0284\7Y\2\2\u0284\u0286"+
		"\5P)\2\u0285\u0283\3\2\2\2\u0285\u0286\3\2\2\2\u0286M\3\2\2\2\u0287\u028c"+
		"\5\u00a4S\2\u0288\u0289\7T\2\2\u0289\u028b\7U\2\2\u028a\u0288\3\2\2\2"+
		"\u028b\u028e\3\2\2\2\u028c\u028a\3\2\2\2\u028c\u028d\3\2\2\2\u028dO\3"+
		"\2\2\2\u028e\u028c\3\2\2\2\u028f\u0292\5R*\2\u0290\u0292\5\u00c8e\2\u0291"+
		"\u028f\3\2\2\2\u0291\u0290\3\2\2\2\u0292Q\3\2\2\2\u0293\u029f\7R\2\2\u0294"+
		"\u0299\5P)\2\u0295\u0296\7W\2\2\u0296\u0298\5P)\2\u0297\u0295\3\2\2\2"+
		"\u0298\u029b\3\2\2\2\u0299\u0297\3\2\2\2\u0299\u029a\3\2\2\2\u029a\u029d"+
		"\3\2\2\2\u029b\u0299\3\2\2\2\u029c\u029e\7W\2\2\u029d\u029c\3\2\2\2\u029d"+
		"\u029e\3\2\2\2\u029e\u02a0\3\2\2\2\u029f\u0294\3\2\2\2\u029f\u02a0\3\2"+
		"\2\2\u02a0\u02a1\3\2\2\2\u02a1\u02a2\7S\2\2\u02a2S\3\2\2\2\u02a3\u02a5"+
		"\5\u00a4S\2\u02a4\u02a6\5\u00f6|\2\u02a5\u02a4\3\2\2\2\u02a5\u02a6\3\2"+
		"\2\2\u02a6\u02a7\3\2\2\2\u02a7\u02a8\7X\2\2\u02a8\u02aa\3\2\2\2\u02a9"+
		"\u02a3\3\2\2\2\u02aa\u02ad\3\2\2\2\u02ab\u02a9\3\2\2\2\u02ab\u02ac\3\2"+
		"\2\2\u02ac\u02ae\3\2\2\2\u02ad\u02ab\3\2\2\2\u02ae\u02b0\5\u00a6T\2\u02af"+
		"\u02b1\5\u00f6|\2\u02b0\u02af\3\2\2\2\u02b0\u02b1\3\2\2\2\u02b1U\3\2\2"+
		"\2\u02b2\u02bf\5\u00f2z\2\u02b3\u02b5\5r:\2\u02b4\u02b3\3\2\2\2\u02b5"+
		"\u02b8\3\2\2\2\u02b6\u02b4\3\2\2\2\u02b6\u02b7\3\2\2\2\u02b7\u02b9\3\2"+
		"\2\2\u02b8\u02b6\3\2\2\2\u02b9\u02bc\7^\2\2\u02ba\u02bb\t\2\2\2\u02bb"+
		"\u02bd\5\u00f2z\2\u02bc\u02ba\3\2\2\2\u02bc\u02bd\3\2\2\2\u02bd\u02bf"+
		"\3\2\2\2\u02be\u02b2\3\2\2\2\u02be\u02b6\3\2\2\2\u02bfW\3\2\2\2\u02c0"+
		"\u02c5\5h\65\2\u02c1\u02c2\7W\2\2\u02c2\u02c4\5h\65\2\u02c3\u02c1\3\2"+
		"\2\2\u02c4\u02c7\3\2\2\2\u02c5\u02c3\3\2\2\2\u02c5\u02c6\3\2\2\2\u02c6"+
		"Y\3\2\2\2\u02c7\u02c5\3\2\2\2\u02c8\u02d4\7P\2\2\u02c9\u02cb\5\\/\2\u02ca"+
		"\u02c9\3\2\2\2\u02ca\u02cb\3\2\2\2\u02cb\u02d5\3\2\2\2\u02cc\u02cf\5\\"+
		"/\2\u02cd\u02ce\7W\2\2\u02ce\u02d0\5^\60\2\u02cf\u02cd\3\2\2\2\u02cf\u02d0"+
		"\3\2\2\2\u02d0\u02d5\3\2\2\2\u02d1\u02d3\5^\60\2\u02d2\u02d1\3\2\2\2\u02d2"+
		"\u02d3\3\2\2\2\u02d3\u02d5\3\2\2\2\u02d4\u02ca\3\2\2\2\u02d4\u02cc\3\2"+
		"\2\2\u02d4\u02d2\3\2\2\2\u02d5\u02d6\3\2\2\2\u02d6\u02d7\7Q\2\2\u02d7"+
		"[\3\2\2\2\u02d8\u02de\5\u00f2z\2\u02d9\u02da\5\u00a4S\2\u02da\u02db\7"+
		"X\2\2\u02db\u02dd\3\2\2\2\u02dc\u02d9\3\2\2\2\u02dd\u02e0\3\2\2\2\u02de"+
		"\u02dc\3\2\2\2\u02de\u02df\3\2\2\2\u02df\u02e1\3\2\2\2\u02e0\u02de\3\2"+
		"\2\2\u02e1\u02e2\7-\2\2\u02e2]\3\2\2\2\u02e3\u02e8\5`\61\2\u02e4\u02e5"+
		"\7W\2\2\u02e5\u02e7\5`\61\2\u02e6\u02e4\3\2\2\2\u02e7\u02ea\3\2\2\2\u02e8"+
		"\u02e6\3\2\2\2\u02e8\u02e9\3\2\2\2\u02e9\u02ed\3\2\2\2\u02ea\u02e8\3\2"+
		"\2\2\u02eb\u02ec\7W\2\2\u02ec\u02ee\5b\62\2\u02ed\u02eb\3\2\2\2\u02ed"+
		"\u02ee\3\2\2\2\u02ee\u02f1\3\2\2\2\u02ef\u02f1\5b\62\2\u02f0\u02e3\3\2"+
		"\2\2\u02f0\u02ef\3\2\2\2\u02f1_\3\2\2\2\u02f2\u02f4\5\16\b\2\u02f3\u02f2"+
		"\3\2\2\2\u02f4\u02f7\3\2\2\2\u02f5\u02f3\3\2\2\2\u02f5\u02f6\3\2\2\2\u02f6"+
		"\u02f8\3\2\2\2\u02f7\u02f5\3\2\2\2\u02f8\u02f9\5\u00f2z\2\u02f9\u02fa"+
		"\5N(\2\u02faa\3\2\2\2\u02fb\u02fd\5\16\b\2\u02fc\u02fb\3\2\2\2\u02fd\u0300"+
		"\3\2\2\2\u02fe\u02fc\3\2\2\2\u02fe\u02ff\3\2\2\2\u02ff\u0301\3\2\2\2\u0300"+
		"\u02fe\3\2\2\2\u0301\u0305\5\u00f2z\2\u0302\u0304\5r:\2\u0303\u0302\3"+
		"\2\2\2\u0304\u0307\3\2\2\2\u0305\u0303\3\2\2\2\u0305\u0306\3\2\2\2\u0306"+
		"\u0308\3\2\2\2\u0307\u0305\3\2\2\2\u0308\u0309\7~\2\2\u0309\u030a\5N("+
		"\2\u030ac\3\2\2\2\u030b\u0310\5f\64\2\u030c\u030d\7W\2\2\u030d\u030f\5"+
		"f\64\2\u030e\u030c\3\2\2\2\u030f\u0312\3\2\2\2\u0310\u030e\3\2\2\2\u0310"+
		"\u0311\3\2\2\2\u0311e\3\2\2\2\u0312\u0310\3\2\2\2\u0313\u0315\5\16\b\2"+
		"\u0314\u0313\3\2\2\2\u0315\u0318\3\2\2\2\u0316\u0314\3\2\2\2\u0316\u0317"+
		"\3\2\2\2\u0317\u0319\3\2\2\2\u0318\u0316\3\2\2\2\u0319\u031a\7?\2\2\u031a"+
		"\u031b\5\u00a4S\2\u031bg\3\2\2\2\u031c\u0321\5\u00a4S\2\u031d\u031e\7"+
		"X\2\2\u031e\u0320\5\u00a4S\2\u031f\u031d\3\2\2\2\u0320\u0323\3\2\2\2\u0321"+
		"\u031f\3\2\2\2\u0321\u0322\3\2\2\2\u0322i\3\2\2\2\u0323\u0321\3\2\2\2"+
		"\u0324\u032c\5l\67\2\u0325\u032c\5n8\2\u0326\u032c\7L\2\2\u0327\u032c"+
		"\7M\2\2\u0328\u032c\7K\2\2\u0329\u032c\7O\2\2\u032a\u032c\7N\2\2\u032b"+
		"\u0324\3\2\2\2\u032b\u0325\3\2\2\2\u032b\u0326\3\2\2\2\u032b\u0327\3\2"+
		"\2\2\u032b\u0328\3\2\2\2\u032b\u0329\3\2\2\2\u032b\u032a\3\2\2\2\u032c"+
		"k\3\2\2\2\u032d\u032e\t\3\2\2\u032em\3\2\2\2\u032f\u0330\t\4\2\2\u0330"+
		"o\3\2\2\2\u0331\u0332\5\u00a4S\2\u0332\u0333\7X\2\2\u0333\u0335\3\2\2"+
		"\2\u0334\u0331\3\2\2\2\u0335\u0338\3\2\2\2\u0336\u0334\3\2\2\2\u0336\u0337"+
		"\3\2\2\2\u0337\u0339\3\2\2\2\u0338\u0336\3\2\2\2\u0339\u033a\7}\2\2\u033a"+
		"\u033b\5\u00a4S\2\u033bq\3\2\2\2\u033c\u033d\7}\2\2\u033d\u0340\5h\65"+
		"\2\u033e\u0340\5p9\2\u033f\u033c\3\2\2\2\u033f\u033e\3\2\2\2\u0340\u0347"+
		"\3\2\2\2\u0341\u0344\7P\2\2\u0342\u0345\5t;\2\u0343\u0345\5x=\2\u0344"+
		"\u0342\3\2\2\2\u0344\u0343\3\2\2\2\u0344\u0345\3\2\2\2\u0345\u0346\3\2"+
		"\2\2\u0346\u0348\7Q\2\2\u0347\u0341\3\2\2\2\u0347\u0348\3\2\2\2\u0348"+
		"s\3\2\2\2\u0349\u034e\5v<\2\u034a\u034b\7W\2\2\u034b\u034d\5v<\2\u034c"+
		"\u034a\3\2\2\2\u034d\u0350\3\2\2\2\u034e\u034c\3\2\2\2\u034e\u034f\3\2"+
		"\2\2\u034fu\3\2\2\2\u0350\u034e\3\2\2\2\u0351\u0352\5\u00a4S\2\u0352\u0353"+
		"\7Y\2\2\u0353\u0354\5x=\2\u0354w\3\2\2\2\u0355\u0359\5\u00c8e\2\u0356"+
		"\u0359\5r:\2\u0357\u0359\5z>\2\u0358\u0355\3\2\2\2\u0358\u0356\3\2\2\2"+
		"\u0358\u0357\3\2\2\2\u0359y\3\2\2\2\u035a\u0363\7R\2\2\u035b\u0360\5x"+
		"=\2\u035c\u035d\7W\2\2\u035d\u035f\5x=\2\u035e\u035c\3\2\2\2\u035f\u0362"+
		"\3\2\2\2\u0360\u035e\3\2\2\2\u0360\u0361\3\2\2\2\u0361\u0364\3\2\2\2\u0362"+
		"\u0360\3\2\2\2\u0363\u035b\3\2\2\2\u0363\u0364\3\2\2\2\u0364\u0366\3\2"+
		"\2\2\u0365\u0367\7W\2\2\u0366\u0365\3\2\2\2\u0366\u0367\3\2\2\2\u0367"+
		"\u0368\3\2\2\2\u0368\u0369\7S\2\2\u0369{\3\2\2\2\u036a\u036b\7}\2\2\u036b"+
		"\u036c\7\36\2\2\u036c\u036d\5\u00a4S\2\u036d\u036e\5~@\2\u036e}\3\2\2"+
		"\2\u036f\u0373\7R\2\2\u0370\u0372\5\u0080A\2\u0371\u0370\3\2\2\2\u0372"+
		"\u0375\3\2\2\2\u0373\u0371\3\2\2\2\u0373\u0374\3\2\2\2\u0374\u0376\3\2"+
		"\2\2\u0375\u0373\3\2\2\2\u0376\u0377\7S\2\2\u0377\177\3\2\2\2\u0378\u037a"+
		"\5\n\6\2\u0379\u0378\3\2\2\2\u037a\u037d\3\2\2\2\u037b\u0379\3\2\2\2\u037b"+
		"\u037c\3\2\2\2\u037c\u037e\3\2\2\2\u037d\u037b\3\2\2\2\u037e\u0381\5\u0082"+
		"B\2\u037f\u0381\7V\2\2\u0380\u037b\3\2\2\2\u0380\u037f\3\2\2\2\u0381\u0081"+
		"\3\2\2\2\u0382\u0383\5\u00f2z\2\u0383\u0384\5\u0084C\2\u0384\u0385\7V"+
		"\2\2\u0385\u039b\3\2\2\2\u0386\u0388\5\20\t\2\u0387\u0389\7V\2\2\u0388"+
		"\u0387\3\2\2\2\u0388\u0389\3\2\2\2\u0389\u039b\3\2\2\2\u038a\u038c\5 "+
		"\21\2\u038b\u038d\7V\2\2\u038c\u038b\3\2\2\2\u038c\u038d\3\2\2\2\u038d"+
		"\u039b\3\2\2\2\u038e\u0390\5\30\r\2\u038f\u0391\7V\2\2\u0390\u038f\3\2"+
		"\2\2\u0390\u0391\3\2\2\2\u0391\u039b\3\2\2\2\u0392\u0394\5|?\2\u0393\u0395"+
		"\7V\2\2\u0394\u0393\3\2\2\2\u0394\u0395\3\2\2\2\u0395\u039b\3\2\2\2\u0396"+
		"\u0398\5\u0094K\2\u0397\u0399\7V\2\2\u0398\u0397\3\2\2\2\u0398\u0399\3"+
		"\2\2\2\u0399\u039b\3\2\2\2\u039a\u0382\3\2\2\2\u039a\u0386\3\2\2\2\u039a"+
		"\u038a\3\2\2\2\u039a\u038e\3\2\2\2\u039a\u0392\3\2\2\2\u039a\u0396\3\2"+
		"\2\2\u039b\u0083\3\2\2\2\u039c\u039f\5\u0086D\2\u039d\u039f\5\u0088E\2"+
		"\u039e\u039c\3\2\2\2\u039e\u039d\3\2\2\2\u039f\u0085\3\2\2\2\u03a0\u03a1"+
		"\5\u00a4S\2\u03a1\u03a2\7P\2\2\u03a2\u03a4\7Q\2\2\u03a3\u03a5\5\u008a"+
		"F\2\u03a4\u03a3\3\2\2\2\u03a4\u03a5\3\2\2\2\u03a5\u0087\3\2\2\2\u03a6"+
		"\u03a7\5J&\2\u03a7\u0089\3\2\2\2\u03a8\u03a9\7\16\2\2\u03a9\u03aa\5x="+
		"\2\u03aa\u008b\3\2\2\2\u03ab\u03ad\7\66\2\2\u03ac\u03ab\3\2\2\2\u03ac"+
		"\u03ad\3\2\2\2\u03ad\u03ae\3\2\2\2\u03ae\u03af\7\65\2\2\u03af\u03b0\5"+
		"h\65\2\u03b0\u03b1\5\u008eH\2\u03b1\u008d\3\2\2\2\u03b2\u03b6\7R\2\2\u03b3"+
		"\u03b5\5\u0090I\2\u03b4\u03b3\3\2\2\2\u03b5\u03b8\3\2\2\2\u03b6\u03b4"+
		"\3\2\2\2\u03b6\u03b7\3\2\2\2\u03b7\u03b9\3\2\2\2\u03b8\u03b6\3\2\2\2\u03b9"+
		"\u03ba\7S\2\2\u03ba\u008f\3\2\2\2\u03bb\u03bf\7\67\2\2\u03bc\u03be\5\u0092"+
		"J\2\u03bd\u03bc\3\2\2\2\u03be\u03c1\3\2\2\2\u03bf\u03bd\3\2\2\2\u03bf"+
		"\u03c0\3\2\2\2\u03c0\u03c2\3\2\2\2\u03c1\u03bf\3\2\2\2\u03c2\u03c3\5h"+
		"\65\2\u03c3\u03c4\7V\2\2\u03c4\u03e0\3\2\2\2\u03c5\u03c6\78\2\2\u03c6"+
		"\u03c9\5h\65\2\u03c7\u03c8\7:\2\2\u03c8\u03ca\5h\65\2\u03c9\u03c7\3\2"+
		"\2\2\u03c9\u03ca\3\2\2\2\u03ca\u03cb\3\2\2\2\u03cb\u03cc\7V\2\2\u03cc"+
		"\u03e0\3\2\2\2\u03cd\u03ce\79\2\2\u03ce\u03d1\5h\65\2\u03cf\u03d0\7:\2"+
		"\2\u03d0\u03d2\5h\65\2\u03d1\u03cf\3\2\2\2\u03d1\u03d2\3\2\2\2\u03d2\u03d3"+
		"\3\2\2\2\u03d3\u03d4\7V\2\2\u03d4\u03e0\3\2\2\2\u03d5\u03d6\7;\2\2\u03d6"+
		"\u03d7\5h\65\2\u03d7\u03d8\7V\2\2\u03d8\u03e0\3\2\2\2\u03d9\u03da\7<\2"+
		"\2\u03da\u03db\5h\65\2\u03db\u03dc\7=\2\2\u03dc\u03dd\5h\65\2\u03dd\u03de"+
		"\7V\2\2\u03de\u03e0\3\2\2\2\u03df\u03bb\3\2\2\2\u03df\u03c5\3\2\2\2\u03df"+
		"\u03cd\3\2\2\2\u03df\u03d5\3\2\2\2\u03df\u03d9\3\2\2\2\u03e0\u0091\3\2"+
		"\2\2\u03e1\u03e2\t\5\2\2\u03e2\u0093\3\2\2\2\u03e3\u03e4\7A\2\2\u03e4"+
		"\u03e6\5\u00a4S\2\u03e5\u03e7\5\22\n\2\u03e6\u03e5\3\2\2\2\u03e6\u03e7"+
		"\3\2\2\2\u03e7\u03e8\3\2\2\2\u03e8\u03eb\5\u0096L\2\u03e9\u03ea\7\32\2"+
		"\2\u03ea\u03ec\5\u00f0y\2\u03eb\u03e9\3\2\2\2\u03eb\u03ec\3\2\2\2\u03ec"+
		"\u03ed\3\2\2\2\u03ed\u03ee\5\u009cO\2\u03ee\u0095\3\2\2\2\u03ef\u03f1"+
		"\7P\2\2\u03f0\u03f2\5\u0098M\2\u03f1\u03f0\3\2\2\2\u03f1\u03f2\3\2\2\2"+
		"\u03f2\u03f3\3\2\2\2\u03f3\u03f4\7Q\2\2\u03f4\u0097\3\2\2\2\u03f5\u03fa"+
		"\5\u009aN\2\u03f6\u03f7\7W\2\2\u03f7\u03f9\5\u009aN\2\u03f8\u03f6\3\2"+
		"\2\2\u03f9\u03fc\3\2\2\2\u03fa\u03f8\3\2\2\2\u03fa\u03fb\3\2\2\2\u03fb"+
		"\u0099\3\2\2\2\u03fc\u03fa\3\2\2\2\u03fd\u03fe\5\u00f2z\2\u03fe\u03ff"+
		"\5\u00a4S\2\u03ff\u009b\3\2\2\2\u0400\u0405\7R\2\2\u0401\u0404\5&\24\2"+
		"\u0402\u0404\5\66\34\2\u0403\u0401\3\2\2\2\u0403\u0402\3\2\2\2\u0404\u0407"+
		"\3\2\2\2\u0405\u0403\3\2\2\2\u0405\u0406\3\2\2\2\u0406\u0408\3\2\2\2\u0407"+
		"\u0405\3\2\2\2\u0408\u0409\7S\2\2\u0409\u009d\3\2\2\2\u040a\u040e\7R\2"+
		"\2\u040b\u040d\5\u00a0Q\2\u040c\u040b\3\2\2\2\u040d\u0410\3\2\2\2\u040e"+
		"\u040c\3\2\2\2\u040e\u040f\3\2\2\2\u040f\u0411\3\2\2\2\u0410\u040e\3\2"+
		"\2\2\u0411\u0412\7S\2\2\u0412\u009f\3\2\2\2\u0413\u0414\5\u00a2R\2\u0414"+
		"\u0415\7V\2\2\u0415\u0419\3\2\2\2\u0416\u0419\5\u00a8U\2\u0417\u0419\5"+
		"\u00aaV\2\u0418\u0413\3\2\2\2\u0418\u0416\3\2\2\2\u0418\u0417\3\2\2\2"+
		"\u0419\u00a1\3\2\2\2\u041a\u041c\5\16\b\2\u041b\u041a\3\2\2\2\u041c\u041f"+
		"\3\2\2\2\u041d\u041b\3\2\2\2\u041d\u041e\3\2\2\2\u041e\u0428\3\2\2\2\u041f"+
		"\u041d\3\2\2\2\u0420\u0421\7?\2\2\u0421\u0422\5\u00a4S\2\u0422\u0423\7"+
		"Y\2\2\u0423\u0424\5\u00c8e\2\u0424\u0429\3\2\2\2\u0425\u0426\5\u00f2z"+
		"\2\u0426\u0427\5J&\2\u0427\u0429\3\2\2\2\u0428\u0420\3\2\2\2\u0428\u0425"+
		"\3\2\2\2\u0429\u00a3\3\2\2\2\u042a\u042b\t\6\2\2\u042b\u00a5\3\2\2\2\u042c"+
		"\u042d\t\7\2\2\u042d\u00a7\3\2\2\2\u042e\u0430\5\f\7\2\u042f\u042e\3\2"+
		"\2\2\u0430\u0433\3\2\2\2\u0431\u042f\3\2\2\2\u0431\u0432\3\2\2\2\u0432"+
		"\u0437\3\2\2\2\u0433\u0431\3\2\2\2\u0434\u0438\5\20\t\2\u0435\u0438\5"+
		" \21\2\u0436\u0438\5\u0094K\2\u0437\u0434\3\2\2\2\u0437\u0435\3\2\2\2"+
		"\u0437\u0436\3\2\2\2\u0438\u00a9\3\2\2\2\u0439\u04ab\5\u009eP\2\u043a"+
		"\u043b\7\4\2\2\u043b\u043e\5\u00c8e\2\u043c\u043d\7_\2\2\u043d\u043f\5"+
		"\u00c8e\2\u043e\u043c\3\2\2\2\u043e\u043f\3\2\2\2\u043f\u0440\3\2\2\2"+
		"\u0440\u0441\7V\2\2\u0441\u04ab\3\2\2\2\u0442\u0443\7\30\2\2\u0443\u0444"+
		"\5\u00c2b\2\u0444\u0447\5\u00aaV\2\u0445\u0446\7\21\2\2\u0446\u0448\5"+
		"\u00aaV\2\u0447\u0445\3\2\2\2\u0447\u0448\3\2\2\2\u0448\u04ab\3\2\2\2"+
		"\u0449\u044a\7\27\2\2\u044a\u044b\7P\2\2\u044b\u044c\5\u00bc_\2\u044c"+
		"\u044d\7Q\2\2\u044d\u044e\5\u00aaV\2\u044e\u04ab\3\2\2\2\u044f\u0450\7"+
		"\64\2\2\u0450\u0451\5\u00c2b\2\u0451\u0452\5\u00aaV\2\u0452\u04ab\3\2"+
		"\2\2\u0453\u0454\7\17\2\2\u0454\u0455\5\u00aaV\2\u0455\u0456\7\64\2\2"+
		"\u0456\u0457\5\u00c2b\2\u0457\u0458\7V\2\2\u0458\u04ab\3\2\2\2\u0459\u045a"+
		"\7\61\2\2\u045a\u0464\5\u009eP\2\u045b\u045d\5\u00acW\2\u045c\u045b\3"+
		"\2\2\2\u045d\u045e\3\2\2\2\u045e\u045c\3\2\2\2\u045e\u045f\3\2\2\2\u045f"+
		"\u0461\3\2\2\2\u0460\u0462\5\u00b0Y\2\u0461\u0460\3\2\2\2\u0461\u0462"+
		"\3\2\2\2\u0462\u0465\3\2\2\2\u0463\u0465\5\u00b0Y\2\u0464\u045c\3\2\2"+
		"\2\u0464\u0463\3\2\2\2\u0465\u04ab\3\2\2\2\u0466\u0467\7\61\2\2\u0467"+
		"\u0468\5\u00b2Z\2\u0468\u046c\5\u009eP\2\u0469\u046b\5\u00acW\2\u046a"+
		"\u0469\3\2\2\2\u046b\u046e\3\2\2\2\u046c\u046a\3\2\2\2\u046c\u046d\3\2"+
		"\2\2\u046d\u0470\3\2\2\2\u046e\u046c\3\2\2\2\u046f\u0471\5\u00b0Y\2\u0470"+
		"\u046f\3\2\2\2\u0470\u0471\3\2\2\2\u0471\u04ab\3\2\2\2\u0472\u0473\7+"+
		"\2\2\u0473\u0474\5\u00c2b\2\u0474\u0478\7R\2\2\u0475\u0477\5\u00b8]\2"+
		"\u0476\u0475\3\2\2\2\u0477\u047a\3\2\2\2\u0478\u0476\3\2\2\2\u0478\u0479"+
		"\3\2\2\2\u0479\u047e\3\2\2\2\u047a\u0478\3\2\2\2\u047b\u047d\5\u00ba^"+
		"\2\u047c\u047b\3\2\2\2\u047d\u0480\3\2\2\2\u047e\u047c\3\2\2\2\u047e\u047f"+
		"\3\2\2\2\u047f\u0481\3\2\2\2\u0480\u047e\3\2\2\2\u0481\u0482\7S\2\2\u0482"+
		"\u04ab\3\2\2\2\u0483\u0484\7,\2\2\u0484\u0485\5\u00c2b\2\u0485\u0486\5"+
		"\u009eP\2\u0486\u04ab\3\2\2\2\u0487\u0489\7&\2\2\u0488\u048a\5\u00c8e"+
		"\2\u0489\u0488\3\2\2\2\u0489\u048a\3\2\2\2\u048a\u048b\3\2\2\2\u048b\u04ab"+
		"\7V\2\2\u048c\u048d\7.\2\2\u048d\u048e\5\u00c8e\2\u048e\u048f\7V\2\2\u048f"+
		"\u04ab\3\2\2\2\u0490\u0492\7\6\2\2\u0491\u0493\5\u00a4S\2\u0492\u0491"+
		"\3\2\2\2\u0492\u0493\3\2\2\2\u0493\u0494\3\2\2\2\u0494\u04ab\7V\2\2\u0495"+
		"\u0497\7\r\2\2\u0496\u0498\5\u00a4S\2\u0497\u0496\3\2\2\2\u0497\u0498"+
		"\3\2\2\2\u0498\u0499\3\2\2\2\u0499\u04ab\7V\2\2\u049a\u049b\7@\2\2\u049b"+
		"\u049c\5\u00c8e\2\u049c\u049d\7V\2\2\u049d\u04ab\3\2\2\2\u049e\u04ab\7"+
		"V\2\2\u049f\u04a0\5\u00c8e\2\u04a0\u04a1\7V\2\2\u04a1\u04ab\3\2\2\2\u04a2"+
		"\u04a4\5\u00d4k\2\u04a3\u04a5\7V\2\2\u04a4\u04a3\3\2\2\2\u04a4\u04a5\3"+
		"\2\2\2\u04a5\u04ab\3\2\2\2\u04a6\u04a7\5\u00a4S\2\u04a7\u04a8\7_\2\2\u04a8"+
		"\u04a9\5\u00aaV\2\u04a9\u04ab\3\2\2\2\u04aa\u0439\3\2\2\2\u04aa\u043a"+
		"\3\2\2\2\u04aa\u0442\3\2\2\2\u04aa\u0449\3\2\2\2\u04aa\u044f\3\2\2\2\u04aa"+
		"\u0453\3\2\2\2\u04aa\u0459\3\2\2\2\u04aa\u0466\3\2\2\2\u04aa\u0472\3\2"+
		"\2\2\u04aa\u0483\3\2\2\2\u04aa\u0487\3\2\2\2\u04aa\u048c\3\2\2\2\u04aa"+
		"\u0490\3\2\2\2\u04aa\u0495\3\2\2\2\u04aa\u049a\3\2\2\2\u04aa\u049e\3\2"+
		"\2\2\u04aa\u049f\3\2\2\2\u04aa\u04a2\3\2\2\2\u04aa\u04a6\3\2\2\2\u04ab"+
		"\u00ab\3\2\2\2\u04ac\u04ad\7\t\2\2\u04ad\u04b1\7P\2\2\u04ae\u04b0\5\16"+
		"\b\2\u04af\u04ae\3\2\2\2\u04b0\u04b3\3\2\2\2\u04b1\u04af\3\2\2\2\u04b1"+
		"\u04b2\3\2\2\2\u04b2\u04b4\3\2\2\2\u04b3\u04b1\3\2\2\2\u04b4\u04b5\5\u00ae"+
		"X\2\u04b5\u04b6\5\u00a4S\2\u04b6\u04b7\7Q\2\2\u04b7\u04b8\5\u009eP\2\u04b8"+
		"\u00ad\3\2\2\2\u04b9\u04be\5h\65\2\u04ba\u04bb\7m\2\2\u04bb\u04bd\5h\65"+
		"\2\u04bc\u04ba\3\2\2\2\u04bd\u04c0\3\2\2\2\u04be\u04bc\3\2\2\2\u04be\u04bf"+
		"\3\2\2\2\u04bf\u00af\3\2\2\2\u04c0\u04be\3\2\2\2\u04c1\u04c2\7\25\2\2"+
		"\u04c2\u04c3\5\u009eP\2\u04c3\u00b1\3\2\2\2\u04c4\u04c5\7P\2\2\u04c5\u04c7"+
		"\5\u00b4[\2\u04c6\u04c8\7V\2\2\u04c7\u04c6\3\2\2\2\u04c7\u04c8\3\2\2\2"+
		"\u04c8\u04c9\3\2\2\2\u04c9\u04ca\7Q\2\2\u04ca\u00b3\3\2\2\2\u04cb\u04d0"+
		"\5\u00b6\\\2\u04cc\u04cd\7V\2\2\u04cd\u04cf\5\u00b6\\\2\u04ce\u04cc\3"+
		"\2\2\2\u04cf\u04d2\3\2\2\2\u04d0\u04ce\3\2\2\2\u04d0\u04d1\3\2\2\2\u04d1"+
		"\u00b5\3\2\2\2\u04d2\u04d0\3\2\2\2\u04d3\u04d5\5\16\b\2\u04d4\u04d3\3"+
		"\2\2\2\u04d5\u04d8\3\2\2\2\u04d6\u04d4\3\2\2\2\u04d6\u04d7\3\2\2\2\u04d7"+
		"\u04de\3\2\2\2\u04d8\u04d6\3\2\2\2\u04d9\u04da\5T+\2\u04da\u04db\5N(\2"+
		"\u04db\u04df\3\2\2\2\u04dc\u04dd\7?\2\2\u04dd\u04df\5\u00a4S\2\u04de\u04d9"+
		"\3\2\2\2\u04de\u04dc\3\2\2\2\u04df\u04e0\3\2\2\2\u04e0\u04e1\7Y\2\2\u04e1"+
		"\u04e2\5\u00c8e\2\u04e2\u04e5\3\2\2\2\u04e3\u04e5\5\u00a4S\2\u04e4\u04d6"+
		"\3\2\2\2\u04e4\u04e3\3\2\2\2\u04e5\u00b7\3\2\2\2\u04e6\u04e8\5\u00ba^"+
		"\2\u04e7\u04e6\3\2\2\2\u04e8\u04e9\3\2\2\2\u04e9\u04e7\3\2\2\2\u04e9\u04ea"+
		"\3\2\2\2\u04ea\u04ec\3\2\2\2\u04eb\u04ed\5\u00a0Q\2\u04ec\u04eb\3\2\2"+
		"\2\u04ed\u04ee\3\2\2\2\u04ee\u04ec\3\2\2\2\u04ee\u04ef\3\2\2\2\u04ef\u00b9"+
		"\3\2\2\2\u04f0\u04f6\7\b\2\2\u04f1\u04f7\5\u00c8e\2\u04f2\u04f7\7\u0083"+
		"\2\2\u04f3\u04f4\5\u00f2z\2\u04f4\u04f5\5\u00a4S\2\u04f5\u04f7\3\2\2\2"+
		"\u04f6\u04f1\3\2\2\2\u04f6\u04f2\3\2\2\2\u04f6\u04f3\3\2\2\2\u04f7\u04f8"+
		"\3\2\2\2\u04f8\u04fc\7_\2\2\u04f9\u04fa\7\16\2\2\u04fa\u04fc\7_\2\2\u04fb"+
		"\u04f0\3\2\2\2\u04fb\u04f9\3\2\2\2\u04fc\u00bb\3\2\2\2\u04fd\u050a\5\u00c0"+
		"a\2\u04fe\u0500\5\u00be`\2\u04ff\u04fe\3\2\2\2\u04ff\u0500\3\2\2\2\u0500"+
		"\u0501\3\2\2\2\u0501\u0503\7V\2\2\u0502\u0504\5\u00c8e\2\u0503\u0502\3"+
		"\2\2\2\u0503\u0504\3\2\2\2\u0504\u0505\3\2\2\2\u0505\u0507\7V\2\2\u0506"+
		"\u0508\5\u00c4c\2\u0507\u0506\3\2\2\2\u0507\u0508\3\2\2\2\u0508\u050a"+
		"\3\2\2\2\u0509\u04fd\3\2\2\2\u0509\u04ff\3\2\2\2\u050a\u00bd\3\2\2\2\u050b"+
		"\u050e\5\u00a2R\2\u050c\u050e\5\u00c4c\2\u050d\u050b\3\2\2\2\u050d\u050c"+
		"\3\2\2\2\u050e\u00bf\3\2\2\2\u050f\u0511\5\16\b\2\u0510\u050f\3\2\2\2"+
		"\u0511\u0514\3\2\2\2\u0512\u0510\3\2\2\2\u0512\u0513\3\2\2\2\u0513\u0517"+
		"\3\2\2\2\u0514\u0512\3\2\2\2\u0515\u0518\5\u00f2z\2\u0516\u0518\7?\2\2"+
		"\u0517\u0515\3\2\2\2\u0517\u0516\3\2\2\2\u0518\u0519\3\2\2\2\u0519\u051a"+
		"\5N(\2\u051a\u051b\7_\2\2\u051b\u051c\5\u00c8e\2\u051c\u00c1\3\2\2\2\u051d"+
		"\u051e\7P\2\2\u051e\u051f\5\u00c8e\2\u051f\u0520\7Q\2\2\u0520\u00c3\3"+
		"\2\2\2\u0521\u0526\5\u00c8e\2\u0522\u0523\7W\2\2\u0523\u0525\5\u00c8e"+
		"\2\u0524\u0522\3\2\2\2\u0525\u0528\3\2\2\2\u0526\u0524\3\2\2\2\u0526\u0527"+
		"\3\2\2\2\u0527\u00c5\3\2\2\2\u0528\u0526\3\2\2\2\u0529\u052a\5\u00a4S"+
		"\2\u052a\u052c\7P\2\2\u052b\u052d\5\u00c4c\2\u052c\u052b\3\2\2\2\u052c"+
		"\u052d\3\2\2\2\u052d\u052e\3\2\2\2\u052e\u052f\7Q\2\2\u052f\u053d\3\2"+
		"\2\2\u0530\u0531\7-\2\2\u0531\u0533\7P\2\2\u0532\u0534\5\u00c4c\2\u0533"+
		"\u0532\3\2\2\2\u0533\u0534\3\2\2\2\u0534\u0535\3\2\2\2\u0535\u053d\7Q"+
		"\2\2\u0536\u0537\7*\2\2\u0537\u0539\7P\2\2\u0538\u053a\5\u00c4c\2\u0539"+
		"\u0538\3\2\2\2\u0539\u053a\3\2\2\2\u053a\u053b\3\2\2\2\u053b\u053d\7Q"+
		"\2\2\u053c\u0529\3\2\2\2\u053c\u0530\3\2\2\2\u053c\u0536\3\2\2\2\u053d"+
		"\u00c7\3\2\2\2\u053e\u053f\be\1\2\u053f\u056c\5\u00d2j\2\u0540\u056c\5"+
		"\u00c6d\2\u0541\u0542\7!\2\2\u0542\u056c\5\u00dep\2\u0543\u0547\7P\2\2"+
		"\u0544\u0546\5r:\2\u0545\u0544\3\2\2\2\u0546\u0549\3\2\2\2\u0547\u0545"+
		"\3\2\2\2\u0547\u0548\3\2\2\2\u0548\u054a\3\2\2\2\u0549\u0547\3\2\2\2\u054a"+
		"\u054f\5\u00f2z\2\u054b\u054c\7l\2\2\u054c\u054e\5\u00f2z\2\u054d\u054b"+
		"\3\2\2\2\u054e\u0551\3\2\2\2\u054f\u054d\3\2\2\2\u054f\u0550\3\2\2\2\u0550"+
		"\u0552\3\2\2\2\u0551\u054f\3\2\2\2\u0552\u0553\7Q\2\2\u0553\u0554\5\u00c8"+
		"e\30\u0554\u056c\3\2\2\2\u0555\u0556\t\b\2\2\u0556\u056c\5\u00c8e\26\u0557"+
		"\u0558\t\t\2\2\u0558\u056c\5\u00c8e\25\u0559\u056c\5\u00ccg\2\u055a\u056c"+
		"\5\u00d4k\2\u055b\u055c\5\u00f2z\2\u055c\u0562\7|\2\2\u055d\u055f\5\u00f6"+
		"|\2\u055e\u055d\3\2\2\2\u055e\u055f\3\2\2\2\u055f\u0560\3\2\2\2\u0560"+
		"\u0563\5\u00a4S\2\u0561\u0563\7!\2\2\u0562\u055e\3\2\2\2\u0562\u0561\3"+
		"\2\2\2\u0563\u056c\3\2\2\2\u0564\u0565\5\u00dco\2\u0565\u0567\7|\2\2\u0566"+
		"\u0568\5\u00f6|\2\u0567\u0566\3\2\2\2\u0567\u0568\3\2\2\2\u0568\u0569"+
		"\3\2\2\2\u0569\u056a\7!\2\2\u056a\u056c\3\2\2\2\u056b\u053e\3\2\2\2\u056b"+
		"\u0540\3\2\2\2\u056b\u0541\3\2\2\2\u056b\u0543\3\2\2\2\u056b\u0555\3\2"+
		"\2\2\u056b\u0557\3\2\2\2\u056b\u0559\3\2\2\2\u056b\u055a\3\2\2\2\u056b"+
		"\u055b\3\2\2\2\u056b\u0564\3\2\2\2\u056c\u05c0\3\2\2\2\u056d\u056e\f\24"+
		"\2\2\u056e\u056f\t\n\2\2\u056f\u05bf\5\u00c8e\25\u0570\u0571\f\23\2\2"+
		"\u0571\u0572\t\13\2\2\u0572\u05bf\5\u00c8e\24\u0573\u057b\f\22\2\2\u0574"+
		"\u0575\7[\2\2\u0575\u057c\7[\2\2\u0576\u0577\7Z\2\2\u0577\u0578\7Z\2\2"+
		"\u0578\u057c\7Z\2\2\u0579\u057a\7Z\2\2\u057a\u057c\7Z\2\2\u057b\u0574"+
		"\3\2\2\2\u057b\u0576\3\2\2\2\u057b\u0579\3\2\2\2\u057c\u057d\3\2\2\2\u057d"+
		"\u05bf\5\u00c8e\23\u057e\u057f\f\21\2\2\u057f\u0580\t\f\2\2\u0580\u05bf"+
		"\5\u00c8e\22\u0581\u0582\f\17\2\2\u0582\u0583\t\r\2\2\u0583\u05bf\5\u00c8"+
		"e\20\u0584\u0585\f\16\2\2\u0585\u0586\7l\2\2\u0586\u05bf\5\u00c8e\17\u0587"+
		"\u0588\f\r\2\2\u0588\u0589\7n\2\2\u0589\u05bf\5\u00c8e\16\u058a\u058b"+
		"\f\f\2\2\u058b\u058c\7m\2\2\u058c\u05bf\5\u00c8e\r\u058d\u058e\f\13\2"+
		"\2\u058e\u058f\7d\2\2\u058f\u05bf\5\u00c8e\f\u0590\u0591\f\n\2\2\u0591"+
		"\u0592\7e\2\2\u0592\u05bf\5\u00c8e\13\u0593\u0594\f\t\2\2\u0594\u0595"+
		"\7^\2\2\u0595\u0596\5\u00c8e\2\u0596\u0597\7_\2\2\u0597\u0598\5\u00c8"+
		"e\t\u0598\u05bf\3\2\2\2\u0599\u059a\f\b\2\2\u059a\u059b\t\16\2\2\u059b"+
		"\u05bf\5\u00c8e\b\u059c\u059d\f\34\2\2\u059d\u05a9\7X\2\2\u059e\u05aa"+
		"\5\u00a4S\2\u059f\u05aa\5\u00c6d\2\u05a0\u05aa\7-\2\2\u05a1\u05a3\7!\2"+
		"\2\u05a2\u05a4\5\u00eex\2\u05a3\u05a2\3\2\2\2\u05a3\u05a4\3\2\2\2\u05a4"+
		"\u05a5\3\2\2\2\u05a5\u05aa\5\u00e2r\2\u05a6\u05a7\7*\2\2\u05a7\u05aa\5"+
		"\u00f8}\2\u05a8\u05aa\5\u00e8u\2\u05a9\u059e\3\2\2\2\u05a9\u059f\3\2\2"+
		"\2\u05a9\u05a0\3\2\2\2\u05a9\u05a1\3\2\2\2\u05a9\u05a6\3\2\2\2\u05a9\u05a8"+
		"\3\2\2\2\u05aa\u05bf\3\2\2\2\u05ab\u05ac\f\33\2\2\u05ac\u05ad\7T\2\2\u05ad"+
		"\u05ae\5\u00c8e\2\u05ae\u05af\7U\2\2\u05af\u05bf\3\2\2\2\u05b0\u05b1\f"+
		"\27\2\2\u05b1\u05bf\t\17\2\2\u05b2\u05b3\f\20\2\2\u05b3\u05b6\7\34\2\2"+
		"\u05b4\u05b7\5\u00f2z\2\u05b5\u05b7\5\u00caf\2\u05b6\u05b4\3\2\2\2\u05b6"+
		"\u05b5\3\2\2\2\u05b7\u05bf\3\2\2\2\u05b8\u05b9\f\5\2\2\u05b9\u05bb\7|"+
		"\2\2\u05ba\u05bc\5\u00f6|\2\u05bb\u05ba\3\2\2\2\u05bb\u05bc\3\2\2\2\u05bc"+
		"\u05bd\3\2\2\2\u05bd\u05bf\5\u00a4S\2\u05be\u056d\3\2\2\2\u05be\u0570"+
		"\3\2\2\2\u05be\u0573\3\2\2\2\u05be\u057e\3\2\2\2\u05be\u0581\3\2\2\2\u05be"+
		"\u0584\3\2\2\2\u05be\u0587\3\2\2\2\u05be\u058a\3\2\2\2\u05be\u058d\3\2"+
		"\2\2\u05be\u0590\3\2\2\2\u05be\u0593\3\2\2\2\u05be\u0599\3\2\2\2\u05be"+
		"\u059c\3\2\2\2\u05be\u05ab\3\2\2\2\u05be\u05b0\3\2\2\2\u05be\u05b2\3\2"+
		"\2\2\u05be\u05b8\3\2\2\2\u05bf\u05c2\3\2\2\2\u05c0\u05be\3\2\2\2\u05c0"+
		"\u05c1\3\2\2\2\u05c1\u00c9\3\2\2\2\u05c2\u05c0\3\2\2\2\u05c3\u05c5\5\16"+
		"\b\2\u05c4\u05c3\3\2\2\2\u05c5\u05c8\3\2\2\2\u05c6\u05c4\3\2\2\2\u05c6"+
		"\u05c7\3\2\2\2\u05c7\u05c9\3\2\2\2\u05c8\u05c6\3\2\2\2\u05c9\u05cd\5\u00f2"+
		"z\2\u05ca\u05cc\5r:\2\u05cb\u05ca\3\2\2\2\u05cc\u05cf\3\2\2\2\u05cd\u05cb"+
		"\3\2\2\2\u05cd\u05ce\3\2\2\2\u05ce\u05d0\3\2\2\2\u05cf\u05cd\3\2\2\2\u05d0"+
		"\u05d1\5\u00a4S\2\u05d1\u00cb\3\2\2\2\u05d2\u05d3\5\u00ceh\2\u05d3\u05d4"+
		"\7{\2\2\u05d4\u05d5\5\u00d0i\2\u05d5\u00cd\3\2\2\2\u05d6\u05ed\5\u00a4"+
		"S\2\u05d7\u05d9\7P\2\2\u05d8\u05da\5^\60\2\u05d9\u05d8\3\2\2\2\u05d9\u05da"+
		"\3\2\2\2\u05da\u05db\3\2\2\2\u05db\u05ed\7Q\2\2\u05dc\u05dd\7P\2\2\u05dd"+
		"\u05e2\5\u00a4S\2\u05de\u05df\7W\2\2\u05df\u05e1\5\u00a4S\2\u05e0\u05de"+
		"\3\2\2\2\u05e1\u05e4\3\2\2\2\u05e2\u05e0\3\2\2\2\u05e2\u05e3\3\2\2\2\u05e3"+
		"\u05e5\3\2\2\2\u05e4\u05e2\3\2\2\2\u05e5\u05e6\7Q\2\2\u05e6\u05ed\3\2"+
		"\2\2\u05e7\u05e9\7P\2\2\u05e8\u05ea\5d\63\2\u05e9\u05e8\3\2\2\2\u05e9"+
		"\u05ea\3\2\2\2\u05ea\u05eb\3\2\2\2\u05eb\u05ed\7Q\2\2\u05ec\u05d6\3\2"+
		"\2\2\u05ec\u05d7\3\2\2\2\u05ec\u05dc\3\2\2\2\u05ec\u05e7\3\2\2\2\u05ed"+
		"\u00cf\3\2\2\2\u05ee\u05f1\5\u00c8e\2\u05ef\u05f1\5\u009eP\2\u05f0\u05ee"+
		"\3\2\2\2\u05f0\u05ef\3\2\2\2\u05f1\u00d1\3\2\2\2\u05f2\u05f3\7P\2\2\u05f3"+
		"\u05f4\5\u00c8e\2\u05f4\u05f5\7Q\2\2\u05f5\u0605\3\2\2\2\u05f6\u0605\7"+
		"-\2\2\u05f7\u0605\7*\2\2\u05f8\u0605\5j\66\2\u05f9\u0605\5\u00a4S\2\u05fa"+
		"\u05fb\5.\30\2\u05fb\u05fc\7X\2\2\u05fc\u05fd\7\13\2\2\u05fd\u0605\3\2"+
		"\2\2\u05fe\u0602\5\u00eex\2\u05ff\u0603\5\u00fa~\2\u0600\u0601\7-\2\2"+
		"\u0601\u0603\5\u00fc\177\2\u0602\u05ff\3\2\2\2\u0602\u0600\3\2\2\2\u0603"+
		"\u0605\3\2\2\2\u0604\u05f2\3\2\2\2\u0604\u05f6\3\2\2\2\u0604\u05f7\3\2"+
		"\2\2\u0604\u05f8\3\2\2\2\u0604\u05f9\3\2\2\2\u0604\u05fa\3\2\2\2\u0604"+
		"\u05fe\3\2\2\2\u0605\u00d3\3\2\2\2\u0606\u0607\7+\2\2\u0607\u0608\5\u00c2"+
		"b\2\u0608\u060c\7R\2\2\u0609\u060b\5\u00d6l\2\u060a\u0609\3\2\2\2\u060b"+
		"\u060e\3\2\2\2\u060c\u060a\3\2\2\2\u060c\u060d\3\2\2\2\u060d\u060f\3\2"+
		"\2\2\u060e\u060c\3\2\2\2\u060f\u0610\7S\2\2\u0610\u00d5\3\2\2\2\u0611"+
		"\u0615\7\b\2\2\u0612\u0616\5\u00c4c\2\u0613\u0616\7O\2\2\u0614\u0616\5"+
		"\u00d8m\2\u0615\u0612\3\2\2\2\u0615\u0613\3\2\2\2\u0615\u0614\3\2\2\2"+
		"\u0616\u0617\3\2\2\2\u0617\u0618\t\20\2\2\u0618\u061d\5\u00dan\2\u0619"+
		"\u061a\7\16\2\2\u061a\u061b\t\20\2\2\u061b\u061d\5\u00dan\2\u061c\u0611"+
		"\3\2\2\2\u061c\u0619\3\2\2\2\u061d\u00d7\3\2\2\2\u061e\u061f\bm\1\2\u061f"+
		"\u0620\7P\2\2\u0620\u0621\5\u00d8m\2\u0621\u0622\7Q\2\2\u0622\u0639\3"+
		"\2\2\2\u0623\u0625\5\16\b\2\u0624\u0623\3\2\2\2\u0625\u0628\3\2\2\2\u0626"+
		"\u0624\3\2\2\2\u0626\u0627\3\2\2\2\u0627\u0629\3\2\2\2\u0628\u0626\3\2"+
		"\2\2\u0629\u062d\5\u00f2z\2\u062a\u062c\5r:\2\u062b\u062a\3\2\2\2\u062c"+
		"\u062f\3\2\2\2\u062d\u062b\3\2\2\2\u062d\u062e\3\2\2\2\u062e\u0630\3\2"+
		"\2\2\u062f\u062d\3\2\2\2\u0630\u0635\5\u00a4S\2\u0631\u0632\7d\2\2\u0632"+
		"\u0634\5\u00c8e\2\u0633\u0631\3\2\2\2\u0634\u0637\3\2\2\2\u0635\u0633"+
		"\3\2\2\2\u0635\u0636\3\2\2\2\u0636\u0639\3\2\2\2\u0637\u0635\3\2\2\2\u0638"+
		"\u061e\3\2\2\2\u0638\u0626\3\2\2\2\u0639\u063f\3\2\2\2\u063a\u063b\f\3"+
		"\2\2\u063b\u063c\7d\2\2\u063c\u063e\5\u00c8e\2\u063d\u063a\3\2\2\2\u063e"+
		"\u0641\3\2\2\2\u063f\u063d\3\2\2\2\u063f\u0640\3\2\2\2\u0640\u00d9\3\2"+
		"\2\2\u0641\u063f\3\2\2\2\u0642\u064a\5\u009eP\2\u0643\u0645\5\u00a0Q\2"+
		"\u0644\u0643\3\2\2\2\u0645\u0648\3\2\2\2\u0646\u0644\3\2\2\2\u0646\u0647"+
		"\3\2\2\2\u0647\u064a\3\2\2\2\u0648\u0646\3\2\2\2\u0649\u0642\3\2\2\2\u0649"+
		"\u0646\3\2\2\2\u064a\u00db\3\2\2\2\u064b\u064c\5T+\2\u064c\u064d\7X\2"+
		"\2\u064d\u064f\3\2\2\2\u064e\u064b\3\2\2\2\u064e\u064f\3\2\2\2\u064f\u0653"+
		"\3\2\2\2\u0650\u0652\5r:\2\u0651\u0650\3\2\2\2\u0652\u0655\3\2\2\2\u0653"+
		"\u0651\3\2\2\2\u0653\u0654\3\2\2\2\u0654\u0656\3\2\2\2\u0655\u0653\3\2"+
		"\2\2\u0656\u0658\5\u00a4S\2\u0657\u0659\5\u00f6|\2\u0658\u0657\3\2\2\2"+
		"\u0658\u0659\3\2\2\2\u0659\u00dd\3\2\2\2\u065a\u065b\5\u00eex\2\u065b"+
		"\u065c\5\u00e0q\2\u065c\u065d\5\u00e6t\2\u065d\u0664\3\2\2\2\u065e\u0661"+
		"\5\u00e0q\2\u065f\u0662\5\u00e4s\2\u0660\u0662\5\u00e6t\2\u0661\u065f"+
		"\3\2\2\2\u0661\u0660\3\2\2\2\u0662\u0664\3\2\2\2\u0663\u065a\3\2\2\2\u0663"+
		"\u065e\3\2\2\2\u0664\u00df\3\2\2\2\u0665\u0667\5\u00a4S\2\u0666\u0668"+
		"\5\u00eav\2\u0667\u0666\3\2\2\2\u0667\u0668\3\2\2\2\u0668\u0670\3\2\2"+
		"\2\u0669\u066a\7X\2\2\u066a\u066c\5\u00a4S\2\u066b\u066d\5\u00eav\2\u066c"+
		"\u066b\3\2\2\2\u066c\u066d\3\2\2\2\u066d\u066f\3\2\2\2\u066e\u0669\3\2"+
		"\2\2\u066f\u0672\3\2\2\2\u0670\u066e\3\2\2\2\u0670\u0671\3\2\2\2\u0671"+
		"\u0675\3\2\2\2\u0672\u0670\3\2\2\2\u0673\u0675\5\u00f4{\2\u0674\u0665"+
		"\3\2\2\2\u0674\u0673\3\2\2\2\u0675\u00e1\3\2\2\2\u0676\u0678\5\u00a4S"+
		"\2\u0677\u0679\5\u00ecw\2\u0678\u0677\3\2\2\2\u0678\u0679\3\2\2\2\u0679"+
		"\u067a\3\2\2\2\u067a\u067b\5\u00e6t\2\u067b\u00e3\3\2\2\2\u067c\u0698"+
		"\7T\2\2\u067d\u0682\7U\2\2\u067e\u067f\7T\2\2\u067f\u0681\7U\2\2\u0680"+
		"\u067e\3\2\2\2\u0681\u0684\3\2\2\2\u0682\u0680\3\2\2\2\u0682\u0683\3\2"+
		"\2\2\u0683\u0685\3\2\2\2\u0684\u0682\3\2\2\2\u0685\u0699\5R*\2\u0686\u0687"+
		"\5\u00c8e\2\u0687\u068e\7U\2\2\u0688\u0689\7T\2\2\u0689\u068a\5\u00c8"+
		"e\2\u068a\u068b\7U\2\2\u068b\u068d\3\2\2\2\u068c\u0688\3\2\2\2\u068d\u0690"+
		"\3\2\2\2\u068e\u068c\3\2\2\2\u068e\u068f\3\2\2\2\u068f\u0695\3\2\2\2\u0690"+
		"\u068e\3\2\2\2\u0691\u0692\7T\2\2\u0692\u0694\7U\2\2\u0693\u0691\3\2\2"+
		"\2\u0694\u0697\3\2\2\2\u0695\u0693\3\2\2\2\u0695\u0696\3\2\2\2\u0696\u0699"+
		"\3\2\2\2\u0697\u0695\3\2\2\2\u0698\u067d\3\2\2\2\u0698\u0686\3\2\2\2\u0699"+
		"\u00e5\3\2\2\2\u069a\u069c\5\u00fc\177\2\u069b\u069d\5\"\22\2\u069c\u069b"+
		"\3\2\2\2\u069c\u069d\3\2\2\2\u069d\u00e7\3\2\2\2\u069e\u069f\5\u00eex"+
		"\2\u069f\u06a0\5\u00fa~\2\u06a0\u00e9\3\2\2\2\u06a1\u06a2\7[\2\2\u06a2"+
		"\u06a5\7Z\2\2\u06a3\u06a5\5\u00f6|\2\u06a4\u06a1\3\2\2\2\u06a4\u06a3\3"+
		"\2\2\2\u06a5\u00eb\3\2\2\2\u06a6\u06a7\7[\2\2\u06a7\u06aa\7Z\2\2\u06a8"+
		"\u06aa\5\u00eex\2\u06a9\u06a6\3\2\2\2\u06a9\u06a8\3\2\2\2\u06aa\u00ed"+
		"\3\2\2\2\u06ab\u06ac\7[\2\2\u06ac\u06ad\5\u00f0y\2\u06ad\u06ae\7Z\2\2"+
		"\u06ae\u00ef\3\2\2\2\u06af\u06b4\5\u00f2z\2\u06b0\u06b1\7W\2\2\u06b1\u06b3"+
		"\5\u00f2z\2\u06b2\u06b0\3\2\2\2\u06b3\u06b6\3\2\2\2\u06b4\u06b2\3\2\2"+
		"\2\u06b4\u06b5\3\2\2\2\u06b5\u00f1\3\2\2\2\u06b6\u06b4\3\2\2\2\u06b7\u06b9"+
		"\5r:\2\u06b8\u06b7\3\2\2\2\u06b9\u06bc\3\2\2\2\u06ba\u06b8\3\2\2\2\u06ba"+
		"\u06bb\3\2\2\2\u06bb\u06bf\3\2\2\2\u06bc\u06ba\3\2\2\2\u06bd\u06c0\5T"+
		"+\2\u06be\u06c0\5\u00f4{\2\u06bf\u06bd\3\2\2\2\u06bf\u06be\3\2\2\2\u06c0"+
		"\u06cb\3\2\2\2\u06c1\u06c3\5r:\2\u06c2\u06c1\3\2\2\2\u06c3\u06c6\3\2\2"+
		"\2\u06c4\u06c2\3\2\2\2\u06c4\u06c5\3\2\2\2\u06c5\u06c7\3\2\2\2\u06c6\u06c4"+
		"\3\2\2\2\u06c7\u06c8\7T\2\2\u06c8\u06ca\7U\2\2\u06c9\u06c4\3\2\2\2\u06ca"+
		"\u06cd\3\2\2\2\u06cb\u06c9\3\2\2\2\u06cb\u06cc\3\2\2\2\u06cc\u00f3\3\2"+
		"\2\2\u06cd\u06cb\3\2\2\2\u06ce\u06cf\t\21\2\2\u06cf\u00f5\3\2\2\2\u06d0"+
		"\u06d1\7[\2\2\u06d1\u06d6\5V,\2\u06d2\u06d3\7W\2\2\u06d3\u06d5\5V,\2\u06d4"+
		"\u06d2\3\2\2\2\u06d5\u06d8\3\2\2\2\u06d6\u06d4\3\2\2\2\u06d6\u06d7\3\2"+
		"\2\2\u06d7\u06d9\3\2\2\2\u06d8\u06d6\3\2\2\2\u06d9\u06da\7Z\2\2\u06da"+
		"\u00f7\3\2\2\2\u06db\u06e5\5\u00fc\177\2\u06dc\u06de\7X\2\2\u06dd\u06df"+
		"\5\u00f6|\2\u06de\u06dd\3\2\2\2\u06de\u06df\3\2\2\2\u06df\u06e0\3\2\2"+
		"\2\u06e0\u06e2\5\u00a4S\2\u06e1\u06e3\5\u00fc\177\2\u06e2\u06e1\3\2\2"+
		"\2\u06e2\u06e3\3\2\2\2\u06e3\u06e5\3\2\2\2\u06e4\u06db\3\2\2\2\u06e4\u06dc"+
		"\3\2\2\2\u06e5\u00f9\3\2\2\2\u06e6\u06e7\7*\2\2\u06e7\u06ec\5\u00f8}\2"+
		"\u06e8\u06e9\5\u00a4S\2\u06e9\u06ea\5\u00fc\177\2\u06ea\u06ec\3\2\2\2"+
		"\u06eb\u06e6\3\2\2\2\u06eb\u06e8\3\2\2\2\u06ec\u00fb\3\2\2\2\u06ed\u06ef"+
		"\7P\2\2\u06ee\u06f0\5\u00c4c\2\u06ef\u06ee\3\2\2\2\u06ef\u06f0\3\2\2\2"+
		"\u06f0\u06f1\3\2\2\2\u06f1\u06f2\7Q\2\2\u06f2\u00fd\3\2\2\2\u00df\u00ff"+
		"\u0104\u010a\u0110\u0115\u011e\u0123\u012a\u0132\u0135\u013c\u0148\u014c"+
		"\u0151\u0155\u0159\u015d\u0167\u016f\u0177\u017b\u0182\u0189\u018d\u0190"+
		"\u0193\u019c\u01a2\u01a7\u01aa\u01b0\u01b6\u01ba\u01be\u01c6\u01cf\u01d6"+
		"\u01dc\u01e0\u01ec\u01f5\u01fa\u0200\u0204\u0210\u0217\u0224\u0229\u0233"+
		"\u023b\u0245\u024e\u0259\u025e\u0267\u0271\u0276\u027f\u0285\u028c\u0291"+
		"\u0299\u029d\u029f\u02a5\u02ab\u02b0\u02b6\u02bc\u02be\u02c5\u02ca\u02cf"+
		"\u02d2\u02d4\u02de\u02e8\u02ed\u02f0\u02f5\u02fe\u0305\u0310\u0316\u0321"+
		"\u032b\u0336\u033f\u0344\u0347\u034e\u0358\u0360\u0363\u0366\u0373\u037b"+
		"\u0380\u0388\u038c\u0390\u0394\u0398\u039a\u039e\u03a4\u03ac\u03b6\u03bf"+
		"\u03c9\u03d1\u03df\u03e6\u03eb\u03f1\u03fa\u0403\u0405\u040e\u0418\u041d"+
		"\u0428\u0431\u0437\u043e\u0447\u045e\u0461\u0464\u046c\u0470\u0478\u047e"+
		"\u0489\u0492\u0497\u04a4\u04aa\u04b1\u04be\u04c7\u04d0\u04d6\u04de\u04e4"+
		"\u04e9\u04ee\u04f6\u04fb\u04ff\u0503\u0507\u0509\u050d\u0512\u0517\u0526"+
		"\u052c\u0533\u0539\u053c\u0547\u054f\u055e\u0562\u0567\u056b\u057b\u05a3"+
		"\u05a9\u05b6\u05bb\u05be\u05c0\u05c6\u05cd\u05d9\u05e2\u05e9\u05ec\u05f0"+
		"\u0602\u0604\u060c\u0615\u061c\u0626\u062d\u0635\u0638\u063f\u0646\u0649"+
		"\u064e\u0653\u0658\u0661\u0663\u0667\u066c\u0670\u0674\u0678\u0682\u068e"+
		"\u0695\u0698\u069c\u06a4\u06a9\u06b4\u06ba\u06bf\u06c4\u06cb\u06d6\u06de"+
		"\u06e2\u06e4\u06eb\u06ef";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}