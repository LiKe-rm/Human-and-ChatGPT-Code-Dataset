package com.hust.model;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;
import org.antlr.v4.runtime.tree.TerminalNode;

import com.hust.antlr.cpp.CPP14Lexer;
import com.hust.antlr.cpp.CPP14Parser;
import com.hust.antlr.cpp.CPP14ParserBaseListener;
import com.hust.antlr.cpp.CPP14Parser.ConditionalExpressionContext;
import com.hust.antlr.cpp.CPP14Parser.FunctionDefinitionContext;
import com.hust.antlr.cpp.CPP14Parser.IterationStatementContext;
import com.hust.antlr.cpp.CPP14Parser.LiteralContext;
import com.hust.antlr.cpp.CPP14Parser.ParameterDeclarationContext;
import com.hust.antlr.cpp.CPP14Parser.SelectionStatementContext;

public class CppExtract extends CPP14ParserBaseListener implements Extract {
    // function based features
    public List<Function> functionList;
    private List<Variable> functionParams;

    // code style
    public int ternaryOperatorNumber;
    public int controlStructureNumber;
    public int literalNumber;
    public int nestingDepth;
    private int nestingLocalDepth;
    public List<Integer> branchingNumberList;

    // AST based features
    public List<Integer> typeNodeDepth;
    public List<Integer> leafNodeDepth;
    public Map<String, Double> typeNodeFrequency;
    public Map<String, Double> leafNodeFrequency;
    public Map<String, Double> keywordFrequency;

    public CppExtract() {
        // function based features
        functionList = new ArrayList<Function>();
        functionParams = new ArrayList<>();

        // code style
        ternaryOperatorNumber = 0;
        controlStructureNumber = 0;
        literalNumber = 0;
        nestingDepth = 0;
        nestingLocalDepth = 0;
        branchingNumberList = new ArrayList<Integer>();

        // AST based features
        typeNodeDepth = new ArrayList<Integer>();
        leafNodeDepth = new ArrayList<Integer>();
        typeNodeFrequency = new HashMap<String, Double>();
        leafNodeFrequency = new HashMap<String, Double>();
        keywordFrequency = new HashMap<String, Double>();
    }

    @Override
    public void enterSelectionStatement(SelectionStatementContext ctx) {
        controlStructureNumber += 1;
        nestingLocalDepth += 1;
        if (ctx.Else() != null) {
            controlStructureNumber += 1;
        }
        // record current nesting depth and refresh nestingDepth
        if (nestingLocalDepth > nestingDepth) {
            nestingDepth = nestingLocalDepth;
        }
        // record the number of subtree of control or loop statement
        branchingNumberList.add(ctx.getChildCount());
        super.enterSelectionStatement(ctx);
    }

    @Override
    public void enterIterationStatement(IterationStatementContext ctx) {
        controlStructureNumber += 1;
        // record current nesting depth and refresh nestingDepth
        nestingLocalDepth += 1;
        if (nestingLocalDepth > nestingDepth) {
            nestingDepth = nestingLocalDepth;
        }
        // record the number of subtree of control or loop statement
        branchingNumberList.add(ctx.getChildCount());
        super.enterIterationStatement(ctx);
    }

    @Override
    public void enterConditionalExpression(ConditionalExpressionContext ctx) {
        if (ctx.Question() != null) {
            ternaryOperatorNumber += 1;
        }
        super.enterConditionalExpression(ctx);
    }

    @Override
    public void enterLiteral(LiteralContext ctx) {
        literalNumber += 1;
        super.enterLiteral(ctx);
    }

    @Override
    public void enterFunctionDefinition(FunctionDefinitionContext ctx) {
        functionParams.clear();
        super.enterFunctionDefinition(ctx);
    }

    @Override
    public void exitFunctionDefinition(FunctionDefinitionContext ctx) {
        String functionName = "";
        String functionBody = ctx.getText();
        int functionStartLine = ctx.start.getLine();
        int functionStopLine = ctx.stop.getLine();
        functionList.add(new Function(functionName, functionBody, functionStartLine, functionStopLine, functionParams));
        super.exitFunctionDefinition(ctx);
    }

    @Override
    public void enterParameterDeclaration(ParameterDeclarationContext ctx) {
        String paramName = ctx.declarator() != null ? ctx.declarator().getText() : "";
        String paramType = ctx.declSpecifierSeq().getText();
        int paramLine = ctx.start.getLine();
        int paramColumn = ctx.start.getCharPositionInLine();
        functionParams.add(new Variable(paramName, paramType, paramLine, paramColumn));
        super.enterParameterDeclaration(ctx);
    }

    @Override
    public void enterEveryRule(ParserRuleContext ctx) {
        // calculate node depth, including type node and leaf node
        typeNodeDepth.add(ctx.depth());
        if (ctx.children != null) {
            for (ParseTree child : ctx.children) {
                if (child instanceof TerminalNode) {
                    leafNodeDepth.add(ctx.depth() + 1);
                }
            }
        }

        // calculate type node frequency
        String type = String.valueOf(ctx.getRuleIndex());
        if (typeNodeFrequency.containsKey(type)) {
            typeNodeFrequency.put(type, typeNodeFrequency.get(type) + 1);
        } else {
            typeNodeFrequency.put(type, Double.valueOf(1));
        }
        super.enterEveryRule(ctx);
    }

    @Override
    public void visitTerminal(TerminalNode node) {
        int type = node.getSymbol().getType();
        String text = node.getText();

        // calculate java keyword frequency
        if (type >= CPP14Lexer.Alignas && type <= CPP14Lexer.While) {
            if (keywordFrequency.containsKey(text)) {
                keywordFrequency.put(text, keywordFrequency.get(text) + 1);
            } else {
                keywordFrequency.put(text, Double.valueOf(1));
            }
        }else if (type != CPP14Lexer.StringLiteral && type != CPP14Lexer.Identifier) {
            if (leafNodeFrequency.containsKey(text)) {
                leafNodeFrequency.put(text, leafNodeFrequency.get(text) + 1);
            } else {
                leafNodeFrequency.put(text, Double.valueOf(1));
            }
        }

        // calculate leaf node frequency


        super.visitTerminal(node);
    }

    public static void main(String[] args) {
        CppExtract cppExtract = new CppExtract();
        try {
            CharStream charStream = CharStreams.fromFileName("D:\\Code\\dataset\\test.cpp");
            CPP14Lexer cppLexer = new CPP14Lexer(charStream);
            CommonTokenStream tokens = new CommonTokenStream(cppLexer);
            CPP14Parser cppParser = new CPP14Parser(tokens);
            ParseTreeWalker walker = new ParseTreeWalker();
            walker.walk(cppExtract, cppParser.translationUnit());
        } catch (Exception e) {
            System.out.println(e);
        }
        System.out.println("ee");
    }

    @Override
    public List<Integer> getBranchingNumberList() {
        return branchingNumberList;
    }

    @Override
    public List<Function> getFunctionList() {
        return functionList;
    }

    @Override
    public List<Integer> getLeafNodeDepth() {
        return leafNodeDepth;
    }

    @Override
    public int getLiteralNumber() {
        return literalNumber;
    }

    @Override
    public int getTernaryOperatorNumber() {
        return ternaryOperatorNumber;
    }

    @Override
    public int getNestingDepth() {
        return nestingDepth;
    }

    @Override
    public int getControlStructureNumber() {
        return controlStructureNumber;
    }

    @Override
    public Map<String, Double> getKeywordFrequency() {
        return keywordFrequency;
    }

    @Override
    public Map<String, Double> getLeafNodeFrequency() {
        return leafNodeFrequency;
    }

    @Override
    public List<Integer> getTypeNodeDepth() {
        return typeNodeDepth;
    }

    @Override
    public Map<String, Double> getTypeNodeFrequency() {
        return typeNodeFrequency;
    }
}
