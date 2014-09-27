/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 12 "ripper.y"


#ifndef PARSER_DEBUG
#define PARSER_DEBUG 0
#endif
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYSTACK_USE_ALLOCA 0

#include "ruby/ruby.h"
#include "ruby/st.h"
#include "ruby/encoding.h"
#include "internal.h"
#include "node.h"
#include "parse.h"
#include "symbol.h"
#include "regenc.h"
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include "probes.h"

#define YYMALLOC(size)		rb_parser_malloc(parser, (size))
#define YYREALLOC(ptr, size)	rb_parser_realloc(parser, (ptr), (size))
#define YYCALLOC(nelem, size)	rb_parser_calloc(parser, (nelem), (size))
#define YYFREE(ptr)		rb_parser_free(parser, (ptr))
#undef malloc
#undef realloc
#undef calloc
#undef free
#define malloc	YYMALLOC
#define realloc	YYREALLOC
#define calloc	YYCALLOC
#define free	YYFREE

enum lex_state_bits {
    EXPR_BEG_bit,		/* ignore newline, +/- is a sign. */
    EXPR_END_bit,		/* newline significant, +/- is an operator. */
    EXPR_ENDARG_bit,		/* ditto, and unbound braces. */
    EXPR_ENDFN_bit,		/* ditto, and unbound braces. */
    EXPR_ARG_bit,		/* newline significant, +/- is an operator. */
    EXPR_CMDARG_bit,		/* newline significant, +/- is an operator. */
    EXPR_MID_bit,		/* newline significant, +/- is an operator. */
    EXPR_FNAME_bit,		/* ignore newline, no reserved words. */
    EXPR_DOT_bit,		/* right after `.' or `::', no reserved words. */
    EXPR_CLASS_bit,		/* immediate after `class', no here document. */
    EXPR_VALUE_bit,		/* alike EXPR_BEG but label is disallowed. */
    EXPR_LABELARG_bit,		/* ignore significant, +/- is a sign. */
    EXPR_MAX_STATE
};
/* examine combinations */
enum lex_state_e {
#define DEF_EXPR(n) EXPR_##n = (1 << EXPR_##n##_bit)
    DEF_EXPR(BEG),
    DEF_EXPR(END),
    DEF_EXPR(ENDARG),
    DEF_EXPR(ENDFN),
    DEF_EXPR(ARG),
    DEF_EXPR(CMDARG),
    DEF_EXPR(MID),
    DEF_EXPR(FNAME),
    DEF_EXPR(DOT),
    DEF_EXPR(CLASS),
    DEF_EXPR(VALUE),
    DEF_EXPR(LABELARG),
    EXPR_BEG_ANY  =  (EXPR_BEG | EXPR_VALUE | EXPR_MID | EXPR_CLASS | EXPR_LABELARG),
    EXPR_ARG_ANY  =  (EXPR_ARG | EXPR_CMDARG),
    EXPR_END_ANY  =  (EXPR_END | EXPR_ENDARG | EXPR_ENDFN)
};
#define IS_lex_state_for(x, ls)	((x) & (ls))
#define IS_lex_state(ls)	IS_lex_state_for(lex_state, (ls))

#if PARSER_DEBUG
static const char *lex_state_name(enum lex_state_e state);
#endif

typedef VALUE stack_type;

# define BITSTACK_PUSH(stack, n)	((stack) = ((stack)<<1)|((n)&1))
# define BITSTACK_POP(stack)	((stack) = (stack) >> 1)
# define BITSTACK_LEXPOP(stack)	((stack) = ((stack) >> 1) | ((stack) & 1))
# define BITSTACK_SET_P(stack)	((stack)&1)

#define COND_PUSH(n)	BITSTACK_PUSH(cond_stack, (n))
#define COND_POP()	BITSTACK_POP(cond_stack)
#define COND_LEXPOP()	BITSTACK_LEXPOP(cond_stack)
#define COND_P()	BITSTACK_SET_P(cond_stack)

#define CMDARG_PUSH(n)	BITSTACK_PUSH(cmdarg_stack, (n))
#define CMDARG_POP()	BITSTACK_POP(cmdarg_stack)
#define CMDARG_LEXPOP()	BITSTACK_LEXPOP(cmdarg_stack)
#define CMDARG_P()	BITSTACK_SET_P(cmdarg_stack)

struct vtable {
    ID *tbl;
    int pos;
    int capa;
    struct vtable *prev;
};

struct local_vars {
    struct vtable *args;
    struct vtable *vars;
    struct vtable *used;
    struct local_vars *prev;
    stack_type cmdargs;
};

#define DVARS_INHERIT ((void*)1)
#define DVARS_TOPSCOPE NULL
#define DVARS_SPECIAL_P(tbl) (!POINTER_P(tbl))
#define POINTER_P(val) ((VALUE)(val) & ~(VALUE)3)

static int
vtable_size(const struct vtable *tbl)
{
    if (POINTER_P(tbl)) {
        return tbl->pos;
    }
    else {
        return 0;
    }
}

#define VTBL_DEBUG 0

static struct vtable *
vtable_alloc(struct vtable *prev)
{
    struct vtable *tbl = ALLOC(struct vtable);
    tbl->pos = 0;
    tbl->capa = 8;
    tbl->tbl = ALLOC_N(ID, tbl->capa);
    tbl->prev = prev;
    if (VTBL_DEBUG) printf("vtable_alloc: %p\n", (void *)tbl);
    return tbl;
}

static void
vtable_free(struct vtable *tbl)
{
    if (VTBL_DEBUG)printf("vtable_free: %p\n", (void *)tbl);
    if (POINTER_P(tbl)) {
        if (tbl->tbl) {
            xfree(tbl->tbl);
        }
        xfree(tbl);
    }
}

static void
vtable_add(struct vtable *tbl, ID id)
{
    if (!POINTER_P(tbl)) {
        rb_bug("vtable_add: vtable is not allocated (%p)", (void *)tbl);
    }
    if (VTBL_DEBUG) printf("vtable_add: %p, %"PRIsVALUE"\n", (void *)tbl, rb_id2str(id));

    if (tbl->pos == tbl->capa) {
        tbl->capa = tbl->capa * 2;
        REALLOC_N(tbl->tbl, ID, tbl->capa);
    }
    tbl->tbl[tbl->pos++] = id;
}

static int
vtable_included(const struct vtable * tbl, ID id)
{
    int i;

    if (POINTER_P(tbl)) {
        for (i = 0; i < tbl->pos; i++) {
            if (tbl->tbl[i] == id) {
                return i+1;
            }
        }
    }
    return 0;
}


#ifndef RIPPER
typedef struct token_info {
    const char *token;
    int linenum;
    int column;
    int nonspc;
    struct token_info *next;
} token_info;
#endif

/*
    Structure of Lexer Buffer:

 lex_pbeg      tokp         lex_p        lex_pend
    |           |              |            |
    |-----------+--------------+------------|
                |<------------>|
                     token
*/
struct parser_params {
    NODE *heap;

    YYSTYPE *parser_yylval;
    VALUE eofp;

    NODE *parser_lex_strterm;
    stack_type parser_cond_stack;
    stack_type parser_cmdarg_stack;
    enum lex_state_e parser_lex_state;
    int parser_class_nest;
    int parser_paren_nest;
    int parser_lpar_beg;
    int parser_in_single;
    int parser_in_def;
    int parser_brace_nest;
    int parser_compile_for_eval;
    VALUE parser_cur_mid;
    int parser_in_kwarg;
    int parser_in_defined;
    char *parser_tokenbuf;
    int parser_tokidx;
    int parser_toksiz;
    int parser_tokline;
    int is_ripper; /* bool, seems unused */
    VALUE parser_lex_input;
    VALUE parser_lex_lastline;
    VALUE parser_lex_nextline;
    const char *parser_lex_pbeg;
    const char *parser_lex_p;
    const char *parser_lex_pend;
    int parser_heredoc_end;
    int parser_command_start;
    NODE *parser_deferred_nodes;
    long parser_lex_gets_ptr;
    VALUE (*parser_lex_gets)(struct parser_params*,VALUE);
    struct local_vars *parser_lvtbl;
    int parser_ruby__end__seen;
    int line_count;
    int has_shebang;
    int parser_ruby_sourceline;	/* current line no. */
    char *parser_ruby_sourcefile; /* current source file */
    VALUE parser_ruby_sourcefile_string;
    rb_encoding *enc;

    int parser_yydebug;

    int last_cr_line;

#ifndef RIPPER
    /* Ruby core only */
    NODE *parser_eval_tree_begin;
    NODE *parser_eval_tree;
    VALUE debug_lines;
    VALUE coverage;
    int nerr;

    int parser_token_info_enabled;
    token_info *parser_token_info;
#else
    /* Ripper only */
    const char *tokp;
    VALUE delayed;
    int delayed_line;
    int delayed_col;

    VALUE value;
    VALUE result;
    VALUE parsing_thread;
    int toplevel_p;
#endif
};

#ifdef RIPPER
#define intern_cstr(n,l,en) rb_intern3(n,l,en)
#else
#define intern_cstr(n,l,en) rb_intern3(n,l,en)
#endif

#define STR_NEW(p,n) rb_enc_str_new((p),(n),current_enc)
#define STR_NEW0() rb_enc_str_new(0,0,current_enc)
#define STR_NEW2(p) rb_enc_str_new((p),strlen(p),current_enc)
#define STR_NEW3(p,n,e,func) parser_str_new((p),(n),(e),(func),current_enc)
#define TOK_INTERN() intern_cstr(tok(), toklen(), current_enc)

static int parser_yyerror(struct parser_params*, const char*);
#define yyerror(msg) parser_yyerror(parser, (msg))

#define lex_strterm		(parser->parser_lex_strterm)
#define lex_state		(parser->parser_lex_state)
#define cond_stack		(parser->parser_cond_stack)
#define cmdarg_stack		(parser->parser_cmdarg_stack)
#define class_nest		(parser->parser_class_nest)
#define paren_nest		(parser->parser_paren_nest)
#define lpar_beg		(parser->parser_lpar_beg)
#define brace_nest		(parser->parser_brace_nest)
#define in_single		(parser->parser_in_single)
#define in_def			(parser->parser_in_def)
#define compile_for_eval	(parser->parser_compile_for_eval)
#define cur_mid			(parser->parser_cur_mid)
#define in_defined		(parser->parser_in_defined)
#define tokenbuf		(parser->parser_tokenbuf)
#define tokidx			(parser->parser_tokidx)
#define toksiz			(parser->parser_toksiz)
#define tokline			(parser->parser_tokline)
#define lex_input		(parser->parser_lex_input)
#define lex_lastline		(parser->parser_lex_lastline)
#define lex_nextline		(parser->parser_lex_nextline)
#define lex_pbeg		(parser->parser_lex_pbeg)
#define lex_p			(parser->parser_lex_p)
#define lex_pend		(parser->parser_lex_pend)
#define heredoc_end		(parser->parser_heredoc_end)
#define command_start		(parser->parser_command_start)
#define deferred_nodes		(parser->parser_deferred_nodes)
#define lex_gets_ptr		(parser->parser_lex_gets_ptr)
#define lex_gets		(parser->parser_lex_gets)
#define lvtbl			(parser->parser_lvtbl)
#define ruby__end__seen		(parser->parser_ruby__end__seen)
#define ruby_sourceline		(parser->parser_ruby_sourceline)
#define ruby_sourcefile		(parser->parser_ruby_sourcefile)
#define ruby_sourcefile_string	(parser->parser_ruby_sourcefile_string)
#define current_enc		(parser->enc)
#define yydebug			(parser->parser_yydebug)
#ifdef RIPPER
#else
#define ruby_eval_tree		(parser->parser_eval_tree)
#define ruby_eval_tree_begin	(parser->parser_eval_tree_begin)
#define ruby_debug_lines	(parser->debug_lines)
#define ruby_coverage		(parser->coverage)
#endif

#if YYPURE
static int yylex(void*, void*);
#else
static int yylex(void*);
#endif

#ifndef RIPPER
#define yyparse ruby_yyparse

static NODE* node_newnode(struct parser_params *, enum node_type, VALUE, VALUE, VALUE);
#define rb_node_newnode(type, a1, a2, a3) node_newnode(parser, (type), (a1), (a2), (a3))

static NODE *cond_gen(struct parser_params*,NODE*);
#define cond(node) cond_gen(parser, (node))
static NODE *logop_gen(struct parser_params*,enum node_type,NODE*,NODE*);
#define logop(type,node1,node2) logop_gen(parser, (type), (node1), (node2))

static NODE *newline_node(NODE*);
static void fixpos(NODE*,NODE*);

static int value_expr_gen(struct parser_params*,NODE*);
static void void_expr_gen(struct parser_params*,NODE*);
static NODE *remove_begin(NODE*);
static NODE *remove_begin_all(NODE*);
#define value_expr(node) value_expr_gen(parser, (node) = remove_begin(node))
#define void_expr0(node) void_expr_gen(parser, (node))
#define void_expr(node) void_expr0((node) = remove_begin(node))
static void void_stmts_gen(struct parser_params*,NODE*);
#define void_stmts(node) void_stmts_gen(parser, (node))
static void reduce_nodes_gen(struct parser_params*,NODE**);
#define reduce_nodes(n) reduce_nodes_gen(parser,(n))
static void block_dup_check_gen(struct parser_params*,NODE*,NODE*);
#define block_dup_check(n1,n2) block_dup_check_gen(parser,(n1),(n2))

static NODE *block_append_gen(struct parser_params*,NODE*,NODE*);
#define block_append(h,t) block_append_gen(parser,(h),(t))
static NODE *list_append_gen(struct parser_params*,NODE*,NODE*);
#define list_append(l,i) list_append_gen(parser,(l),(i))
static NODE *list_concat_gen(struct parser_params*,NODE*,NODE*);
#define list_concat(h,t) list_concat_gen(parser,(h),(t))
static NODE *arg_append_gen(struct parser_params*,NODE*,NODE*);
#define arg_append(h,t) arg_append_gen(parser,(h),(t))
static NODE *arg_concat_gen(struct parser_params*,NODE*,NODE*);
#define arg_concat(h,t) arg_concat_gen(parser,(h),(t))
static NODE *literal_concat_gen(struct parser_params*,NODE*,NODE*);
#define literal_concat(h,t) literal_concat_gen(parser,(h),(t))
static int literal_concat0(struct parser_params *, VALUE, VALUE);
static NODE *new_evstr_gen(struct parser_params*,NODE*);
#define new_evstr(n) new_evstr_gen(parser,(n))
static NODE *evstr2dstr_gen(struct parser_params*,NODE*);
#define evstr2dstr(n) evstr2dstr_gen(parser,(n))
static NODE *splat_array(NODE*);

static NODE *call_bin_op_gen(struct parser_params*,NODE*,ID,NODE*);
#define call_bin_op(recv,id,arg1) call_bin_op_gen(parser, (recv),(id),(arg1))
static NODE *call_uni_op_gen(struct parser_params*,NODE*,ID);
#define call_uni_op(recv,id) call_uni_op_gen(parser, (recv),(id))

static NODE *new_args_gen(struct parser_params*,NODE*,NODE*,ID,NODE*,NODE*);
#define new_args(f,o,r,p,t) new_args_gen(parser, (f),(o),(r),(p),(t))
static NODE *new_args_tail_gen(struct parser_params*,NODE*,ID,ID);
#define new_args_tail(k,kr,b) new_args_tail_gen(parser, (k),(kr),(b))

static VALUE negate_lit(VALUE);
static NODE *ret_args_gen(struct parser_params*,NODE*);
#define ret_args(node) ret_args_gen(parser, (node))
static NODE *arg_blk_pass(NODE*,NODE*);
static NODE *new_yield_gen(struct parser_params*,NODE*);
#define new_yield(node) new_yield_gen(parser, (node))
static NODE *dsym_node_gen(struct parser_params*,NODE*);
#define dsym_node(node) dsym_node_gen(parser, (node))

static NODE *gettable_gen(struct parser_params*,ID);
#define gettable(id) gettable_gen(parser,(id))
static NODE *assignable_gen(struct parser_params*,ID,NODE*);
#define assignable(id,node) assignable_gen(parser, (id), (node))

static NODE *aryset_gen(struct parser_params*,NODE*,NODE*);
#define aryset(node1,node2) aryset_gen(parser, (node1), (node2))
static NODE *attrset_gen(struct parser_params*,NODE*,ID);
#define attrset(node,id) attrset_gen(parser, (node), (id))

static void rb_backref_error_gen(struct parser_params*,NODE*);
#define rb_backref_error(n) rb_backref_error_gen(parser,(n))
static NODE *node_assign_gen(struct parser_params*,NODE*,NODE*);
#define node_assign(node1, node2) node_assign_gen(parser, (node1), (node2))

static NODE *new_op_assign_gen(struct parser_params *parser, NODE *lhs, ID op, NODE *rhs);
static NODE *new_attr_op_assign_gen(struct parser_params *parser, NODE *lhs, ID attr, ID op, NODE *rhs);
#define new_attr_op_assign(lhs, type, attr, op, rhs) new_attr_op_assign_gen(parser, (lhs), (attr), (op), (rhs))
static NODE *new_const_op_assign_gen(struct parser_params *parser, NODE *lhs, ID op, NODE *rhs);
#define new_const_op_assign(lhs, op, rhs) new_const_op_assign_gen(parser, (lhs), (op), (rhs))

#define new_defined(expr) NEW_DEFINED(remove_begin_all(expr))

static NODE *match_op_gen(struct parser_params*,NODE*,NODE*);
#define match_op(node1,node2) match_op_gen(parser, (node1), (node2))

static ID  *local_tbl_gen(struct parser_params*);
#define local_tbl() local_tbl_gen(parser)

static void fixup_nodes(NODE **);

static VALUE reg_compile_gen(struct parser_params*, VALUE, int);
#define reg_compile(str,options) reg_compile_gen(parser, (str), (options))
static void reg_fragment_setenc_gen(struct parser_params*, VALUE, int);
#define reg_fragment_setenc(str,options) reg_fragment_setenc_gen(parser, (str), (options))
static int reg_fragment_check_gen(struct parser_params*, VALUE, int);
#define reg_fragment_check(str,options) reg_fragment_check_gen(parser, (str), (options))
static NODE *reg_named_capture_assign_gen(struct parser_params* parser, VALUE regexp, NODE *match);
#define reg_named_capture_assign(regexp,match) reg_named_capture_assign_gen(parser,(regexp),(match))

#define get_id(id) (id)
#define get_value(val) (val)
#else
#define value_expr(node) ((void)(node))
#define remove_begin(node) (node)
#define rb_dvar_defined(id) 0
#define rb_local_defined(id) 0
static ID ripper_get_id(VALUE);
#define get_id(id) ripper_get_id(id)
static VALUE ripper_get_value(VALUE);
#define get_value(val) ripper_get_value(val)
static VALUE assignable_gen(struct parser_params*,VALUE);
#define assignable(lhs,node) assignable_gen(parser, (lhs))
static int id_is_var_gen(struct parser_params *parser, ID id);
#define id_is_var(id) id_is_var_gen(parser, (id))

#define node_assign(node1, node2) dispatch2(assign, (node1), (node2))

static VALUE new_op_assign_gen(struct parser_params *parser, VALUE lhs, VALUE op, VALUE rhs);
static VALUE new_attr_op_assign_gen(struct parser_params *parser, VALUE lhs, VALUE type, VALUE attr, VALUE op, VALUE rhs);
#define new_attr_op_assign(lhs, type, attr, op, rhs) new_attr_op_assign_gen(parser, (lhs), (type), (attr), (op), (rhs))

#endif /* !RIPPER */

#define new_op_assign(lhs, op, rhs) new_op_assign_gen(parser, (lhs), (op), (rhs))

static ID formal_argument_gen(struct parser_params*, ID);
#define formal_argument(id) formal_argument_gen(parser, (id))
static ID shadowing_lvar_gen(struct parser_params*,ID);
#define shadowing_lvar(name) shadowing_lvar_gen(parser, (name))
static void new_bv_gen(struct parser_params*,ID);
#define new_bv(id) new_bv_gen(parser, (id))

static void local_push_gen(struct parser_params*,int);
#define local_push(top) local_push_gen(parser,(top))
static void local_pop_gen(struct parser_params*);
#define local_pop() local_pop_gen(parser)
static void local_var_gen(struct parser_params*, ID);
#define local_var(id) local_var_gen(parser, (id))
static void arg_var_gen(struct parser_params*, ID);
#define arg_var(id) arg_var_gen(parser, (id))
static int  local_id_gen(struct parser_params*, ID);
#define local_id(id) local_id_gen(parser, (id))
static ID   internal_id_gen(struct parser_params*);
#define internal_id() internal_id_gen(parser)

static const struct vtable *dyna_push_gen(struct parser_params *);
#define dyna_push() dyna_push_gen(parser)
static void dyna_pop_gen(struct parser_params*, const struct vtable *);
#define dyna_pop(node) dyna_pop_gen(parser, (node))
static int dyna_in_block_gen(struct parser_params*);
#define dyna_in_block() dyna_in_block_gen(parser)
#define dyna_var(id) local_var(id)
static int dvar_defined_gen(struct parser_params*,ID,int);
#define dvar_defined(id) dvar_defined_gen(parser, (id), 0)
#define dvar_defined_get(id) dvar_defined_gen(parser, (id), 1)
static int dvar_curr_gen(struct parser_params*,ID);
#define dvar_curr(id) dvar_curr_gen(parser, (id))

static int lvar_defined_gen(struct parser_params*, ID);
#define lvar_defined(id) lvar_defined_gen(parser, (id))

#define RE_OPTION_ONCE (1<<16)
#define RE_OPTION_ENCODING_SHIFT 8
#define RE_OPTION_ENCODING(e) (((e)&0xff)<<RE_OPTION_ENCODING_SHIFT)
#define RE_OPTION_ENCODING_IDX(o) (((o)>>RE_OPTION_ENCODING_SHIFT)&0xff)
#define RE_OPTION_ENCODING_NONE(o) ((o)&RE_OPTION_ARG_ENCODING_NONE)
#define RE_OPTION_MASK  0xff
#define RE_OPTION_ARG_ENCODING_NONE 32

#define NODE_STRTERM NODE_ZARRAY	/* nothing to gc */
#define NODE_HEREDOC NODE_ARRAY 	/* 1, 3 to gc */
#define SIGN_EXTEND(x,n) (((1<<(n)-1)^((x)&~(~0<<(n))))-(1<<(n)-1))
#define nd_func u1.id
#if SIZEOF_SHORT == 2
#define nd_term(node) ((signed short)(node)->u2.id)
#else
#define nd_term(node) SIGN_EXTEND((node)->u2.id, CHAR_BIT*2)
#endif
#define nd_paren(node) (char)((node)->u2.id >> CHAR_BIT*2)
#define nd_nest u3.cnt

/****** Ripper *******/

#ifdef RIPPER
#define RIPPER_VERSION "0.1.0"

#include "eventids1.c"
#include "eventids2.c"

static VALUE ripper_dispatch0(struct parser_params*,ID);
static VALUE ripper_dispatch1(struct parser_params*,ID,VALUE);
static VALUE ripper_dispatch2(struct parser_params*,ID,VALUE,VALUE);
static VALUE ripper_dispatch3(struct parser_params*,ID,VALUE,VALUE,VALUE);
static VALUE ripper_dispatch4(struct parser_params*,ID,VALUE,VALUE,VALUE,VALUE);
static VALUE ripper_dispatch5(struct parser_params*,ID,VALUE,VALUE,VALUE,VALUE,VALUE);
static VALUE ripper_dispatch7(struct parser_params*,ID,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE);

#define dispatch0(n)            ripper_dispatch0(parser, TOKEN_PASTE(ripper_id_, n))
#define dispatch1(n,a)          ripper_dispatch1(parser, TOKEN_PASTE(ripper_id_, n), (a))
#define dispatch2(n,a,b)        ripper_dispatch2(parser, TOKEN_PASTE(ripper_id_, n), (a), (b))
#define dispatch3(n,a,b,c)      ripper_dispatch3(parser, TOKEN_PASTE(ripper_id_, n), (a), (b), (c))
#define dispatch4(n,a,b,c,d)    ripper_dispatch4(parser, TOKEN_PASTE(ripper_id_, n), (a), (b), (c), (d))
#define dispatch5(n,a,b,c,d,e)  ripper_dispatch5(parser, TOKEN_PASTE(ripper_id_, n), (a), (b), (c), (d), (e))
#define dispatch7(n,a,b,c,d,e,f,g) ripper_dispatch7(parser, TOKEN_PASTE(ripper_id_, n), (a), (b), (c), (d), (e), (f), (g))

#define yyparse ripper_yyparse

#define ripper_intern(s) ID2SYM(rb_intern(s))
static VALUE ripper_id2sym(ID);
#ifdef __GNUC__
#define ripper_id2sym(id) ((id) < 256 && rb_ispunct(id) ? \
			   ID2SYM(id) : ripper_id2sym(id))
#endif

#define arg_new() dispatch0(args_new)
#define arg_add(l,a) dispatch2(args_add, (l), (a))
#define arg_add_star(l,a) dispatch2(args_add_star, (l), (a))
#define arg_add_block(l,b) dispatch2(args_add_block, (l), (b))
#define arg_add_optblock(l,b) ((b)==Qundef? (l) : dispatch2(args_add_block, (l), (b)))
#define bare_assoc(v) dispatch1(bare_assoc_hash, (v))
#define arg_add_assocs(l,b) arg_add((l), bare_assoc(b))

#define args2mrhs(a) dispatch1(mrhs_new_from_args, (a))
#define mrhs_new() dispatch0(mrhs_new)
#define mrhs_add(l,a) dispatch2(mrhs_add, (l), (a))
#define mrhs_add_star(l,a) dispatch2(mrhs_add_star, (l), (a))

#define mlhs_new() dispatch0(mlhs_new)
#define mlhs_add(l,a) dispatch2(mlhs_add, (l), (a))
#define mlhs_add_star(l,a) dispatch2(mlhs_add_star, (l), (a))

#define params_new(pars, opts, rest, pars2, kws, kwrest, blk) \
        dispatch7(params, (pars), (opts), (rest), (pars2), (kws), (kwrest), (blk))

#define blockvar_new(p,v) dispatch2(block_var, (p), (v))
#define blockvar_add_star(l,a) dispatch2(block_var_add_star, (l), (a))
#define blockvar_add_block(l,a) dispatch2(block_var_add_block, (l), (a))

#define method_optarg(m,a) ((a)==Qundef ? (m) : dispatch2(method_add_arg,(m),(a)))
#define method_arg(m,a) dispatch2(method_add_arg,(m),(a))
#define method_add_block(m,b) dispatch2(method_add_block, (m), (b))

#define escape_Qundef(x) ((x)==Qundef ? Qnil : (x))

static inline VALUE
new_args_gen(struct parser_params *parser, VALUE f, VALUE o, VALUE r, VALUE p, VALUE tail)
{
    NODE *t = (NODE *)tail;
    VALUE k = t->u1.value, kr = t->u2.value, b = t->u3.value;
    return params_new(f, o, r, p, k, kr, escape_Qundef(b));
}
#define new_args(f,o,r,p,t) new_args_gen(parser, (f),(o),(r),(p),(t))

static inline VALUE
new_args_tail_gen(struct parser_params *parser, VALUE k, VALUE kr, VALUE b)
{
    return (VALUE)rb_node_newnode(NODE_MEMO, k, kr, b);
}
#define new_args_tail(k,kr,b) new_args_tail_gen(parser, (k),(kr),(b))

#define new_defined(expr) dispatch1(defined, (expr))

#define FIXME 0

#endif /* RIPPER */

#ifndef RIPPER
# define Qnone 0
# define ifndef_ripper(x) (x)
#else
# define Qnone Qnil
# define ifndef_ripper(x)
#endif

#ifndef RIPPER
# define rb_warn0(fmt)    rb_compile_warn(ruby_sourcefile, ruby_sourceline, (fmt))
# define rb_warnI(fmt,a)  rb_compile_warn(ruby_sourcefile, ruby_sourceline, (fmt), (a))
# define rb_warnS(fmt,a)  rb_compile_warn(ruby_sourcefile, ruby_sourceline, (fmt), (a))
# define rb_warn4S(file,line,fmt,a)  rb_compile_warn((file), (line), (fmt), (a))
# define rb_warn4V(file,line,fmt,a)  rb_compile_warn((file), (line), (fmt), (a))
# define rb_warning0(fmt) rb_compile_warning(ruby_sourcefile, ruby_sourceline, (fmt))
# define rb_warningS(fmt,a) rb_compile_warning(ruby_sourcefile, ruby_sourceline, (fmt), (a))
# define rb_warningV(fmt,a) rb_compile_warning(ruby_sourcefile, ruby_sourceline, (fmt), (a))
#else
# define rb_warn0(fmt)    ripper_warn0(parser, (fmt))
# define rb_warnI(fmt,a)  ripper_warnI(parser, (fmt), (a))
# define rb_warnS(fmt,a)  ripper_warnS(parser, (fmt), (a))
# define rb_warnV(fmt,a)  ripper_warnV(parser, (fmt), (a))
# define rb_warn4S(file,line,fmt,a)  ripper_warnS(parser, (fmt), (a))
# define rb_warn4V(file,line,fmt,a)  ripper_warnV(parser, (fmt), (a))
# define rb_warning0(fmt) ripper_warning0(parser, (fmt))
# define rb_warningS(fmt,a) ripper_warningS(parser, (fmt), (a))
# define rb_warningV(fmt,a) ripper_warningV(parser, (fmt), (a))
static void ripper_warn0(struct parser_params*, const char*);
static void ripper_warnI(struct parser_params*, const char*, int);
#if 0				/* not in use right now */
static void ripper_warnS(struct parser_params*, const char*, const char*);
#endif
static void ripper_warnV(struct parser_params*, const char*, VALUE);
static void ripper_warning0(struct parser_params*, const char*);
static void ripper_warningS(struct parser_params*, const char*, const char*);
static void ripper_warningV(struct parser_params*, const char*, VALUE);
#endif

#ifdef RIPPER
static void ripper_compile_error(struct parser_params*, const char *fmt, ...);
# define rb_compile_error ripper_compile_error
# define compile_error ripper_compile_error
# define PARSER_ARG parser,
#else
# define rb_compile_error rb_compile_error_with_enc
# define compile_error parser->nerr++,rb_compile_error_with_enc
# define PARSER_ARG ruby_sourcefile, ruby_sourceline, (void *)current_enc,
#endif

/* Older versions of Yacc set YYMAXDEPTH to a very low value by default (150,
   for instance).  This is too low for Ruby to parse some files, such as
   date/format.rb, therefore bump the value up to at least Bison's default. */
#ifdef OLD_YACC
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif
#endif

#ifndef RIPPER
static void token_info_push(struct parser_params*, const char *token);
static void token_info_pop(struct parser_params*, const char *token);
#define token_info_push(token) (RTEST(ruby_verbose) ? token_info_push(parser, (token)) : (void)0)
#define token_info_pop(token) (RTEST(ruby_verbose) ? token_info_pop(parser, (token)) : (void)0)
#else
#define token_info_push(token) /* nothing */
#define token_info_pop(token) /* nothing */
#endif

/* Line 371 of yacc.c  */
#line 747 "parse.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
#ifndef yydebug
extern int yydebug;
#endif
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END_OF_INPUT = 0,
     keyword_class = 258,
     keyword_module = 259,
     keyword_def = 260,
     keyword_undef = 261,
     keyword_begin = 262,
     keyword_rescue = 263,
     keyword_ensure = 264,
     keyword_end = 265,
     keyword_if = 266,
     keyword_unless = 267,
     keyword_then = 268,
     keyword_elsif = 269,
     keyword_else = 270,
     keyword_case = 271,
     keyword_when = 272,
     keyword_while = 273,
     keyword_until = 274,
     keyword_for = 275,
     keyword_break = 276,
     keyword_next = 277,
     keyword_redo = 278,
     keyword_retry = 279,
     keyword_in = 280,
     keyword_do = 281,
     keyword_do_cond = 282,
     keyword_do_block = 283,
     keyword_do_LAMBDA = 284,
     keyword_return = 285,
     keyword_yield = 286,
     keyword_super = 287,
     keyword_self = 288,
     keyword_nil = 289,
     keyword_true = 290,
     keyword_false = 291,
     keyword_and = 292,
     keyword_or = 293,
     keyword_not = 294,
     modifier_if = 295,
     modifier_unless = 296,
     modifier_while = 297,
     modifier_until = 298,
     modifier_rescue = 299,
     keyword_alias = 300,
     keyword_defined = 301,
     keyword_BEGIN = 302,
     keyword_END = 303,
     keyword__LINE__ = 304,
     keyword__FILE__ = 305,
     keyword__ENCODING__ = 306,
     tIDENTIFIER = 307,
     tFID = 308,
     tGVAR = 309,
     tIVAR = 310,
     tCONSTANT = 311,
     tCVAR = 312,
     tLABEL = 313,
     tINTEGER = 314,
     tFLOAT = 315,
     tRATIONAL = 316,
     tIMAGINARY = 317,
     tSTRING_CONTENT = 318,
     tCHAR = 319,
     tNTH_REF = 320,
     tBACK_REF = 321,
     tREGEXP_END = 322,
     tUPLUS = 130,
     tUMINUS = 131,
     tPOW = 132,
     tCMP = 134,
     tEQ = 139,
     tEQQ = 140,
     tNEQ = 141,
     tGEQ = 138,
     tLEQ = 137,
     tANDOP = 323,
     tOROP = 324,
     tMATCH = 142,
     tNMATCH = 143,
     tDOT2 = 128,
     tDOT3 = 129,
     tAREF = 144,
     tASET = 145,
     tLSHFT = 135,
     tRSHFT = 136,
     tCOLON2 = 325,
     tCOLON3 = 326,
     tOP_ASGN = 327,
     tASSOC = 328,
     tLPAREN = 329,
     tLPAREN_ARG = 330,
     tRPAREN = 331,
     tLBRACK = 332,
     tLBRACE = 333,
     tLBRACE_ARG = 334,
     tSTAR = 335,
     tDSTAR = 336,
     tAMPER = 337,
     tLAMBDA = 338,
     tSYMBEG = 339,
     tSTRING_BEG = 340,
     tXSTRING_BEG = 341,
     tREGEXP_BEG = 342,
     tWORDS_BEG = 343,
     tQWORDS_BEG = 344,
     tSYMBOLS_BEG = 345,
     tQSYMBOLS_BEG = 346,
     tSTRING_DBEG = 347,
     tSTRING_DEND = 348,
     tSTRING_DVAR = 349,
     tSTRING_END = 350,
     tLAMBEG = 351,
     tLOWEST = 352,
     tUMINUS_NUM = 353,
     tLAST_TOKEN = 354
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 695 "ripper.y"

    VALUE val;
    NODE *node;
    ID id;
    int num;
    const struct vtable *vars;


/* Line 387 of yacc.c  */
#line 913 "parse.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct parser_params *parser);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 940 "parse.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   10754

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  144
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  204
/* YYNRULES -- Number of rules.  */
#define YYNRULES  627
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1060

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   354

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     143,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,   142,   129,     2,     2,     2,   127,   122,     2,
     138,   139,   125,   123,   136,   124,   135,   126,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   117,   141,
     119,   115,   118,   116,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   134,     2,   140,   121,     2,   137,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   132,   120,   133,   130,     2,    81,    82,
      68,    69,    70,     2,    71,    85,    86,    76,    75,    72,
      73,    74,    79,    80,    83,    84,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    77,    78,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   128,   131
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    14,    18,    21,
      23,    24,    30,    35,    38,    40,    42,    46,    49,    51,
      52,    58,    59,    64,    68,    72,    76,    79,    83,    87,
      91,    95,    99,   104,   106,   110,   114,   121,   127,   133,
     139,   145,   149,   153,   157,   159,   163,   167,   169,   173,
     177,   181,   184,   186,   188,   190,   192,   194,   199,   200,
     206,   208,   211,   215,   220,   226,   231,   237,   240,   243,
     246,   249,   252,   254,   258,   260,   264,   266,   269,   273,
     279,   282,   287,   290,   295,   297,   301,   303,   307,   310,
     314,   316,   320,   322,   324,   329,   333,   337,   341,   345,
     348,   350,   352,   354,   359,   363,   367,   371,   375,   378,
     380,   382,   384,   387,   389,   393,   395,   397,   399,   401,
     403,   405,   407,   409,   411,   413,   414,   419,   421,   423,
     425,   427,   429,   431,   433,   435,   437,   439,   441,   443,
     445,   447,   449,   451,   453,   455,   457,   459,   461,   463,
     465,   467,   469,   471,   473,   475,   477,   479,   481,   483,
     485,   487,   489,   491,   493,   495,   497,   499,   501,   503,
     505,   507,   509,   511,   513,   515,   517,   519,   521,   523,
     525,   527,   529,   531,   533,   535,   537,   539,   541,   543,
     545,   547,   549,   551,   553,   555,   557,   559,   561,   565,
     571,   575,   581,   588,   594,   600,   606,   612,   617,   621,
     625,   629,   633,   637,   641,   645,   649,   653,   658,   661,
     664,   668,   672,   676,   680,   684,   688,   692,   696,   700,
     704,   708,   712,   716,   719,   722,   726,   730,   734,   738,
     739,   744,   751,   753,   755,   757,   760,   765,   768,   772,
     774,   776,   778,   780,   783,   788,   791,   793,   796,   799,
     804,   806,   807,   810,   813,   816,   818,   820,   823,   827,
     832,   834,   836,   840,   845,   848,   850,   852,   854,   856,
     858,   860,   862,   864,   866,   868,   870,   871,   876,   877,
     881,   882,   883,   889,   893,   897,   900,   904,   908,   910,
     915,   919,   921,   922,   929,   934,   938,   941,   943,   946,
     949,   956,   963,   964,   965,   973,   974,   975,   983,   989,
     994,   995,   996,  1006,  1007,  1014,  1015,  1016,  1025,  1026,
    1032,  1033,  1040,  1041,  1042,  1052,  1054,  1056,  1058,  1060,
    1062,  1064,  1066,  1068,  1070,  1072,  1074,  1076,  1078,  1080,
    1082,  1084,  1086,  1088,  1091,  1093,  1095,  1097,  1103,  1105,
    1108,  1110,  1112,  1114,  1118,  1120,  1124,  1126,  1131,  1138,
    1142,  1148,  1151,  1156,  1158,  1162,  1167,  1170,  1173,  1175,
    1178,  1179,  1186,  1195,  1200,  1207,  1212,  1215,  1222,  1225,
    1230,  1237,  1240,  1245,  1248,  1253,  1255,  1257,  1259,  1263,
    1265,  1270,  1272,  1277,  1279,  1283,  1285,  1287,  1288,  1289,
    1290,  1296,  1301,  1303,  1307,  1311,  1312,  1318,  1321,  1326,
    1332,  1338,  1341,  1342,  1348,  1349,  1355,  1359,  1360,  1365,
    1366,  1371,  1374,  1376,  1381,  1382,  1388,  1389,  1395,  1401,
    1403,  1405,  1412,  1414,  1416,  1418,  1420,  1423,  1425,  1428,
    1430,  1432,  1434,  1436,  1438,  1440,  1442,  1445,  1449,  1453,
    1457,  1461,  1465,  1466,  1470,  1472,  1475,  1479,  1483,  1484,
    1488,  1492,  1496,  1500,  1504,  1505,  1509,  1510,  1514,  1515,
    1518,  1519,  1522,  1523,  1526,  1528,  1529,  1533,  1534,  1535,
    1536,  1543,  1545,  1547,  1549,  1551,  1554,  1556,  1558,  1560,
    1562,  1566,  1568,  1571,  1573,  1575,  1577,  1579,  1581,  1583,
    1585,  1587,  1589,  1591,  1593,  1595,  1597,  1599,  1601,  1603,
    1605,  1607,  1609,  1611,  1613,  1615,  1617,  1618,  1623,  1626,
    1630,  1631,  1635,  1640,  1643,  1646,  1648,  1651,  1652,  1659,
    1668,  1673,  1680,  1685,  1692,  1695,  1700,  1707,  1710,  1715,
    1718,  1723,  1725,  1726,  1728,  1730,  1732,  1734,  1736,  1738,
    1740,  1742,  1746,  1748,  1752,  1754,  1757,  1759,  1762,  1764,
    1766,  1770,  1772,  1776,  1778,  1780,  1783,  1785,  1789,  1793,
    1795,  1799,  1801,  1805,  1807,  1809,  1812,  1814,  1816,  1818,
    1821,  1824,  1826,  1828,  1829,  1834,  1836,  1839,  1841,  1845,
    1849,  1852,  1855,  1857,  1859,  1861,  1863,  1865,  1867,  1869,
    1871,  1873,  1875,  1877,  1879,  1880,  1882,  1883,  1885,  1888,
    1891,  1892,  1894,  1896,  1898,  1900,  1902,  1905
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     145,     0,    -1,    -1,   146,   147,    -1,   148,   340,    -1,
     347,    -1,   149,    -1,   148,   346,   149,    -1,     1,   149,
      -1,   156,    -1,    -1,    47,   150,   132,   147,   133,    -1,
     152,   265,   233,   268,    -1,   153,   340,    -1,   347,    -1,
     154,    -1,   153,   346,   154,    -1,     1,   156,    -1,   156,
      -1,    -1,    47,   155,   132,   147,   133,    -1,    -1,    45,
     179,   157,   179,    -1,    45,    54,    54,    -1,    45,    54,
      66,    -1,    45,    54,    65,    -1,     6,   180,    -1,   156,
      40,   160,    -1,   156,    41,   160,    -1,   156,    42,   160,
      -1,   156,    43,   160,    -1,   156,    44,   156,    -1,    48,
     132,   152,   133,    -1,   158,    -1,   167,   115,   161,    -1,
     301,    89,   161,    -1,   218,   134,   190,   343,    89,   161,
      -1,   218,   135,    52,    89,   161,    -1,   218,   135,    56,
      89,   161,    -1,   218,    87,    56,    89,   161,    -1,   218,
      87,    52,    89,   161,    -1,   302,    89,   161,    -1,   174,
     115,   198,    -1,   167,   115,   197,    -1,   159,    -1,   174,
     115,   161,    -1,   174,   115,   158,    -1,   161,    -1,   159,
      37,   159,    -1,   159,    38,   159,    -1,    39,   341,   159,
      -1,   129,   161,    -1,   184,    -1,   159,    -1,   166,    -1,
     162,    -1,   254,    -1,   254,   339,   337,   192,    -1,    -1,
      96,   164,   241,   152,   133,    -1,   336,    -1,   165,   192,
      -1,   165,   192,   163,    -1,   218,   135,   337,   192,    -1,
     218,   135,   337,   192,   163,    -1,   218,    87,   337,   192,
      -1,   218,    87,   337,   192,   163,    -1,    32,   192,    -1,
      31,   192,    -1,    30,   191,    -1,    21,   191,    -1,    22,
     191,    -1,   169,    -1,    91,   168,   342,    -1,   169,    -1,
      91,   168,   342,    -1,   171,    -1,   171,   170,    -1,   171,
      97,   173,    -1,   171,    97,   173,   136,   172,    -1,   171,
      97,    -1,   171,    97,   136,   172,    -1,    97,   173,    -1,
      97,   173,   136,   172,    -1,    97,    -1,    97,   136,   172,
      -1,   173,    -1,    91,   168,   342,    -1,   170,   136,    -1,
     171,   170,   136,    -1,   170,    -1,   172,   136,   170,    -1,
     298,    -1,   299,    -1,   218,   134,   190,   343,    -1,   218,
     135,    52,    -1,   218,    87,    52,    -1,   218,   135,    56,
      -1,   218,    87,    56,    -1,    88,    56,    -1,   302,    -1,
     298,    -1,   299,    -1,   218,   134,   190,   343,    -1,   218,
     135,    52,    -1,   218,    87,    52,    -1,   218,   135,    56,
      -1,   218,    87,    56,    -1,    88,    56,    -1,   302,    -1,
      52,    -1,    56,    -1,    88,   175,    -1,   175,    -1,   218,
      87,   175,    -1,    52,    -1,    56,    -1,    53,    -1,   182,
      -1,   183,    -1,   177,    -1,   293,    -1,   178,    -1,   295,
      -1,   179,    -1,    -1,   180,   136,   181,   179,    -1,   120,
      -1,   121,    -1,   122,    -1,    71,    -1,    72,    -1,    73,
      -1,    79,    -1,    80,    -1,   118,    -1,    75,    -1,   119,
      -1,    76,    -1,    74,    -1,    85,    -1,    86,    -1,   123,
      -1,   124,    -1,   125,    -1,    97,    -1,   126,    -1,   127,
      -1,    70,    -1,    98,    -1,   129,    -1,   130,    -1,    68,
      -1,    69,    -1,    83,    -1,    84,    -1,   137,    -1,    49,
      -1,    50,    -1,    51,    -1,    47,    -1,    48,    -1,    45,
      -1,    37,    -1,     7,    -1,    21,    -1,    16,    -1,     3,
      -1,     5,    -1,    46,    -1,    26,    -1,    15,    -1,    14,
      -1,    10,    -1,     9,    -1,    36,    -1,    20,    -1,    25,
      -1,     4,    -1,    22,    -1,    34,    -1,    39,    -1,    38,
      -1,    23,    -1,     8,    -1,    24,    -1,    30,    -1,    33,
      -1,    32,    -1,    13,    -1,    35,    -1,     6,    -1,    17,
      -1,    31,    -1,    11,    -1,    12,    -1,    18,    -1,    19,
      -1,   174,   115,   184,    -1,   174,   115,   184,    44,   184,
      -1,   301,    89,   184,    -1,   301,    89,   184,    44,   184,
      -1,   218,   134,   190,   343,    89,   184,    -1,   218,   135,
      52,    89,   184,    -1,   218,   135,    56,    89,   184,    -1,
     218,    87,    52,    89,   184,    -1,   218,    87,    56,    89,
     184,    -1,    88,    56,    89,   184,    -1,   302,    89,   184,
      -1,   184,    81,   184,    -1,   184,    82,   184,    -1,   184,
     123,   184,    -1,   184,   124,   184,    -1,   184,   125,   184,
      -1,   184,   126,   184,    -1,   184,   127,   184,    -1,   184,
      70,   184,    -1,   128,   297,    70,   184,    -1,    68,   184,
      -1,    69,   184,    -1,   184,   120,   184,    -1,   184,   121,
     184,    -1,   184,   122,   184,    -1,   184,    71,   184,    -1,
     184,   118,   184,    -1,   184,    75,   184,    -1,   184,   119,
     184,    -1,   184,    76,   184,    -1,   184,    72,   184,    -1,
     184,    73,   184,    -1,   184,    74,   184,    -1,   184,    79,
     184,    -1,   184,    80,   184,    -1,   129,   184,    -1,   130,
     184,    -1,   184,    85,   184,    -1,   184,    86,   184,    -1,
     184,    77,   184,    -1,   184,    78,   184,    -1,    -1,    46,
     341,   185,   184,    -1,   184,   116,   184,   341,   117,   184,
      -1,   199,    -1,   184,    -1,   347,    -1,   196,   344,    -1,
     196,   136,   334,   344,    -1,   334,   344,    -1,   138,   190,
     342,    -1,   347,    -1,   188,    -1,   347,    -1,   191,    -1,
     196,   136,    -1,   196,   136,   334,   136,    -1,   334,   136,
      -1,   166,    -1,   196,   195,    -1,   334,   195,    -1,   196,
     136,   334,   195,    -1,   194,    -1,    -1,   193,   191,    -1,
      99,   186,    -1,   136,   194,    -1,   347,    -1,   186,    -1,
      97,   186,    -1,   196,   136,   186,    -1,   196,   136,    97,
     186,    -1,   198,    -1,   186,    -1,   196,   136,   186,    -1,
     196,   136,    97,   186,    -1,    97,   186,    -1,   269,    -1,
     270,    -1,   273,    -1,   274,    -1,   275,    -1,   280,    -1,
     278,    -1,   281,    -1,   300,    -1,   302,    -1,    53,    -1,
      -1,   219,   200,   151,   229,    -1,    -1,    92,   201,   342,
      -1,    -1,    -1,    92,   202,   159,   203,   342,    -1,    91,
     152,   139,    -1,   218,    87,    56,    -1,    88,    56,    -1,
      94,   187,   140,    -1,    95,   333,   133,    -1,    30,    -1,
      31,   138,   191,   342,    -1,    31,   138,   342,    -1,    31,
      -1,    -1,    46,   341,   138,   204,   159,   342,    -1,    39,
     138,   159,   342,    -1,    39,   138,   342,    -1,   165,   260,
      -1,   255,    -1,   255,   260,    -1,   100,   246,    -1,   220,
     160,   230,   152,   232,   229,    -1,   221,   160,   230,   152,
     233,   229,    -1,    -1,    -1,   222,   205,   160,   231,   206,
     152,   229,    -1,    -1,    -1,   223,   207,   160,   231,   208,
     152,   229,    -1,   224,   160,   340,   263,   229,    -1,   224,
     340,   263,   229,    -1,    -1,    -1,   225,   234,    25,   209,
     160,   231,   210,   152,   229,    -1,    -1,   226,   176,   303,
     211,   151,   229,    -1,    -1,    -1,   226,    85,   159,   212,
     345,   213,   151,   229,    -1,    -1,   227,   176,   214,   151,
     229,    -1,    -1,   228,   177,   215,   305,   151,   229,    -1,
      -1,    -1,   228,   331,   339,   216,   177,   217,   305,   151,
     229,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
     199,    -1,     7,    -1,    11,    -1,    12,    -1,    18,    -1,
      19,    -1,    16,    -1,    20,    -1,     3,    -1,     4,    -1,
       5,    -1,    10,    -1,   345,    -1,    13,    -1,   345,    13,
      -1,   345,    -1,    27,    -1,   233,    -1,    14,   160,   230,
     152,   232,    -1,   347,    -1,    15,   152,    -1,   174,    -1,
     167,    -1,   311,    -1,    91,   237,   342,    -1,   235,    -1,
     236,   136,   235,    -1,   236,    -1,   236,   136,    97,   311,
      -1,   236,   136,    97,   311,   136,   236,    -1,   236,   136,
      97,    -1,   236,   136,    97,   136,   236,    -1,    97,   311,
      -1,    97,   311,   136,   236,    -1,    97,    -1,    97,   136,
     236,    -1,   318,   136,   321,   330,    -1,   318,   330,    -1,
     321,   330,    -1,   329,    -1,   136,   238,    -1,    -1,   314,
     136,   324,   136,   327,   239,    -1,   314,   136,   324,   136,
     327,   136,   314,   239,    -1,   314,   136,   324,   239,    -1,
     314,   136,   324,   136,   314,   239,    -1,   314,   136,   327,
     239,    -1,   314,   136,    -1,   314,   136,   327,   136,   314,
     239,    -1,   314,   239,    -1,   324,   136,   327,   239,    -1,
     324,   136,   327,   136,   314,   239,    -1,   324,   239,    -1,
     324,   136,   314,   239,    -1,   327,   239,    -1,   327,   136,
     314,   239,    -1,   238,    -1,   347,    -1,   242,    -1,   120,
     243,   120,    -1,    78,    -1,   120,   240,   243,   120,    -1,
     341,    -1,   341,   141,   244,   341,    -1,   245,    -1,   244,
     136,   245,    -1,    52,    -1,   310,    -1,    -1,    -1,    -1,
     247,   248,   250,   249,   251,    -1,   138,   309,   243,   139,
      -1,   309,    -1,   113,   152,   133,    -1,    29,   152,    10,
      -1,    -1,    28,   253,   241,   152,    10,    -1,   166,   252,
      -1,   254,   339,   337,   189,    -1,   254,   339,   337,   189,
     260,    -1,   254,   339,   337,   192,   252,    -1,   165,   188,
      -1,    -1,   218,   135,   337,   256,   189,    -1,    -1,   218,
      87,   337,   257,   188,    -1,   218,    87,   338,    -1,    -1,
     218,   135,   258,   188,    -1,    -1,   218,    87,   259,   188,
      -1,    32,   188,    -1,    32,    -1,   218,   134,   190,   343,
      -1,    -1,   132,   261,   241,   152,   133,    -1,    -1,    26,
     262,   241,   152,    10,    -1,    17,   196,   230,   152,   264,
      -1,   233,    -1,   263,    -1,     8,   266,   267,   230,   152,
     265,    -1,   347,    -1,   186,    -1,   198,    -1,   347,    -1,
      90,   174,    -1,   347,    -1,     9,   152,    -1,   347,    -1,
     296,    -1,   293,    -1,   295,    -1,   271,    -1,    64,    -1,
     272,    -1,   271,   272,    -1,   102,   284,   112,    -1,   103,
     285,   112,    -1,   104,   286,    67,    -1,   105,   142,   112,
      -1,   105,   276,   112,    -1,    -1,   276,   277,   142,    -1,
     287,    -1,   277,   287,    -1,   107,   142,   112,    -1,   107,
     279,   112,    -1,    -1,   279,   277,   142,    -1,   106,   142,
     112,    -1,   106,   282,   112,    -1,   108,   142,   112,    -1,
     108,   283,   112,    -1,    -1,   282,    63,   142,    -1,    -1,
     283,    63,   142,    -1,    -1,   284,   287,    -1,    -1,   285,
     287,    -1,    -1,   286,   287,    -1,    63,    -1,    -1,   111,
     288,   292,    -1,    -1,    -1,    -1,   109,   289,   290,   291,
     152,   110,    -1,    54,    -1,    55,    -1,    57,    -1,   302,
      -1,   101,   294,    -1,   177,    -1,    55,    -1,    54,    -1,
      57,    -1,   101,   285,   112,    -1,   297,    -1,   128,   297,
      -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,    52,
      -1,    55,    -1,    54,    -1,    56,    -1,    57,    -1,    34,
      -1,    33,    -1,    35,    -1,    36,    -1,    50,    -1,    49,
      -1,    51,    -1,   298,    -1,   299,    -1,   298,    -1,   299,
      -1,    65,    -1,    66,    -1,   345,    -1,    -1,   119,   304,
     160,   345,    -1,     1,   345,    -1,   138,   309,   342,    -1,
      -1,   306,   309,   345,    -1,   319,   136,   321,   330,    -1,
     319,   330,    -1,   321,   330,    -1,   329,    -1,   136,   307,
      -1,    -1,   314,   136,   325,   136,   327,   308,    -1,   314,
     136,   325,   136,   327,   136,   314,   308,    -1,   314,   136,
     325,   308,    -1,   314,   136,   325,   136,   314,   308,    -1,
     314,   136,   327,   308,    -1,   314,   136,   327,   136,   314,
     308,    -1,   314,   308,    -1,   325,   136,   327,   308,    -1,
     325,   136,   327,   136,   314,   308,    -1,   325,   308,    -1,
     325,   136,   314,   308,    -1,   327,   308,    -1,   327,   136,
     314,   308,    -1,   307,    -1,    -1,    56,    -1,    55,    -1,
      54,    -1,    57,    -1,   310,    -1,    52,    -1,   311,    -1,
     312,    -1,    91,   237,   342,    -1,   313,    -1,   314,   136,
     313,    -1,    58,    -1,   315,   186,    -1,   315,    -1,   315,
     218,    -1,   315,    -1,   317,    -1,   318,   136,   317,    -1,
     316,    -1,   319,   136,   316,    -1,    70,    -1,    98,    -1,
     320,    52,    -1,   320,    -1,   312,   115,   186,    -1,   312,
     115,   218,    -1,   323,    -1,   324,   136,   323,    -1,   322,
      -1,   325,   136,   322,    -1,   125,    -1,    97,    -1,   326,
      52,    -1,   326,    -1,   122,    -1,    99,    -1,   328,    52,
      -1,   136,   329,    -1,   347,    -1,   300,    -1,    -1,   138,
     332,   159,   342,    -1,   347,    -1,   334,   344,    -1,   335,
      -1,   334,   136,   335,    -1,   186,    90,   186,    -1,    58,
     186,    -1,    98,   186,    -1,    52,    -1,    56,    -1,    53,
      -1,    52,    -1,    56,    -1,    53,    -1,   182,    -1,    52,
      -1,    53,    -1,   182,    -1,   135,    -1,    87,    -1,    -1,
     346,    -1,    -1,   143,    -1,   341,   139,    -1,   341,   140,
      -1,    -1,   143,    -1,   136,    -1,   141,    -1,   143,    -1,
     345,    -1,   346,   141,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   859,   859,   859,   890,   901,   910,   918,   926,   932,
     934,   933,   954,   987,   998,  1007,  1015,  1023,  1029,  1034,
    1033,  1054,  1054,  1062,  1070,  1081,  1091,  1099,  1108,  1117,
    1130,  1143,  1152,  1164,  1165,  1175,  1180,  1201,  1206,  1211,
    1221,  1226,  1236,  1245,  1254,  1257,  1266,  1278,  1279,  1287,
    1295,  1303,  1311,  1314,  1326,  1327,  1330,  1331,  1343,  1342,
    1364,  1374,  1383,  1396,  1405,  1417,  1426,  1438,  1447,  1456,
    1464,  1472,  1482,  1483,  1493,  1494,  1504,  1512,  1520,  1528,
    1537,  1545,  1554,  1562,  1571,  1579,  1590,  1591,  1601,  1609,
    1619,  1627,  1637,  1641,  1645,  1653,  1661,  1669,  1677,  1690,
    1703,  1715,  1724,  1733,  1741,  1749,  1757,  1765,  1778,  1791,
    1802,  1810,  1813,  1821,  1829,  1839,  1840,  1841,  1842,  1847,
    1858,  1859,  1862,  1870,  1873,  1881,  1881,  1891,  1892,  1893,
    1894,  1895,  1896,  1897,  1898,  1899,  1900,  1901,  1902,  1903,
    1904,  1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,  1913,
    1914,  1915,  1916,  1917,  1918,  1919,  1920,  1923,  1923,  1923,
    1924,  1924,  1925,  1925,  1925,  1926,  1926,  1926,  1926,  1927,
    1927,  1927,  1927,  1928,  1928,  1928,  1929,  1929,  1929,  1929,
    1930,  1930,  1930,  1930,  1931,  1931,  1931,  1931,  1932,  1932,
    1932,  1932,  1933,  1933,  1933,  1933,  1934,  1934,  1937,  1946,
    1956,  1961,  1971,  1997,  2002,  2007,  2012,  2022,  2032,  2043,
    2057,  2071,  2079,  2087,  2095,  2103,  2111,  2119,  2128,  2136,
    2144,  2152,  2160,  2168,  2176,  2184,  2192,  2200,  2208,  2216,
    2224,  2232,  2243,  2251,  2259,  2267,  2275,  2283,  2291,  2299,
    2299,  2308,  2318,  2324,  2336,  2337,  2341,  2349,  2359,  2369,
    2370,  2373,  2374,  2375,  2379,  2387,  2397,  2406,  2414,  2424,
    2433,  2442,  2442,  2454,  2464,  2468,  2474,  2482,  2490,  2504,
    2520,  2521,  2524,  2538,  2553,  2563,  2564,  2565,  2566,  2567,
    2568,  2569,  2570,  2571,  2572,  2573,  2582,  2581,  2609,  2609,
    2618,  2622,  2617,  2631,  2639,  2647,  2655,  2668,  2676,  2684,
    2692,  2700,  2708,  2708,  2717,  2725,  2733,  2743,  2744,  2754,
    2758,  2770,  2782,  2782,  2782,  2793,  2793,  2793,  2804,  2815,
    2824,  2826,  2823,  2890,  2889,  2911,  2916,  2910,  2935,  2934,
    2956,  2955,  2978,  2979,  2978,  2999,  3007,  3015,  3023,  3033,
    3045,  3051,  3057,  3063,  3069,  3075,  3081,  3087,  3093,  3099,
    3109,  3115,  3120,  3121,  3128,  3133,  3136,  3137,  3150,  3151,
    3161,  3162,  3165,  3173,  3183,  3191,  3201,  3209,  3218,  3227,
    3235,  3243,  3252,  3264,  3272,  3283,  3287,  3291,  3295,  3301,
    3306,  3311,  3315,  3319,  3323,  3327,  3331,  3339,  3343,  3347,
    3351,  3355,  3359,  3363,  3367,  3371,  3377,  3378,  3384,  3393,
    3402,  3413,  3417,  3427,  3434,  3443,  3451,  3457,  3460,  3465,
    3457,  3481,  3489,  3495,  3499,  3506,  3505,  3526,  3542,  3551,
    3563,  3577,  3587,  3586,  3603,  3602,  3618,  3627,  3626,  3644,
    3643,  3660,  3668,  3676,  3691,  3690,  3710,  3709,  3730,  3742,
    3743,  3746,  3765,  3768,  3776,  3784,  3787,  3791,  3794,  3802,
    3805,  3806,  3814,  3817,  3834,  3835,  3836,  3846,  3856,  3883,
    3948,  3957,  3968,  3975,  3985,  3993,  4003,  4012,  4023,  4030,
    4042,  4051,  4061,  4070,  4081,  4088,  4099,  4106,  4121,  4128,
    4139,  4146,  4157,  4164,  4193,  4195,  4194,  4211,  4217,  4222,
    4210,  4241,  4249,  4257,  4265,  4268,  4279,  4280,  4281,  4282,
    4285,  4296,  4297,  4308,  4309,  4310,  4311,  4314,  4315,  4316,
    4317,  4318,  4321,  4322,  4323,  4324,  4325,  4326,  4327,  4330,
    4343,  4353,  4361,  4371,  4372,  4375,  4384,  4383,  4392,  4404,
    4414,  4414,  4427,  4431,  4435,  4439,  4445,  4450,  4455,  4459,
    4463,  4467,  4471,  4475,  4479,  4483,  4487,  4491,  4495,  4499,
    4503,  4507,  4512,  4518,  4527,  4536,  4545,  4556,  4557,  4564,
    4571,  4579,  4598,  4605,  4619,  4626,  4635,  4646,  4655,  4666,
    4674,  4691,  4699,  4715,  4716,  4719,  4724,  4730,  4741,  4752,
    4760,  4776,  4784,  4800,  4801,  4804,  4817,  4828,  4829,  4832,
    4849,  4853,  4863,  4873,  4873,  4902,  4903,  4913,  4920,  4930,
    4942,  4950,  4960,  4961,  4962,  4965,  4966,  4967,  4968,  4971,
    4972,  4973,  4976,  4981,  4988,  4989,  4992,  4993,  4996,  4999,
    5002,  5003,  5004,  5007,  5008,  5011,  5012,  5016
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end-of-input\"", "error", "$undefined", "keyword_class",
  "keyword_module", "keyword_def", "keyword_undef", "keyword_begin",
  "keyword_rescue", "keyword_ensure", "keyword_end", "keyword_if",
  "keyword_unless", "keyword_then", "keyword_elsif", "keyword_else",
  "keyword_case", "keyword_when", "keyword_while", "keyword_until",
  "keyword_for", "keyword_break", "keyword_next", "keyword_redo",
  "keyword_retry", "keyword_in", "keyword_do", "keyword_do_cond",
  "keyword_do_block", "keyword_do_LAMBDA", "keyword_return",
  "keyword_yield", "keyword_super", "keyword_self", "keyword_nil",
  "keyword_true", "keyword_false", "keyword_and", "keyword_or",
  "keyword_not", "modifier_if", "modifier_unless", "modifier_while",
  "modifier_until", "modifier_rescue", "keyword_alias", "keyword_defined",
  "keyword_BEGIN", "keyword_END", "keyword__LINE__", "keyword__FILE__",
  "keyword__ENCODING__", "tIDENTIFIER", "tFID", "tGVAR", "tIVAR",
  "tCONSTANT", "tCVAR", "tLABEL", "tINTEGER", "tFLOAT", "tRATIONAL",
  "tIMAGINARY", "tSTRING_CONTENT", "tCHAR", "tNTH_REF", "tBACK_REF",
  "tREGEXP_END", "\"unary+\"", "\"unary-\"", "\"**\"", "\"<=>\"", "\"==\"",
  "\"===\"", "\"!=\"", "\">=\"", "\"<=\"", "\"&&\"", "\"||\"", "\"=~\"",
  "\"!~\"", "\"..\"", "\"...\"", "\"[]\"", "\"[]=\"", "\"<<\"", "\">>\"",
  "\"::\"", "\":: at EXPR_BEG\"", "tOP_ASGN", "\"=>\"", "\"(\"",
  "\"( arg\"", "\")\"", "\"[\"", "\"{\"", "\"{ arg\"", "\"*\"",
  "\"**arg\"", "\"&\"", "\"->\"", "tSYMBEG", "tSTRING_BEG", "tXSTRING_BEG",
  "tREGEXP_BEG", "tWORDS_BEG", "tQWORDS_BEG", "tSYMBOLS_BEG",
  "tQSYMBOLS_BEG", "tSTRING_DBEG", "tSTRING_DEND", "tSTRING_DVAR",
  "tSTRING_END", "tLAMBEG", "tLOWEST", "'='", "'?'", "':'", "'>'", "'<'",
  "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "tUMINUS_NUM",
  "'!'", "'~'", "tLAST_TOKEN", "'{'", "'}'", "'['", "'.'", "','", "'`'",
  "'('", "')'", "']'", "';'", "' '", "'\\n'", "$accept", "program", "$@1",
  "top_compstmt", "top_stmts", "top_stmt", "$@2", "bodystmt", "compstmt",
  "stmts", "stmt_or_begin", "$@3", "stmt", "$@4", "command_asgn", "expr",
  "expr_value", "command_call", "block_command", "cmd_brace_block", "@5",
  "fcall", "command", "mlhs", "mlhs_inner", "mlhs_basic", "mlhs_item",
  "mlhs_head", "mlhs_post", "mlhs_node", "lhs", "cname", "cpath", "fname",
  "fsym", "fitem", "undef_list", "$@6", "op", "reswords", "arg", "$@7",
  "arg_value", "aref_args", "paren_args", "opt_paren_args",
  "opt_call_args", "call_args", "command_args", "@8", "block_arg",
  "opt_block_arg", "args", "mrhs_arg", "mrhs", "primary", "@9", "$@10",
  "$@11", "$@12", "$@13", "$@14", "$@15", "$@16", "$@17", "$@18", "$@19",
  "@20", "@21", "@22", "@23", "@24", "$@25", "$@26", "primary_value",
  "k_begin", "k_if", "k_unless", "k_while", "k_until", "k_case", "k_for",
  "k_class", "k_module", "k_def", "k_end", "then", "do", "if_tail",
  "opt_else", "for_var", "f_marg", "f_marg_list", "f_margs",
  "block_args_tail", "opt_block_args_tail", "block_param",
  "opt_block_param", "block_param_def", "opt_bv_decl", "bv_decls", "bvar",
  "lambda", "@27", "@28", "@29", "f_larglist", "lambda_body", "do_block",
  "@30", "block_call", "method_call", "@31", "@32", "@33", "@34",
  "brace_block", "@35", "@36", "case_body", "cases", "opt_rescue",
  "exc_list", "exc_var", "opt_ensure", "literal", "strings", "string",
  "string1", "xstring", "regexp", "words", "word_list", "word", "symbols",
  "symbol_list", "qwords", "qsymbols", "qword_list", "qsym_list",
  "string_contents", "xstring_contents", "regexp_contents",
  "string_content", "@37", "@38", "@39", "@40", "string_dvar", "symbol",
  "sym", "dsym", "numeric", "simple_numeric", "user_variable",
  "keyword_variable", "var_ref", "var_lhs", "backref", "superclass",
  "$@41", "f_arglist", "@42", "args_tail", "opt_args_tail", "f_args",
  "f_bad_arg", "f_norm_arg", "f_arg_asgn", "f_arg_item", "f_arg",
  "f_label", "f_kw", "f_block_kw", "f_block_kwarg", "f_kwarg",
  "kwrest_mark", "f_kwrest", "f_opt", "f_block_opt", "f_block_optarg",
  "f_optarg", "restarg_mark", "f_rest_arg", "blkarg_mark", "f_block_arg",
  "opt_f_block_arg", "singleton", "$@43", "assoc_list", "assocs", "assoc",
  "operation", "operation2", "operation3", "dot_or_colon", "opt_terms",
  "opt_nl", "rparen", "rbracket", "trailer", "term", "terms", "none", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   130,   131,
     132,   134,   139,   140,   141,   138,   137,   323,   324,   142,
     143,   128,   129,   144,   145,   135,   136,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,    61,    63,    58,    62,    60,
     124,    94,    38,    43,    45,    42,    47,    37,   353,    33,
     126,   354,   123,   125,    91,    46,    44,    96,    40,    41,
      93,    59,    32,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   144,   146,   145,   147,   148,   148,   148,   148,   149,
     150,   149,   151,   152,   153,   153,   153,   153,   154,   155,
     154,   157,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   158,   158,   159,   159,   159,
     159,   159,   159,   160,   161,   161,   162,   162,   164,   163,
     165,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   167,   167,   168,   168,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   170,   170,   171,   171,
     172,   172,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     175,   175,   176,   176,   176,   177,   177,   177,   177,   177,
     178,   178,   179,   179,   180,   181,   180,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   182,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   185,
     184,   184,   184,   186,   187,   187,   187,   187,   188,   189,
     189,   190,   190,   190,   190,   190,   191,   191,   191,   191,
     191,   193,   192,   194,   195,   195,   196,   196,   196,   196,
     197,   197,   198,   198,   198,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   200,   199,   201,   199,
     202,   203,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   204,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   205,   206,   199,   207,   208,   199,   199,   199,
     209,   210,   199,   211,   199,   212,   213,   199,   214,   199,
     215,   199,   216,   217,   199,   199,   199,   199,   199,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   230,   230,   231,   231,   232,   232,   233,   233,
     234,   234,   235,   235,   236,   236,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   238,   238,   238,   238,   239,
     239,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   241,   241,   242,   242,
     242,   243,   243,   244,   244,   245,   245,   247,   248,   249,
     246,   250,   250,   251,   251,   253,   252,   254,   254,   254,
     254,   255,   256,   255,   257,   255,   255,   258,   255,   259,
     255,   255,   255,   255,   261,   260,   262,   260,   263,   264,
     264,   265,   265,   266,   266,   266,   267,   267,   268,   268,
     269,   269,   269,   270,   271,   271,   271,   272,   273,   274,
     275,   275,   276,   276,   277,   277,   278,   278,   279,   279,
     280,   280,   281,   281,   282,   282,   283,   283,   284,   284,
     285,   285,   286,   286,   287,   288,   287,   289,   290,   291,
     287,   292,   292,   292,   292,   293,   294,   294,   294,   294,
     295,   296,   296,   297,   297,   297,   297,   298,   298,   298,
     298,   298,   299,   299,   299,   299,   299,   299,   299,   300,
     300,   301,   301,   302,   302,   303,   304,   303,   303,   305,
     306,   305,   307,   307,   307,   307,   308,   308,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   310,   310,   310,   310,   311,   311,   312,
     313,   313,   314,   314,   315,   316,   316,   317,   317,   318,
     318,   319,   319,   320,   320,   321,   321,   322,   323,   324,
     324,   325,   325,   326,   326,   327,   327,   328,   328,   329,
     330,   330,   331,   332,   331,   333,   333,   334,   334,   335,
     335,   335,   336,   336,   336,   337,   337,   337,   337,   338,
     338,   338,   339,   339,   340,   340,   341,   341,   342,   343,
     344,   344,   344,   345,   345,   346,   346,   347
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     3,     2,     1,
       0,     5,     4,     2,     1,     1,     3,     2,     1,     0,
       5,     0,     4,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     4,     1,     3,     3,     6,     5,     5,     5,
       5,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     2,     1,     1,     1,     1,     1,     4,     0,     5,
       1,     2,     3,     4,     5,     4,     5,     2,     2,     2,
       2,     2,     1,     3,     1,     3,     1,     2,     3,     5,
       2,     4,     2,     4,     1,     3,     1,     3,     2,     3,
       1,     3,     1,     1,     4,     3,     3,     3,     3,     2,
       1,     1,     1,     4,     3,     3,     3,     3,     2,     1,
       1,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     5,
       3,     5,     6,     5,     5,     5,     5,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     3,     3,     3,     0,
       4,     6,     1,     1,     1,     2,     4,     2,     3,     1,
       1,     1,     1,     2,     4,     2,     1,     2,     2,     4,
       1,     0,     2,     2,     2,     1,     1,     2,     3,     4,
       1,     1,     3,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     3,
       0,     0,     5,     3,     3,     2,     3,     3,     1,     4,
       3,     1,     0,     6,     4,     3,     2,     1,     2,     2,
       6,     6,     0,     0,     7,     0,     0,     7,     5,     4,
       0,     0,     9,     0,     6,     0,     0,     8,     0,     5,
       0,     6,     0,     0,     9,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     5,     1,     2,
       1,     1,     1,     3,     1,     3,     1,     4,     6,     3,
       5,     2,     4,     1,     3,     4,     2,     2,     1,     2,
       0,     6,     8,     4,     6,     4,     2,     6,     2,     4,
       6,     2,     4,     2,     4,     1,     1,     1,     3,     1,
       4,     1,     4,     1,     3,     1,     1,     0,     0,     0,
       5,     4,     1,     3,     3,     0,     5,     2,     4,     5,
       5,     2,     0,     5,     0,     5,     3,     0,     4,     0,
       4,     2,     1,     4,     0,     5,     0,     5,     5,     1,
       1,     6,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     3,     3,
       3,     3,     0,     3,     1,     2,     3,     3,     0,     3,
       3,     3,     3,     3,     0,     3,     0,     3,     0,     2,
       0,     2,     0,     2,     1,     0,     3,     0,     0,     0,
       6,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     2,     3,
       0,     3,     4,     2,     2,     1,     2,     0,     6,     8,
       4,     6,     4,     6,     2,     4,     6,     2,     4,     2,
       4,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     2,     1,     2,     1,     1,
       3,     1,     3,     1,     1,     2,     1,     3,     3,     1,
       3,     1,     3,     1,     1,     2,     1,     1,     1,     2,
       2,     1,     1,     0,     4,     1,     2,     1,     3,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     0,     1,     2,     2,
       0,     1,     1,     1,     1,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,   347,   348,   349,     0,   340,
     341,   342,   345,   343,   344,   346,   335,   336,   337,   338,
     298,   261,   261,   513,   512,   514,   515,   616,     0,   616,
      10,     0,   517,   516,   518,   602,   604,   509,   508,   603,
     511,   503,   504,   505,   506,   454,   523,   524,     0,     0,
       0,     0,   290,   627,   627,    84,   407,   480,   478,   480,
     482,   462,   474,   468,   476,     0,     0,     0,     3,   614,
       6,     9,    33,    44,    47,    55,   261,    54,     0,    72,
       0,    76,    86,     0,    52,   242,     0,   286,     0,     0,
     312,   315,   614,     0,     0,     0,     0,    56,   307,   275,
     276,   453,   455,   277,   278,   279,   281,   280,   282,   451,
     452,   450,   501,   519,   520,   283,     0,   284,    60,     5,
       8,   167,   178,   168,   191,   164,   184,   174,   173,   194,
     195,   189,   172,   171,   166,   192,   196,   197,   176,   165,
     179,   183,   185,   177,   170,   186,   193,   188,   187,   180,
     190,   175,   163,   182,   181,   162,   169,   160,   161,   157,
     158,   159,   115,   117,   116,   152,   153,   148,   130,   131,
     132,   139,   136,   138,   133,   134,   154,   155,   140,   141,
     145,   149,   135,   137,   127,   128,   129,   142,   143,   144,
     146,   147,   150,   151,   156,   120,   122,   124,    26,   118,
     119,   121,   123,     0,     0,     0,     0,     0,     0,     0,
       0,   256,     0,   243,   266,    70,   260,   627,     0,   519,
     520,     0,   284,   627,   597,    71,    69,   616,    68,     0,
     627,   431,    67,   616,   617,     0,     0,    21,   239,     0,
       0,   335,   336,   298,   301,   432,     0,   218,     0,   219,
     295,     0,    19,     0,     0,   614,    15,    18,   616,    74,
      14,   616,     0,     0,   620,   620,   244,     0,     0,   620,
     595,   616,     0,     0,     0,    82,   339,     0,    92,    93,
     100,   309,   408,   498,   497,   499,   496,     0,   495,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     502,    51,   233,   234,   623,   624,     4,   625,   615,     0,
       0,     0,     0,     0,     0,     0,   436,   434,   421,    61,
     306,   415,   417,     0,    88,     0,    80,    77,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   429,   627,   427,     0,    53,
       0,     0,     0,     0,   614,     0,   615,     0,   361,   360,
       0,     0,   519,   520,   284,   110,   111,     0,     0,   113,
       0,     0,   519,   520,   284,   328,   187,   180,   190,   175,
     157,   158,   159,   115,   116,   593,   330,   592,     0,   613,
     612,     0,   308,   456,     0,     0,   125,   600,   295,   267,
     601,   263,     0,     0,     0,   257,   265,   429,   627,   427,
       0,     0,     0,   258,   616,     0,   300,   262,   616,   252,
     627,   627,   251,   616,   305,    50,    23,    25,    24,     0,
     302,     0,     0,     0,   429,   427,     0,    17,     0,   616,
     293,    13,   615,    73,   289,   291,   296,   622,   621,   245,
     622,   247,   297,   596,     0,    99,   502,    90,    85,     0,
     429,   627,   427,   552,   484,   487,   485,   500,   481,   457,
     479,   458,   459,   483,   460,   461,     0,   464,   470,     0,
     471,   466,   467,     0,   472,     0,   473,     0,   626,     7,
      27,    28,    29,    30,    31,    48,    49,   627,   627,    58,
      62,   627,     0,    34,   271,     0,    43,   270,   616,     0,
      78,    89,    46,    45,     0,   198,   266,    42,   216,   223,
     228,   229,   230,   225,   227,   237,   238,   231,   232,   209,
     210,   235,   236,   616,   224,   226,   220,   221,   222,   211,
     212,   213,   214,   215,   605,   607,   606,   608,     0,   261,
     426,   616,   605,   607,   606,   608,     0,   261,     0,   627,
     352,     0,   351,     0,     0,     0,     0,     0,     0,   295,
     429,   627,   427,   320,   325,   110,   111,   112,     0,   526,
     323,   525,   429,   627,   427,     0,     0,   530,   332,   605,
     606,   261,    35,   200,    41,   208,     0,   198,   599,     0,
     268,   264,   627,   605,   606,   616,   605,   606,   598,   299,
     618,   248,   253,   255,   304,    22,     0,   240,     0,    32,
     424,   422,   207,     0,    75,    16,   616,   620,     0,    83,
      96,    98,   616,   605,   606,   558,   555,   554,   553,   556,
     564,   573,     0,   584,   574,   588,   587,   583,   552,   409,
     551,   412,   557,   559,   560,   562,   537,   566,   571,   627,
     576,   627,   581,   537,   586,   537,     0,   535,   488,     0,
     463,   465,   475,   469,   477,   217,   399,   616,     0,   397,
     396,     0,   627,     0,   274,     0,    87,    81,     0,     0,
       0,     0,     0,     0,   430,    65,     0,     0,   433,     0,
       0,   428,    63,   627,   350,   287,   627,   627,   442,   627,
     353,   627,   355,   313,   354,   316,     0,     0,   319,   609,
     294,   616,   605,   606,     0,     0,   528,     0,     0,   110,
     111,   114,   616,     0,   616,   552,     0,   552,     0,   250,
     418,    57,   249,     0,   126,   269,   259,     0,     0,   433,
       0,     0,   627,   616,    11,     0,   292,   246,    91,    94,
       0,   373,   364,   366,   616,   362,   616,     0,     0,     0,
     544,   565,     0,   533,   591,   575,     0,   534,     0,   547,
     585,     0,   549,   589,   489,   491,   492,   493,   486,   494,
     395,   616,     0,   560,   380,   568,   569,   627,   627,   579,
     380,   380,   378,   401,     0,     0,     0,     0,     0,   272,
      79,   199,     0,    40,   205,    39,   206,    66,   425,   619,
       0,    37,   203,    38,   204,    64,   423,   443,   444,   627,
     445,     0,   627,   358,     0,     0,   356,     0,     0,     0,
     318,     0,     0,   433,     0,   326,     0,     0,   433,   329,
     594,   616,     0,     0,   333,   419,   420,   201,     0,   254,
     303,    20,   616,     0,   371,     0,   561,     0,     0,     0,
     410,   577,   536,   563,   537,   537,   572,   627,   590,   537,
     582,   537,   560,   537,     0,     0,   398,     0,   386,   388,
       0,   567,     0,   376,   377,     0,   391,     0,   393,     0,
     437,   435,     0,   416,   273,   241,    36,   202,     0,     0,
     447,   359,     0,    12,   449,     0,   310,   311,     0,     0,
     268,   627,   321,     0,   527,   324,   529,   331,   531,   530,
     363,   374,     0,   369,   365,   411,     0,     0,     0,   540,
       0,   542,   532,     0,   548,     0,   545,   550,     0,   400,
     578,   379,   380,   380,   295,   429,   570,   627,   380,   580,
     380,   380,   405,   616,   403,   406,    59,     0,   446,     0,
     101,   102,   109,     0,   448,     0,   314,   317,   439,   440,
     438,     0,     0,     0,     0,   372,     0,   367,   414,   413,
     537,   537,   537,   537,   490,     0,   383,     0,   385,   609,
     294,   375,     0,   392,     0,   389,   394,     0,   402,   108,
     429,   627,   427,   627,   627,     0,   327,     0,   370,     0,
     541,     0,   538,   543,   546,   380,   380,   380,   380,   404,
     609,   107,   616,   605,   606,   441,   357,   322,   334,   368,
     537,   384,     0,   381,   387,   390,   433,   539,   380,   382
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    68,    69,    70,   239,   568,   569,   255,
     256,   448,   257,   439,    72,    73,   360,    74,    75,   510,
     692,   246,    77,    78,   258,    79,    80,    81,   468,    82,
     212,   379,   380,   195,   196,   197,   198,   606,   557,   200,
      84,   441,   214,   263,   231,   750,   428,   429,   228,   229,
     216,   415,   430,   516,   517,    85,   358,   261,   262,   636,
     626,   362,   848,   363,   849,   734,   991,   738,   735,   933,
     595,   597,   748,   939,   248,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,   715,   571,   723,   845,   846,
     371,   772,   773,   774,   961,   899,   801,   688,   689,   802,
     973,   974,   281,   282,   473,   777,   659,   880,   322,   511,
      97,    98,   713,   706,   566,   558,   320,   508,   507,   578,
     990,   717,   839,   919,   923,    99,   100,   101,   102,   103,
     104,   105,   293,   486,   106,   297,   107,   108,   295,   299,
     289,   287,   291,   478,   679,   678,   794,   894,   798,   109,
     288,   110,   111,   112,   219,   220,   115,   221,   222,   590,
     737,   746,   747,   882,   780,   661,   662,   663,   892,   665,
     666,   667,   668,   806,   807,   669,   670,   671,   672,   809,
     810,   673,   674,   675,   676,   677,   783,   398,   596,   268,
     431,   224,   118,   630,   560,   401,   306,   425,   426,   708,
     459,   572,   366,   260
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -815
static const yytype_int16 yypact[] =
{
    -815,   119,  2632,  -815,  7181,  -815,  -815,  -815,  6696,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  7296,  7296,  -815,  -815,
    7296,  3974,  3563,  -815,  -815,  -815,  -815,   254,  6561,    32,
    -815,    -1,  -815,  -815,  -815,  2878,  3700,  -815,  -815,  3015,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  8676,  8676,
     132,  4905,   -18,  7641,  7986,  6959,  -815,  6426,  -815,  -815,
    -815,    65,   115,   124,   134,   828,  8791,  8676,  -815,   460,
    -815,   896,  -815,   499,  -815,  -815,   103,   219,   225,  -815,
     215,  9021,  -815,   248,  2994,    33,    47,  -815,  8906,  8906,
    -815,  -815,  5806,  9132,  9243,  9354,  6290,    69,    61,  -815,
    -815,   278,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,    74,   270,  -815,   321,   612,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,   269,  -815,
    -815,  -815,  -815,   284,  8676,   371,  5046,  8676,  8676,  8676,
    8676,  -815,   323,  2994,   389,  -815,  -815,   330,   453,   258,
     294,   398,   429,   360,  -815,  -815,  -815,  5691,  -815,  7296,
    7296,  -815,  -815,  5921,  -815,  8906,   266,  -815,   382,   394,
    5187,  -815,  -815,  -815,   393,   410,   103,  -815,   524,   481,
     703,  7411,  -815,  4905,   430,   460,  -815,   896,    32,   461,
    -815,    32,  8906,   464,   -19,   385,  -815,   389,   495,   385,
    -815,    32,   583,   828,  9465,   504,  -815,   588,   608,   611,
     617,  -815,  -815,  -815,  -815,  -815,  -815,   459,  -815,   521,
     554,   434,   536,   562,   541,    41,   544,   575,   545,    72,
     602,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  6036,  8906,
    8906,  8906,  8906,  7411,  8906,  8906,  -815,  -815,  -815,   572,
    -815,  -815,  -815,  8101,  -815,  4905,  7070,   542,  8101,  8676,
    8676,  8676,  8676,  8676,  8676,  8676,  8676,  8676,  8676,  8676,
    8676,  8676,  8676,  8676,  8676,  8676,  8676,  8676,  8676,  8676,
    8676,  8676,  8676,  8676,  8676,  2464,  7296,  9748,  4252,   499,
      90,    90,  8906,  8906,   460,   663,   547,   629,  -815,  -815,
     622,   666,    70,    98,   117,   350,   381,  8906,   138,  -815,
      68,   638,  -815,  -815,  -815,  -815,    91,   173,   255,   265,
     316,   336,   356,   365,   369,  -815,  -815,  -815,    69,  -815,
    -815,  9827,  -815,  -815,  8791,  8791,  -815,  -815,   449,  -815,
    -815,  -815,  8676,  8676,  7526,  -815,  -815,  9906,  7296,  9985,
    8676,  8676,  7756,  -815,    32,   558,  -815,  -815,    32,  -815,
     563,   574,  -815,    71,  -815,  -815,  -815,  -815,  -815,  6696,
    -815,  8676,  5320,   579,  9906,  9985,  8676,   896,   589,    32,
    -815,  -815,  6151,   584,  -815,   499,  -815,  7871,  -815,  -815,
    7986,  -815,  -815,  -815,   382,   675,  -815,  -815,   594,  9465,
   10064,  7296, 10143,  1476,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,    50,  -815,  -815,   592,
    -815,  -815,  -815,   361,  -815,   595,  -815,  8676,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,    76,    76,  -815,
    -815,    76,  8676,  -815,   600,   605,  -815,  -815,    32,  9465,
     625,  -815,  -815,  -815,   623,  2080,  -815,  -815,   481,  3268,
    3268,  3268,  3268,   871,   871,  3405,  1982,  3268,  3268,  3131,
    3131,   699,   699,  2371,   871,   871,   520,   520,   970,    45,
      45,   481,   481,   481,  2262,  3152,  4111,  3289,   410,   615,
    -815,    32,   715,  -815,   743,  -815,   410,  3837,   753,   756,
    -815,  4393,   757,  4675,   101,   101,   663,  8216,   753,   118,
   10222,  7296, 10301,  -815,   499,  -815,   675,  -815,   460,  -815,
    -815,  -815, 10380,  7296,  9827,  4252,  8906,   633,  -815,  -815,
    -815,  1953,  -815,  2720,  -815,  2994,  6696,  2857,  -815,  8676,
     389,  -815,   360,  2741,  3426,    32,   509,   566,  -815,  -815,
    -815,  -815,  7526,  7756,  -815,  -815,  8906,  2994,   641,  -815,
    -815,  -815,  2994,  5320,   183,  -815,    32,   385,  9465,   594,
     415,   376,    32,   158,   310,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,   857,  -815,  -815,  -815,  -815,  -815,  1694,  -815,
    -815,  -815,  -815,  -815,   662,  -815,   643,  8676,  -815,   655,
     751,   671,  -815,   677,   759,   679,   775,  -815,  -815,   808,
    -815,  -815,  -815,  -815,  -815,   481,  -815,  1346,  5461,  -815,
    -815,  5187,    76,  5461,   692,  8331,  -815,   594,  9465,  8791,
    8676,   716,  8791,  8791,  -815,   572,   410,   694,   766,  8791,
    8791,  -815,   572,   410,  -815,  -815,  8446,   829,  -815,   621,
    -815,   829,  -815,  -815,  -815,  -815,   753,    62,  -815,    59,
     191,    32,   154,   192,  8906,   460,  -815,  8906,  4252,   415,
     376,  -815,    32,   753,    71,  1694,  4252,  1694,  6831,  -815,
      61,   219,  -815,  8676,  -815,  -815,  -815,  8676,  8676,   603,
    8676,  8676,   709,    71,  -815,   719,  -815,  -815,  -815,   486,
     857,   526,  -815,   720,    32,  -815,    32,    63,  8676,  1694,
    -815,  -815,    42,  -815,  -815,  -815,    58,  -815,  1694,  -815,
    -815,  1182,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,    32,   737,   749,   732,  9576,  -815,   733,   671,  -815,
     734,   739,  -815,   735,   872,   750,  5187,   874,  8676,   758,
     594,  2994,  8676,  -815,  2994,  -815,  2994,  -815,  -815,  -815,
    8791,  -815,  2994,  -815,  2994,  -815,  -815,   600,  -815,   802,
    -815,  4790,   884,  -815,  8906,   753,  -815,   753,  5461,  5461,
    -815,  8561,  4534,   239,   101,  -815,   460,   753,  -815,  -815,
    -815,    32,   753,   460,  -815,  -815,  -815,  2994,  8676,  7756,
    -815,  -815,    32,  1138,   760,   867,  -815,   762,  5461,  5187,
    -815,  -815,  -815,  -815,   767,   771,  -815,   671,  -815,   780,
    -815,   781,  -815,   780,  5576,   798,  -815,  9576,  1694,  -815,
     864,   708,    42,  -815,  -815,  1694,  -815,  1182,  -815,   876,
    -815,  -815,   793,  -815,   791,  2994,  -815,  2994,  9687,    90,
    -815,  -815,  5461,  -815,  -815,    90,  -815,  -815,   753,   753,
    -815,   598,  -815,  4252,  -815,  -815,  -815,  -815,  -815,   633,
    -815,   806,  1138,   540,  -815,  -815,   933,   812,  1694,  -815,
    1182,  -815,  -815,  1182,  -815,  1182,  -815,  -815,   836,  -815,
     708,  -815,   813,   815,  -815, 10459,  -815,   671,   816,  -815,
     819,   816,  -815,   387,  -815,  -815,  -815,   903,  -815,   712,
     608,   611,   617,  4252,  -815,  4393,  -815,  -815,  -815,  -815,
    -815,  5461,   753,  4252,  1138,   806,  1138,   824,  -815,  -815,
     780,   826,   780,   780,  -815,  1694,  -815,  1182,  -815,   825,
     830,  -815,  1182,  -815,  1182,  -815,  -815,   876,  -815,   675,
   10538,  7296, 10617,   756,   621,   753,  -815,   753,   806,  1138,
    -815,  1182,  -815,  -815,  -815,   816,   833,   816,   816,  -815,
     261,   376,    32,   105,   250,  -815,  -815,  -815,  -815,   806,
     780,  -815,  1182,  -815,  -815,  -815,   274,  -815,   816,  -815
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -815,  -815,  -815,  -401,  -815,    28,  -815,  -573,   920,  -815,
     514,  -815,    31,  -815,  -304,   245,    -6,    30,  -815,  -171,
    -815,   473,    -7,   877,  -156,   -15,   -75,  -815,  -405,    -9,
    1624,  -308,   878,   -52,  -815,   -13,  -815,  -815,    20,  -815,
     800,  -815,   856,  -815,   -72,   259,  -344,    51,    18,  -815,
    -393,  -204,    73,  -815,  -303,   -38,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,    56,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,   241,  -353,  -538,   -49,  -679,
    -815,  -794,  -810,   206,   290,  -712,  -815,  -423,  -815,  -624,
    -815,   -37,  -815,  -815,  -815,  -815,  -815,  -815,   230,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,   -96,  -815,  -815,  -553,
    -815,   -40,  -815,  -815,  -815,  -815,  -815,  -815,   885,  -815,
    -815,  -815,  -815,   688,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,   928,  -815,  -131,  -815,  -815,  -815,  -815,  -815,     3,
    -815,     6,  -815,   -12,  1021,  1331,   892,  1725,  1432,  -815,
    -815,    60,  -815,  -434,  -614,  -315,  -799,   128,   303,  -713,
     400,   113,   218,   100,  -815,  -815,  -815,  -557,  -709,  -814,
     107,   227,  -815,  -633,  -815,   797,  -606,  -815,  -815,  -815,
      85,  -415,  -815,  -339,  -815,   614,   -43,   -26,    34,  -595,
    -239,   -42,    13,    -2
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -628
static const yytype_int16 yytable[] =
{
     119,   235,   402,   238,   318,   286,   327,   618,   573,   211,
     211,   201,   561,   211,   202,   237,   559,   276,   567,   423,
     759,   611,   743,   726,   522,   527,   461,   307,   199,   611,
     463,   201,   120,    71,   202,    71,   259,   725,   842,   660,
     232,   628,   847,   276,   396,   618,   275,   769,   199,   365,
     307,   266,   270,   300,   811,   276,   276,   276,    86,   789,
      86,   792,   601,   941,   639,   787,   883,   215,   225,   588,
     587,   226,   218,   218,   615,   570,   218,   199,   559,   890,
     567,   944,   308,   361,  -105,   691,   364,   316,   693,   217,
     217,   969,   878,   217,   319,  -101,   301,   449,   906,   908,
     650,   223,   223,   570,   489,   223,   631,    86,   314,   315,
     975,   277,   651,   474,   697,   329,   199,   457,  -104,     3,
    -339,  -288,   218,  -102,   458,  -288,   264,   642,   722,   316,
     808,   240,   995,   631,   355,   495,   853,   277,   265,   269,
     654,   655,  -109,  -108,   218,   218,   885,   858,   218,   370,
     381,   381,   877,   490,   686,   891,   399,   655,   480,   475,
     483,   476,   487,  -521,   656,   857,   487,  -339,  -339,   518,
     352,   353,   354,   862,   318,   234,   879,   895,  -513,  -104,
     656,   356,   357,   -95,   496,   883,  1028,   589,   250,  -101,
     585,   969,   680,   317,   586,   -96,   687,  -605,   851,   467,
     944,   903,   904,   304,   400,   305,   -92,   292,   618,   304,
     -92,   305,   451,   307,   234,   416,  -107,  -106,   975,  1049,
     211,   416,   211,   211,   660,   887,  -513,   423,   432,   611,
     611,   304,   765,   305,   -93,   317,   276,   731,   259,   890,
     883,   230,   304,   631,   305,   464,  -104,   321,  -104,   742,
    1006,  1008,   988,  -100,   -99,   631,  1013,   294,  1015,  1016,
    -512,   466,    86,  -106,  -103,   963,   296,   434,   452,   816,
     949,   951,   970,   -95,  -105,   954,   298,   956,   424,   957,
     427,   952,   447,   218,   741,   218,   218,  -103,   276,   218,
     -95,   218,   453,   820,   -95,   454,    86,   -95,   -73,   883,
     217,   -95,   217,   500,   501,   502,   503,    86,  -512,    86,
     259,   660,   223,   660,   223,  1001,   932,   520,   218,   -87,
     436,   576,   307,  1051,  1053,  1054,  1055,   -98,   -97,  -606,
     277,   437,   438,   359,   359,   -97,   499,   359,   591,    71,
     323,   808,  -514,   776,   504,   967,  1059,  -521,   808,   211,
     808,   324,  -515,   513,   432,   681,   574,   575,   523,  -522,
     992,  1011,   681,   328,    86,   218,   218,   218,   218,    86,
     218,   218,  1036,  -101,   852,   -94,  -602,   565,   989,   218,
      58,    86,   277,  -522,   218,  -102,  1030,  1032,  1033,  1034,
    -514,  -106,   233,  -106,   467,   522,   515,   234,   767,  -605,
    -515,   515,  -105,  -517,  -105,   406,   -93,  -603,   756,  -102,
     404,   211,   218,   838,    86,  -103,   432,  -103,   218,   218,
    1027,   565,   233,  -516,   474,   -97,   625,   408,   416,   416,
     861,   276,   863,   218,   602,   604,  1057,  -507,   412,   565,
     119,  -609,   201,  -518,   467,   202,   -97,  1056,   808,   -97,
     808,  -517,  -507,   -97,   618,   808,  -510,   808,   619,   199,
     218,   218,   621,  -294,   211,   565,   414,   624,  -510,   432,
     475,  -516,   476,    71,   218,    76,   611,    76,   433,   413,
     435,   276,  -602,   634,  -507,  -507,   704,   420,  -602,    76,
      76,  -518,   565,    76,   711,   808,   422,   474,    86,   612,
    -507,   482,  -609,   683,  -510,   690,   690,   455,    86,   690,
    -294,  -294,  -433,  -603,  -606,  -510,  -510,   701,   421,  -603,
     440,   460,   474,  1017,    76,   277,   442,   218,   458,   749,
     234,   227,   724,   724,   827,   707,   314,   315,   446,    76,
     417,   835,   637,   475,  -109,   476,   736,  -609,   230,  -609,
    -609,   329,   696,  -605,   359,   359,   359,   359,   756,   505,
     506,    76,    76,   768,  -108,    76,   983,   718,   475,   450,
     476,   477,   985,  -433,   211,   277,   -72,   705,   645,   432,
     646,   647,   648,   649,   474,   712,   211,   418,   419,   707,
     329,   432,   645,   754,   646,   647,   648,   649,   760,   752,
     276,   304,   565,   305,   456,   342,   343,   359,   359,   201,
     416,   444,   202,   841,   565,   577,   707,   474,  -433,   751,
    -433,  -433,   584,   467,  -104,   474,   199,    86,   462,    86,
     475,   119,   476,   479,   828,   844,   841,   218,   474,   465,
     469,   749,   349,   350,   351,   352,   353,   354,   484,   218,
     727,    86,   218,   488,   865,   761,   491,   494,   418,   445,
     276,   813,   873,   475,    71,   476,   481,   784,   509,   784,
     766,   475,   497,   476,   485,   470,   996,  1042,   521,    76,
     577,  -106,   218,   631,   475,   579,   476,   492,   498,    86,
     690,   583,   868,   855,   277,  -519,   864,   620,  -520,   622,
      76,   405,    76,    76,  -284,   707,    76,   762,    76,   580,
     623,   752,   629,    76,   840,   843,   707,   843,  -103,   843,
     -87,   633,   471,   472,    76,   592,    76,  -109,   854,   523,
     638,   856,   823,   825,   682,    76,  -266,   684,   699,   831,
     833,   695,  -519,  -519,    86,  -520,  -520,    86,  -100,    86,
     813,  -284,  -284,  -424,   277,   218,   581,   582,   218,   218,
     416,   698,  -295,   714,   716,   218,   218,   276,   199,   329,
     720,   745,   593,   594,   764,   813,   664,   778,   860,   779,
     775,    76,    76,    76,    76,    76,    76,    76,    76,   515,
     218,   782,   446,   218,    86,   965,    76,   870,    76,  1020,
     805,    76,    86,   785,   709,   784,   784,   786,   876,  -295,
    -295,   790,   724,   788,   934,   791,   213,   213,  -108,   728,
     213,   938,   350,   351,   352,   353,   354,   793,  -267,    76,
    -104,    76,   710,   822,   829,    76,    76,   920,   925,   -99,
     924,   744,   593,   594,   841,   869,  1021,  1022,   247,   249,
      76,   -95,   871,   213,   213,   830,   875,   896,  -106,   276,
     916,   901,   795,   796,   897,   797,   302,   303,   898,   902,
     905,   763,    86,    46,    47,   907,   909,    76,    76,   -97,
     276,  -103,   910,   911,   913,   784,   218,    41,    42,    43,
      44,    76,   918,   922,  -268,   936,   942,    86,   775,   874,
     218,   945,   -94,   948,    86,    86,   940,   950,    86,   645,
     267,   646,   647,   648,   649,    76,   953,   955,   959,   645,
     964,   646,   647,   648,   649,    76,   976,  -269,   972,   843,
     646,   647,   648,   649,    86,    86,   309,   310,   311,   312,
     313,   329,   994,   998,    76,   999,  1004,  1018,   770,  1005,
      86,  1007,  1012,   960,   771,  1014,   342,   343,   770,  1019,
    1029,   664,  1031,  -605,   943,   784,   635,   850,  -606,  1052,
     368,   254,   836,   385,   979,  1046,   872,   800,    86,   359,
    1039,   866,   359,  1045,   859,   493,   403,   290,   397,    86,
     803,   347,   348,   349,   350,   351,   352,   353,   354,   993,
     886,   775,   966,   775,   213,   962,   884,   213,   213,   213,
     302,   805,   598,     0,   211,   805,   707,     0,   805,   432,
     805,   718,   843,   113,     0,   113,     0,   213,     0,   213,
     213,     0,     0,     0,     0,     0,     0,     0,     0,    86,
     329,    86,   565,     0,    76,     0,    76,    86,   664,    86,
     664,     0,     0,     0,    76,   342,   343,     0,     0,     0,
     407,     0,     0,   409,   410,   411,    76,     0,    76,    76,
     775,   997,   113,     0,     0,     0,   278,   218,     0,     0,
       0,     0,   664,     0,     0,     0,   926,   804,   927,   359,
       0,   664,     0,   350,   351,   352,   353,   354,   935,    76,
       0,     0,   278,   937,     0,     0,    76,     0,     0,     0,
       0,     0,     0,     0,   372,   382,   382,   382,   805,     0,
     805,     0,   775,   213,   775,   805,   254,   805,   525,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,     0,   213,   775,     0,     0,
     443,    76,     0,     0,    76,   805,    76,     0,     0,   986,
     987,     0,    76,   254,     0,    76,    76,     0,     0,   514,
       0,     0,    76,    76,   526,     0,     0,     0,   889,     0,
     645,   893,   646,   647,   648,   649,     0,     0,     0,     0,
       0,   803,     0,     0,   603,   605,     0,    76,   803,     0,
      76,    76,   607,   213,   213,     0,     0,     0,   213,    76,
     603,   605,   213,     0,     0,     0,     0,   113,     0,   770,
       0,     0,     0,  1026,   645,     0,   646,   647,   648,   649,
     650,   627,     0,     0,     0,   254,   632,     0,     0,     0,
       0,   664,   651,     0,     0,     0,     0,   213,     0,     0,
     213,   113,     0,     0,     0,     0,  1047,     0,  1048,   608,
     610,   213,   113,   652,   113,     0,     0,     0,   267,     0,
     654,   655,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,     0,     0,     0,   278,     0,   685,     0,     0,
       0,     0,     0,    76,   656,   968,     0,   971,   803,     0,
       0,     0,   213,   610,    76,     0,   267,    76,     0,     0,
       0,    76,    76,     0,     0,    76,     0,     0,     0,   113,
       0,     0,     0,   114,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   278,  1000,     0,
    1002,    76,    76,     0,     0,  1003,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,   694,     0,
       0,     0,     0,     0,     0,     0,     0,   213,     0,   113,
       0,   213,   114,     0,     0,     0,   279,     0,     0,     0,
       0,     0,     0,   213,     0,    76,     0,     0,   645,     0,
     646,   647,   648,   649,   650,  1035,    76,  1037,     0,   213,
       0,     0,   279,     0,  1038,     0,   651,     0,     0,     0,
       0,     0,   213,   213,   373,   383,   383,   383,     0,     0,
       0,  1050,     0,   526,   117,     0,   117,   652,     0,     0,
       0,     0,     0,   653,   654,   655,     0,     0,     0,     0,
       0,     0,  1058,     0,     0,     0,    76,     0,    76,     0,
       0,     0,     0,   113,    76,   755,    76,   213,   656,     0,
       0,   657,     0,   113,     0,     0,     0,     0,   610,   267,
       0,     0,     0,   117,   812,     0,     0,   280,     0,   234,
     278,   719,     0,   721,    76,   213,     0,     0,     0,   607,
     821,     0,   824,   826,     0,     0,     0,     0,     0,   832,
     834,     0,     0,   280,     0,     0,   213,     0,     0,     0,
       0,     0,     0,   781,     0,   374,   384,   384,   645,     0,
     646,   647,   648,   649,   650,     0,     0,   114,     0,     0,
     278,     0,     0,     0,     0,     0,   651,     0,     0,     0,
       0,   819,     0,   867,     0,     0,     0,   824,   826,     0,
     832,   834,     0,     0,     0,     0,     0,   652,     0,     0,
       0,   114,   837,   653,   654,   655,     0,     0,   213,   888,
       0,     0,   114,   888,   114,     0,     0,     0,     0,     0,
       0,     0,   113,     0,   113,     0,     0,     0,   656,     0,
       0,   657,     0,     0,     0,   279,     0,     0,   814,     0,
       0,   815,     0,   817,   658,     0,   113,     0,   213,     0,
       0,     0,   915,     0,     0,     0,    83,     0,    83,     0,
     917,     0,     0,     0,   881,     0,     0,     0,   117,   114,
       0,     0,     0,     0,   114,     0,     0,     0,     0,     0,
       0,   213,     0,     0,   113,     0,   114,   279,     0,   278,
       0,     0,     0,     0,     0,     0,     0,     0,   917,   213,
       0,     0,   117,     0,   914,    83,     0,     0,     0,     0,
       0,     0,     0,   117,     0,   117,     0,     0,     0,   114,
       0,     0,     0,     0,     0,   812,     0,     0,     0,   888,
       0,     0,   812,     0,   812,     0,   280,   930,     0,   113,
       0,     0,   113,     0,   113,     0,     0,   369,     0,   278,
       0,     0,     0,     0,     0,   267,     0,   116,     0,   116,
       0,     0,     0,     0,     0,     0,   912,     0,     0,     0,
     117,     0,     0,     0,     0,   117,   645,     0,   646,   647,
     648,   649,   650,     0,     0,     0,     0,   117,   280,   113,
       0,   921,     0,     0,   651,     0,     0,   113,   928,   929,
       0,     0,   931,   114,     0,     0,   116,     0,     0,     0,
       0,     0,     0,   114,     0,   652,     0,     0,     0,     0,
     117,   653,   654,   655,     0,     0,     0,     0,   946,   947,
     279,     0,   812,     0,   812,     0,     0,     0,     0,   812,
       0,   812,     0,     0,   958,     0,   656,     0,     0,   657,
       0,   213,     0,     0,     0,     0,   382,     0,     0,     0,
      83,     0,     0,     0,     0,     0,     0,   113,     0,     0,
       0,     0,   984,     0,     0,     0,     0,     0,     0,   812,
     279,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   113,     0,    83,     0,     0,     0,     0,   113,
     113,     0,     0,   113,   117,    83,     0,    83,     0,     0,
       0,     0,     0,     0,   117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   113,
     113,   280,   114,  1023,   114,  1024,     0,     0,     0,     0,
       0,  1025,     0,     0,     0,   113,     0,     0,   382,     0,
       0,     0,     0,     0,     0,     0,   114,     0,     0,     0,
       0,   116,    83,     0,     0,     0,     0,    83,     0,   980,
       0,     0,     0,   113,     0,     0,     0,     0,     0,    83,
       0,   280,   524,  -627,   113,     0,     0,     0,     0,     0,
       0,  -627,  -627,  -627,   114,   116,  -627,  -627,  -627,   279,
    -627,     0,     0,     0,     0,     0,   116,     0,   116,  -627,
    -627,     0,    83,     0,     0,     0,     0,     0,     0,     0,
    -627,  -627,     0,  -627,  -627,  -627,  -627,  -627,     0,     0,
       0,     0,     0,   117,   113,   117,   113,     0,     0,     0,
       0,     0,   113,     0,   113,     0,     0,     0,     0,   114,
       0,     0,   114,     0,   114,     0,     0,   117,     0,   279,
       0,     0,     0,   116,     0,     0,     0,     0,   116,     0,
    -627,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,     0,   329,   330,   331,   332,   333,   334,   335,   336,
       0,   338,   339,  -627,     0,   117,    83,   342,   343,   114,
     280,     0,     0,     0,     0,     0,    83,   114,     0,     0,
       0,     0,     0,   116,     0,  -627,  -627,     0,  -627,     0,
       0,   230,  -627,     0,  -627,     0,  -627,     0,     0,     0,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
       0,   799,     0,     0,     0,     0,     0,     0,     0,     0,
     117,     0,     0,   117,   700,   117,     0,     0,     0,     0,
     280,     0,     0,     0,     0,     0,   383,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   114,     0,     0,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,     0,     0,   342,   343,   116,     0,     0,
     117,     0,   114,     0,     0,     0,     0,   116,   117,   114,
     114,     0,     0,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,   344,    83,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,     0,   114,
     114,     0,     0,     0,     0,     0,  -243,     0,     0,    83,
       0,     0,     0,     0,     0,   114,     0,     0,   383,     0,
       0,     0,     0,     0,     0,     0,     0,   384,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   981,
       0,     0,     0,   114,     0,     0,     0,    83,     0,     0,
       0,     0,  -609,     0,   114,     0,     0,     0,     0,     0,
    -609,  -609,  -609,   117,     0,     0,  -609,  -609,     0,  -609,
     117,   117,     0,     0,   117,     0,     0,     0,  -609,     0,
       0,     0,     0,     0,     0,     0,   116,     0,   116,  -609,
    -609,     0,  -609,  -609,  -609,  -609,  -609,     0,     0,     0,
     117,   117,    83,     0,   114,    83,   114,    83,     0,     0,
     116,     0,   114,   524,   114,     0,   117,     0,     0,   384,
       0,     0,  -609,  -609,  -609,  -609,  -609,  -609,  -609,  -609,
    -609,  -609,  -609,  -609,  -609,     0,     0,  -609,  -609,  -609,
     982,   702,     0,     0,   117,     0,     0,     0,   116,     0,
       0,     0,    83,     0,     0,   117,     0,     0,     0,     0,
      83,     0,  -609,     0,     0,     0,     0,  -105,  -609,     0,
    -609,  -609,  -609,  -609,  -609,  -609,  -609,  -609,  -609,  -609,
       0,     0,     0,     0,  -609,  -609,  -609,  -609,   -96,     0,
       0,  -609,     0,  -609,     0,  -609,     0,     0,     0,     0,
       0,     0,     0,   116,     0,   117,   116,   117,   116,     0,
       0,     0,     0,   117,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      83,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,     0,     0,   342,   343,     0,     0,
       0,     0,     0,   116,     0,    83,     0,     0,     0,     0,
       0,   116,    83,    83,     0,     0,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   344,     0,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,     0,
       0,     0,    83,    83,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   234,     0,   554,   555,    83,     0,
     556,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   116,   978,   174,   175,     0,    83,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,    83,     0,     0,
       0,   180,   181,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,   116,   116,     0,     0,   116,     0,     0,
       0,     0,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,     0,   192,   193,     0,     0,     0,     0,     0,
       0,   194,     0,   116,   116,     0,     0,    83,     0,    83,
       0,     0,     0,     0,     0,    83,     0,    83,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -627,     4,     0,     5,     6,     7,     8,     9,
       0,     0,     0,    10,    11,     0,     0,   116,    12,     0,
      13,    14,    15,    16,    17,    18,    19,     0,   116,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,    43,    44,     0,    45,    46,    47,     0,
      48,    49,     0,     0,     0,     0,     0,     0,   116,     0,
     116,     0,     0,     0,     0,     0,   116,     0,   116,     0,
      50,     0,     0,    51,    52,     0,    53,    54,     0,    55,
       0,     0,    56,    57,    58,    59,    60,    61,    62,    63,
      64,  -609,     0,     0,     0,     0,     0,     0,     0,  -609,
    -609,  -609,     0,     0,  -609,  -609,  -609,     0,  -609,     0,
      65,    66,    67,     0,   753,     0,     0,  -609,  -609,  -609,
    -609,     0,     0,  -627,     0,  -627,     0,     0,  -609,  -609,
       0,  -609,  -609,  -609,  -609,  -609,     0,     0,     0,     0,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,     0,     0,   342,   343,     0,     0,     0,
       0,  -609,  -609,  -609,  -609,  -609,  -609,  -609,  -609,  -609,
    -609,  -609,  -609,  -609,     0,     0,  -609,  -609,  -609,     0,
     757,  -609,     0,     0,     0,     0,   344,  -609,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,     0,     0,
       0,  -609,     0,     0,  -609,     0,  -105,  -609,  -609,  -609,
    -609,  -609,  -609,  -609,  -609,  -609,  -609,  -609,  -609,     0,
       0,     0,     0,  -609,  -609,  -609,  -609,  -609,  -507,     0,
    -609,  -609,  -609,     0,  -609,     0,  -507,  -507,  -507,     0,
       0,  -507,  -507,  -507,     0,  -507,     0,     0,     0,     0,
       0,   700,     0,  -507,     0,  -507,  -507,  -507,     0,     0,
       0,     0,     0,     0,     0,  -507,  -507,     0,  -507,  -507,
    -507,  -507,  -507,     0,     0,     0,     0,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
       0,     0,   342,   343,     0,     0,     0,     0,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,     0,     0,  -507,  -507,  -507,     0,  -507,  -507,     0,
       0,     0,     0,   344,  -507,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,     0,     0,     0,  -507,     0,
       0,  -507,     0,  -507,  -507,  -507,  -507,  -507,  -507,  -507,
    -507,  -507,  -507,  -507,  -507,  -507,     0,     0,     0,     0,
       0,  -507,  -507,  -507,  -507,  -510,     0,  -507,  -507,  -507,
       0,  -507,     0,  -510,  -510,  -510,     0,     0,  -510,  -510,
    -510,     0,  -510,     0,     0,     0,     0,     0,     0,     0,
    -510,     0,  -510,  -510,  -510,     0,     0,     0,     0,     0,
       0,     0,  -510,  -510,     0,  -510,  -510,  -510,  -510,  -510,
       0,     0,     0,     0,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,     0,     0,   342,
     343,     0,     0,     0,     0,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,     0,     0,
    -510,  -510,  -510,     0,  -510,  -510,     0,     0,     0,     0,
     344,  -510,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,     0,     0,     0,  -510,     0,     0,  -510,     0,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,     0,     0,     0,     0,     0,  -510,  -510,
    -510,  -510,  -610,     0,  -510,  -510,  -510,     0,  -510,     0,
    -610,  -610,  -610,     0,     0,  -610,  -610,  -610,     0,  -610,
       0,     0,     0,     0,     0,     0,     0,     0,  -610,  -610,
    -610,  -610,     0,     0,     0,     0,     0,     0,     0,  -610,
    -610,     0,  -610,  -610,  -610,  -610,  -610,     0,     0,     0,
       0,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,  -628,  -628,     0,     0,   342,   343,     0,     0,
       0,     0,  -610,  -610,  -610,  -610,  -610,  -610,  -610,  -610,
    -610,  -610,  -610,  -610,  -610,     0,     0,  -610,  -610,  -610,
       0,     0,  -610,     0,     0,     0,     0,     0,  -610,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,     0,
       0,     0,  -610,     0,     0,  -610,     0,     0,  -610,  -610,
    -610,  -610,  -610,  -610,  -610,  -610,  -610,  -610,  -610,  -610,
       0,     0,     0,     0,  -610,  -610,  -610,  -610,  -610,  -611,
       0,  -610,  -610,  -610,     0,  -610,     0,  -611,  -611,  -611,
       0,     0,  -611,  -611,  -611,     0,  -611,     0,     0,     0,
       0,     0,     0,     0,     0,  -611,  -611,  -611,  -611,     0,
       0,     0,     0,     0,     0,     0,  -611,  -611,     0,  -611,
    -611,  -611,  -611,  -611,     0,     0,     0,     0,   329,  -628,
    -628,  -628,  -628,   334,   335,     0,     0,  -628,  -628,     0,
       0,     0,     0,   342,   343,     0,     0,     0,     0,  -611,
    -611,  -611,  -611,  -611,  -611,  -611,  -611,  -611,  -611,  -611,
    -611,  -611,     0,     0,  -611,  -611,  -611,     0,     0,  -611,
       0,     0,     0,     0,     0,  -611,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,     0,     0,     0,  -611,
       0,     0,  -611,     0,     0,  -611,  -611,  -611,  -611,  -611,
    -611,  -611,  -611,  -611,  -611,  -611,  -611,     0,     0,     0,
       0,  -611,  -611,  -611,  -611,  -611,  -294,     0,  -611,  -611,
    -611,     0,  -611,     0,  -294,  -294,  -294,     0,     0,  -294,
    -294,  -294,     0,  -294,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -294,  -294,  -294,     0,     0,     0,     0,
       0,     0,     0,  -294,  -294,     0,  -294,  -294,  -294,  -294,
    -294,     0,     0,     0,     0,   329,   330,   331,   332,   333,
     334,   335,     0,     0,   338,   339,     0,     0,     0,     0,
     342,   343,     0,     0,     0,     0,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,     0,
       0,  -294,  -294,  -294,     0,   758,  -294,     0,     0,     0,
       0,     0,  -294,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,     0,     0,     0,  -294,     0,     0,  -294,
       0,  -107,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,     0,     0,     0,     0,     0,  -294,
    -294,  -294,  -294,  -432,     0,  -294,  -294,  -294,     0,  -294,
       0,  -432,  -432,  -432,     0,     0,  -432,  -432,  -432,     0,
    -432,     0,     0,     0,     0,     0,     0,     0,     0,  -432,
    -432,  -432,     0,     0,     0,     0,     0,     0,     0,     0,
    -432,  -432,     0,  -432,  -432,  -432,  -432,  -432,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,     0,     0,  -432,  -432,
    -432,     0,     0,  -432,     0,     0,     0,     0,     0,  -432,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -432,     0,     0,     0,     0,     0,  -432,
       0,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,     0,     0,     0,     0,  -432,  -432,  -432,  -432,  -432,
    -285,   230,  -432,  -432,  -432,     0,  -432,     0,  -285,  -285,
    -285,     0,     0,  -285,  -285,  -285,     0,  -285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -285,  -285,  -285,
       0,     0,     0,     0,     0,     0,     0,  -285,  -285,     0,
    -285,  -285,  -285,  -285,  -285,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,
    -285,  -285,  -285,     0,     0,  -285,  -285,  -285,     0,     0,
    -285,     0,     0,     0,     0,     0,  -285,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -285,     0,     0,  -285,     0,     0,  -285,  -285,  -285,  -285,
    -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,     0,     0,
       0,     0,     0,  -285,  -285,  -285,  -285,  -422,     0,  -285,
    -285,  -285,     0,  -285,     0,  -422,  -422,  -422,     0,     0,
    -422,  -422,  -422,     0,  -422,     0,     0,     0,     0,     0,
       0,     0,     0,  -422,  -422,  -422,     0,     0,     0,     0,
       0,     0,     0,     0,  -422,  -422,     0,  -422,  -422,  -422,
    -422,  -422,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
       0,     0,  -422,  -422,  -422,     0,     0,  -422,     0,     0,
       0,     0,     0,  -422,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -422,     0,     0,
       0,     0,     0,  -422,     0,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,     0,     0,     0,     0,  -422,
    -422,  -422,  -422,  -422,  -301,  -422,  -422,  -422,  -422,     0,
    -422,     0,  -301,  -301,  -301,     0,     0,  -301,  -301,  -301,
       0,  -301,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -301,  -301,     0,     0,     0,     0,     0,     0,     0,
       0,  -301,  -301,     0,  -301,  -301,  -301,  -301,  -301,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -301,  -301,  -301,  -301,  -301,  -301,
    -301,  -301,  -301,  -301,  -301,  -301,  -301,     0,     0,  -301,
    -301,  -301,     0,     0,  -301,     0,     0,     0,     0,     0,
    -301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -301,     0,     0,     0,     0,     0,
    -301,     0,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,
    -301,  -301,     0,     0,     0,     0,     0,  -301,  -301,  -301,
    -301,  -294,   227,  -301,  -301,  -301,     0,  -301,     0,  -294,
    -294,  -294,     0,     0,     0,  -294,  -294,     0,  -294,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -294,  -294,
       0,  -294,  -294,  -294,  -294,  -294,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,     0,     0,  -294,  -294,  -294,     0,
     703,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -294,     0,     0,     0,     0,  -107,  -294,     0,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,     0,
       0,     0,     0,     0,  -294,  -294,  -294,   -98,     0,     0,
    -294,     0,  -294,   251,  -294,     5,     6,     7,     8,     9,
    -627,  -627,  -627,    10,    11,     0,     0,  -627,    12,     0,
      13,    14,    15,    16,    17,    18,    19,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,    29,   252,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,    43,    44,     0,    45,    46,    47,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,    51,    52,     0,    53,    54,     0,    55,
       0,     0,    56,    57,    58,    59,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,    67,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -627,   251,  -627,     5,     6,     7,     8,
       9,     0,     0,  -627,    10,    11,     0,  -627,  -627,    12,
       0,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,     0,    28,    29,
     252,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,     0,    41,    42,    43,    44,     0,    45,    46,    47,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,     0,    51,    52,     0,    53,    54,     0,
      55,     0,     0,    56,    57,    58,    59,    60,    61,    62,
      63,    64,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -627,   251,  -627,     5,     6,     7,
       8,     9,     0,     0,  -627,    10,    11,     0,     0,  -627,
      12,  -627,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
      29,   252,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,    43,    44,     0,    45,    46,
      47,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,    51,    52,     0,    53,    54,
       0,    55,     0,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    66,    67,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -627,   251,  -627,     5,     6,
       7,     8,     9,     0,     0,  -627,    10,    11,     0,     0,
    -627,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,    29,   252,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,     0,    45,
      46,    47,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,    51,    52,     0,    53,
      54,     0,    55,     0,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       0,   251,     0,     5,     6,     7,     8,     9,     0,  -627,
    -627,    10,    11,    65,    66,    67,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,  -627,     0,  -627,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,   252,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,    51,    52,     0,    53,    54,     0,    55,     0,     0,
      56,    57,    58,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,   251,     0,     5,     6,
       7,     8,     9,     0,     0,     0,    10,    11,    65,    66,
      67,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,  -627,     0,  -627,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,    29,   252,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,     0,    45,
      46,    47,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,   253,    52,     0,    53,
      54,     0,    55,     0,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,     0,     0,     0,     0,
       0,     0,     0,     0,  -627,     0,  -627,   251,  -627,     5,
       6,     7,     8,     9,     0,     0,     0,    10,    11,     0,
       0,     0,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,   252,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,    51,    52,     0,
      53,    54,     0,    55,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,     0,  -627,     0,  -627,   251,  -627,
       5,     6,     7,     8,     9,     0,     0,     0,    10,    11,
       0,     0,     0,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,   252,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,    43,    44,
       0,    45,    46,    47,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,     0,    51,    52,
       0,    53,    54,     0,    55,     0,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,     0,     0,
    -627,     4,     0,     5,     6,     7,     8,     9,  -627,     0,
    -627,    10,    11,     0,     0,     0,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,    51,    52,     0,    53,    54,     0,    55,     0,     0,
      56,    57,    58,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    65,    66,
      67,     0,     0,  -627,     0,     0,     0,     0,     0,     0,
       0,  -627,   251,  -627,     5,     6,     7,     8,     9,     0,
       0,  -627,    10,    11,     0,     0,     0,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,    29,   252,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,    52,     0,    53,    54,     0,    55,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,   251,     0,     5,
       6,     7,     8,     9,     0,     0,     0,    10,    11,    65,
      66,    67,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,  -627,     0,  -627,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,   252,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,    51,    52,     0,
      53,    54,     0,    55,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,  -627,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,    66,    67,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,  -627,     0,  -627,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,   204,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,   207,   208,
     209,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
     210,    67,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,   234,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,     0,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,    66,    67,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,   304,     0,   305,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,     0,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,     0,     0,     0,    10,    11,    65,
      66,    67,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,   234,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,    51,    52,     0,
      53,    54,     0,    55,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,     0,
       0,     0,    10,    11,    65,    66,    67,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,   498,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,    29,   252,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,    52,     0,    53,    54,     0,    55,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   498,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,     0,     0,     0,
     145,   146,   147,   386,   387,   388,   389,   152,   153,   154,
       0,     0,     0,     0,     0,   155,   156,   157,   158,   390,
     391,   392,   393,   163,    37,    38,   394,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   165,   166,
     167,   168,   169,   170,   171,   172,   173,     0,     0,   174,
     175,     0,     0,   176,   177,   178,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,     0,   192,
     193,     0,     0,     0,     0,     0,     0,   194,   395,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,     0,     0,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,     0,     0,     0,     0,
       0,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     283,   284,   164,   285,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,     0,   174,   175,     0,     0,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,     0,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,     0,     0,     0,     0,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   236,     0,   164,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,     0,
     174,   175,     0,     0,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,     0,
     192,   193,     0,     0,     0,     0,     0,     0,   194,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     0,     0,     0,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,     0,     0,     0,     0,
       0,   155,   156,   157,   158,   159,   160,   161,   162,   163,
       0,     0,   164,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,     0,   174,   175,     0,     0,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,     0,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,     0,   194,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,     0,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,     0,     0,     0,     0,   155,   156,   157,   158,
     159,   160,   161,   162,   163,     0,     0,   164,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,     0,
     174,   175,     0,     0,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,     0,
     192,   193,     5,     6,     7,     0,     9,     0,   194,     0,
      10,    11,     0,     0,     0,    12,     0,    13,    14,    15,
     241,   242,    18,    19,     0,     0,     0,     0,     0,   243,
     244,   245,    23,    24,    25,    26,     0,     0,   203,     0,
       0,     0,     0,     0,     0,   271,     0,     0,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
      43,    44,     0,    45,    46,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   272,     0,     0,
     206,    52,     0,    53,    54,     0,     0,     0,     0,    56,
      57,    58,    59,    60,    61,    62,    63,    64,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,     0,     0,     0,    12,   273,    13,    14,
      15,   241,   242,    18,    19,   274,     0,     0,     0,     0,
     243,   244,   245,    23,    24,    25,    26,     0,     0,   203,
       0,     0,     0,     0,     0,     0,   271,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   272,     0,
       0,   206,    52,     0,    53,    54,     0,     0,     0,     0,
      56,    57,    58,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,     0,
       0,     0,    10,    11,     0,     0,     0,    12,   273,    13,
      14,    15,    16,    17,    18,    19,   519,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,    52,     0,    53,    54,     0,    55,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
      66,    67,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,   204,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,   207,   208,   209,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,     0,
       0,     0,    10,    11,    65,   210,    67,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,    29,     0,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,    52,     0,    53,    54,     0,    55,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
      66,    67,    12,     0,    13,    14,    15,   241,   242,    18,
      19,     0,     0,     0,     0,     0,   243,   244,   245,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,   204,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,   609,   208,   209,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,   210,    67,    12,     0,    13,
      14,    15,   241,   242,    18,    19,     0,     0,     0,     0,
       0,   243,   244,   245,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,   204,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,   207,   208,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
     210,    67,    12,     0,    13,    14,    15,   241,   242,    18,
      19,     0,     0,     0,     0,     0,   243,   244,   245,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,   204,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,     0,   208,   209,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,   210,    67,    12,     0,    13,
      14,    15,   241,   242,    18,    19,     0,     0,     0,     0,
       0,   243,   244,   245,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,   204,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,   609,   208,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
     210,    67,    12,     0,    13,    14,    15,   241,   242,    18,
      19,     0,     0,     0,     0,     0,   243,   244,   245,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,   204,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,     0,   208,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,   210,    67,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,   512,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
     210,    67,    12,     0,    13,    14,    15,   241,   242,    18,
      19,     0,     0,     0,     0,     0,   243,   244,   245,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,   207,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,   210,    67,    12,     0,    13,
      14,    15,   241,   242,    18,    19,     0,     0,     0,     0,
       0,   243,   244,   245,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,   818,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
     210,    67,    12,     0,    13,    14,    15,   241,   242,    18,
      19,     0,     0,     0,     0,     0,   243,   244,   245,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,   512,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,   210,    67,    12,     0,    13,
      14,    15,   241,   242,    18,    19,     0,     0,     0,     0,
       0,   243,   244,   245,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,   609,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
     210,    67,    12,     0,    13,    14,    15,   241,   242,    18,
      19,     0,     0,     0,     0,     0,   243,   244,   245,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,     0,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,   210,    67,    12,     0,    13,
      14,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,     0,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
     210,    67,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,     0,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,    66,    67,    12,     0,    13,
      14,    15,   241,   242,    18,    19,     0,     0,     0,     0,
       0,   243,   244,   245,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,   271,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   272,
       0,     0,   325,    52,     0,    53,    54,     0,   326,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,     0,     0,     0,    12,   273,
      13,    14,    15,   241,   242,    18,    19,     0,     0,     0,
       0,     0,   243,   244,   245,    23,    24,    25,    26,     0,
       0,   203,     0,     0,     0,     0,     0,     0,   271,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,    43,    44,     0,    45,    46,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     367,     0,     0,    51,    52,     0,    53,    54,     0,    55,
       0,     0,    56,    57,    58,    59,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,     0,     0,     0,    12,
     273,    13,    14,    15,   241,   242,    18,    19,     0,     0,
       0,     0,     0,   243,   244,   245,    23,    24,    25,    26,
       0,     0,   203,     0,     0,     0,     0,     0,     0,   271,
       0,     0,    32,    33,    34,   375,    36,    37,    38,   376,
      40,     0,    41,    42,    43,    44,     0,    45,    46,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   377,     0,
       0,   378,     0,     0,   206,    52,     0,    53,    54,     0,
       0,     0,     0,    56,    57,    58,    59,    60,    61,    62,
      63,    64,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,     0,     0,     0,
      12,   273,    13,    14,    15,   241,   242,    18,    19,     0,
       0,     0,     0,     0,   243,   244,   245,    23,    24,    25,
      26,     0,     0,   203,     0,     0,     0,     0,     0,     0,
     271,     0,     0,    32,    33,    34,   375,    36,    37,    38,
     376,    40,     0,    41,    42,    43,    44,     0,    45,    46,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   378,     0,     0,   206,    52,     0,    53,    54,
       0,     0,     0,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,     0,     0,
       0,    12,   273,    13,    14,    15,   241,   242,    18,    19,
       0,     0,     0,     0,     0,   243,   244,   245,    23,    24,
      25,    26,     0,     0,   203,     0,     0,     0,     0,     0,
       0,   271,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,     0,    45,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   272,     0,     0,   325,    52,     0,    53,
      54,     0,     0,     0,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,     0,
       0,     0,    12,   273,    13,    14,    15,   241,   242,    18,
      19,     0,     0,     0,     0,     0,   243,   244,   245,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,   271,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   900,     0,     0,   206,    52,     0,
      53,    54,     0,     0,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
       0,     0,     0,    12,   273,    13,    14,    15,   241,   242,
      18,    19,     0,     0,     0,     0,     0,   243,   244,   245,
      23,    24,    25,    26,     0,     0,   203,     0,     0,     0,
       0,     0,     0,   271,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,    43,    44,
       0,    45,    46,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   977,     0,     0,   206,    52,
       0,    53,    54,     0,     0,     0,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     0,     0,     0,     0,
     562,   563,     0,     0,   564,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   273,   165,   166,   167,   168,
     169,   170,   171,   172,   173,     0,     0,   174,   175,     0,
       0,   176,   177,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,     0,   192,   193,   599,
     563,     0,     0,   600,     0,   194,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   165,   166,   167,   168,   169,
     170,   171,   172,   173,     0,     0,   174,   175,     0,     0,
     176,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,     0,   192,   193,   613,   555,
       0,     0,   614,     0,   194,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,     0,   174,   175,     0,     0,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,     0,   192,   193,   616,   563,     0,
       0,   617,     0,   194,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165,   166,   167,   168,   169,   170,   171,
     172,   173,     0,     0,   174,   175,     0,     0,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,     0,   192,   193,   640,   555,     0,     0,
     641,     0,   194,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     0,     0,   174,   175,     0,     0,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,     0,   192,   193,   643,   563,     0,     0,   644,
       0,   194,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   165,   166,   167,   168,   169,   170,   171,   172,   173,
       0,     0,   174,   175,     0,     0,   176,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,     0,   192,   193,   729,   555,     0,     0,   730,     0,
     194,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     165,   166,   167,   168,   169,   170,   171,   172,   173,     0,
       0,   174,   175,     0,     0,   176,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
       0,   192,   193,   732,   563,     0,     0,   733,     0,   194,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,     0,
     174,   175,     0,     0,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,     0,
     192,   193,   739,   555,     0,     0,   740,     0,   194,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   165,   166,
     167,   168,   169,   170,   171,   172,   173,     0,     0,   174,
     175,     0,     0,   176,   177,   178,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,     0,   192,
     193,  1009,   555,     0,     0,  1010,     0,   194,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   165,   166,   167,
     168,   169,   170,   171,   172,   173,     0,     0,   174,   175,
       0,     0,   176,   177,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,     0,   192,   193,
    1040,   555,     0,     0,  1041,     0,   194,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   165,   166,   167,   168,
     169,   170,   171,   172,   173,     0,     0,   174,   175,     0,
       0,   176,   177,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,     0,   192,   193,  1043,
     563,     0,     0,  1044,     0,   194,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   165,   166,   167,   168,   169,
     170,   171,   172,   173,     0,     0,   174,   175,     0,     0,
     176,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,     0,   192,   193,     0,     0,
       0,     0,     0,     0,   194
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-815)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-628)))

static const yytype_int16 yycheck[] =
{
       2,    27,    98,    29,    76,    57,    81,   422,   361,    16,
      17,     8,   356,    20,     8,    28,   355,    55,   357,   223,
     615,   414,   595,   576,   328,   328,   265,    69,     8,   422,
     269,    28,     4,     2,    28,     4,    51,   575,   717,   473,
      22,   442,   721,    81,    96,   460,    55,   642,    28,    92,
      92,    53,    54,    65,   687,    93,    94,    95,     2,   673,
       4,   675,   401,   873,   469,   671,   779,    16,    17,     1,
     378,    20,    16,    17,   418,    13,    20,    57,   417,   788,
     419,   875,    69,    89,    25,   508,    92,    26,   511,    16,
      17,   905,    29,    20,    76,    25,    66,   253,   810,   811,
      58,    16,    17,    13,    63,    20,   445,    51,    37,    38,
     909,    55,    70,    63,   519,    70,    96,   136,    13,     0,
      87,   139,    66,    25,   143,   143,    53,   471,    27,    26,
     687,   132,   942,   472,    87,    63,   731,    81,    53,    54,
      98,    99,    25,    25,    88,    89,   779,   742,    92,    93,
      94,    95,   776,   112,    78,   788,    87,    99,   289,   109,
     291,   111,   293,    89,   122,   738,   297,   134,   135,   325,
     125,   126,   127,   746,   246,   143,   113,   801,    87,    25,
     122,   134,   135,    25,   112,   898,   996,   119,    56,   115,
      52,  1005,   142,   132,    56,   136,   120,   138,   136,   274,
     994,   807,   808,   141,   135,   143,   136,   142,   623,   141,
     136,   143,   255,   255,   143,   217,    25,    25,  1017,  1029,
     227,   223,   229,   230,   658,   782,   135,   431,   230,   622,
     623,   141,   633,   143,   136,   132,   274,   581,   253,   948,
     953,   138,   141,   582,   143,   271,   141,    28,   143,   593,
     962,   963,   931,   136,   136,   594,   968,   142,   970,   971,
      87,   273,   206,    13,    25,   898,   142,   233,   255,   692,
     884,   885,   905,   115,    13,   889,   142,   891,   227,   893,
     229,   887,   251,   227,   592,   229,   230,    13,   326,   233,
     136,   235,   258,   698,   136,   261,   240,   139,   115,  1012,
     227,   143,   229,   309,   310,   311,   312,   251,   135,   253,
     325,   745,   227,   747,   229,   948,   854,   326,   262,   136,
      54,   364,   364,  1035,  1036,  1037,  1038,   136,   136,   138,
     274,    65,    66,    88,    89,    25,   308,    92,   380,   308,
     115,   898,    87,   658,   313,   902,  1058,    89,   905,   356,
     907,   136,    87,   323,   356,   486,   362,   363,   328,    89,
     933,   967,   493,   115,   308,   309,   310,   311,   312,   313,
     314,   315,  1005,   115,   727,   136,    26,   357,   931,   323,
     102,   325,   326,    89,   328,   115,  1000,  1001,  1002,  1003,
     135,   141,   138,   143,   469,   699,   323,   143,   637,   138,
     135,   328,   141,    87,   143,   136,   136,    26,   612,   115,
      89,   418,   356,   716,   358,   141,   418,   143,   362,   363,
     993,   401,   138,    87,    63,   115,   439,    56,   430,   431,
     745,   469,   747,   377,   404,   405,  1050,    87,   115,   419,
     442,    26,   439,    87,   519,   439,   136,  1042,  1005,   139,
    1007,   135,    87,   143,   869,  1012,    87,  1014,   424,   439,
     404,   405,   428,    87,   471,   445,   136,   433,    87,   471,
     109,   135,   111,   442,   418,     2,   869,     4,   233,    90,
     235,   519,   132,   449,   134,   135,   558,    89,   138,    16,
      17,   135,   472,    20,   566,  1052,   136,    63,   442,   414,
     135,    67,    87,   142,   135,   507,   508,   262,   452,   511,
     134,   135,    26,   132,   138,   134,   135,   543,    89,   138,
     138,   136,    63,   136,    51,   469,   132,   471,   143,   601,
     143,   138,   574,   575,   705,   561,    37,    38,    89,    66,
      87,   712,   457,   109,   115,   111,   588,   132,   138,   134,
     135,    70,   518,   138,   309,   310,   311,   312,   762,   314,
     315,    88,    89,   638,   115,    92,   919,   569,   109,   139,
     111,   112,   925,    87,   581,   519,   115,   559,    52,   581,
      54,    55,    56,    57,    63,   567,   593,   134,   135,   615,
      70,   593,    52,   606,    54,    55,    56,    57,    89,   601,
     638,   141,   582,   143,   140,    85,    86,   362,   363,   606,
     612,    87,   606,    15,   594,    17,   642,    63,   132,   601,
     134,   135,   377,   698,   115,    63,   606,   571,   133,   573,
     109,   633,   111,   112,   706,    14,    15,   581,    63,    56,
     136,   713,   122,   123,   124,   125,   126,   127,   112,   593,
     577,   595,   596,   112,   750,    89,   112,   112,   134,   135,
     698,   687,   136,   109,   633,   111,   112,   669,    96,   671,
     636,   109,    70,   111,   112,    87,   136,  1021,   136,   206,
      17,   115,   626,  1022,   109,    56,   111,   112,   141,   633,
     692,    25,    89,   735,   638,    87,   748,   139,    87,   136,
     227,    89,   229,   230,    87,   731,   233,   622,   235,    87,
     136,   713,   133,   240,   716,   717,   742,   719,   115,   721,
     136,   132,   134,   135,   251,    87,   253,   115,   734,   699,
     136,   737,   702,   703,   142,   262,   136,   142,   115,   709,
     710,   136,   134,   135,   688,   134,   135,   691,   136,   693,
     776,   134,   135,   138,   698,   699,   134,   135,   702,   703,
     762,   136,    87,    10,     8,   709,   710,   805,   748,    70,
      13,   138,   134,   135,   133,   801,   473,   115,   744,   136,
     652,   308,   309,   310,   311,   312,   313,   314,   315,   716,
     734,   136,    89,   737,   738,    87,   323,   763,   325,    87,
     687,   328,   746,    52,    89,   807,   808,   136,   774,   134,
     135,    52,   854,   136,   856,   136,    16,    17,   115,   578,
      20,   863,   123,   124,   125,   126,   127,    52,   136,   356,
     115,   358,    89,   117,   140,   362,   363,   839,   844,   136,
     842,   596,   134,   135,    15,   136,   134,   135,    48,    49,
     377,   136,   133,    53,    54,    89,   136,   120,   115,   897,
     830,   805,    54,    55,   115,    57,    66,    67,   136,   136,
     136,   626,   816,    65,    66,   136,   141,   404,   405,   136,
     918,   115,    10,   133,    10,   887,   830,    59,    60,    61,
      62,   418,    90,     9,   136,   861,   136,   841,   770,   771,
     844,   139,   136,   136,   848,   849,   872,   136,   852,    52,
      54,    54,    55,    56,    57,   442,   136,   136,   120,    52,
      56,    54,    55,    56,    57,   452,   133,   136,    52,   931,
      54,    55,    56,    57,   878,   879,    40,    41,    42,    43,
      44,    70,   136,    10,   471,   133,   110,   973,    91,   136,
     894,   136,   136,   897,    97,   136,    85,    86,    91,    56,
     136,   658,   136,   138,    97,   967,   452,   726,   138,   136,
      93,    51,   713,    95,   918,  1024,   770,   687,   922,   734,
    1017,   751,   737,  1023,   743,   297,   101,    59,    96,   933,
     687,   120,   121,   122,   123,   124,   125,   126,   127,   939,
     782,   873,   902,   875,   204,   898,   779,   207,   208,   209,
     210,   898,   398,    -1,  1021,   902,  1042,    -1,   905,  1021,
     907,  1023,  1024,     2,    -1,     4,    -1,   227,    -1,   229,
     230,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   983,
      70,   985,  1022,    -1,   571,    -1,   573,   991,   745,   993,
     747,    -1,    -1,    -1,   581,    85,    86,    -1,    -1,    -1,
     204,    -1,    -1,   207,   208,   209,   593,    -1,   595,   596,
     942,   943,    51,    -1,    -1,    -1,    55,  1021,    -1,    -1,
      -1,    -1,   779,    -1,    -1,    -1,   845,   687,   847,   844,
      -1,   788,    -1,   123,   124,   125,   126,   127,   857,   626,
      -1,    -1,    81,   862,    -1,    -1,   633,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    94,    95,    96,  1005,    -1,
    1007,    -1,   994,   323,   996,  1012,   206,  1014,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,    -1,   356,  1029,    -1,    -1,
     240,   688,    -1,    -1,   691,  1052,   693,    -1,    -1,   928,
     929,    -1,   699,   253,    -1,   702,   703,    -1,    -1,   323,
      -1,    -1,   709,   710,   328,    -1,    -1,    -1,   788,    -1,
      52,   791,    54,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,   898,    -1,    -1,   404,   405,    -1,   734,   905,    -1,
     737,   738,   412,   413,   414,    -1,    -1,    -1,   418,   746,
     420,   421,   422,    -1,    -1,    -1,    -1,   206,    -1,    91,
      -1,    -1,    -1,   992,    52,    -1,    54,    55,    56,    57,
      58,   441,    -1,    -1,    -1,   325,   446,    -1,    -1,    -1,
      -1,   948,    70,    -1,    -1,    -1,    -1,   457,    -1,    -1,
     460,   240,    -1,    -1,    -1,    -1,  1025,    -1,  1027,   413,
     414,   471,   251,    91,   253,    -1,    -1,    -1,   422,    -1,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   816,
      -1,    -1,    -1,    -1,    -1,   274,    -1,   497,    -1,    -1,
      -1,    -1,    -1,   830,   122,   905,    -1,   907,  1005,    -1,
      -1,    -1,   512,   457,   841,    -1,   460,   844,    -1,    -1,
      -1,   848,   849,    -1,    -1,   852,    -1,    -1,    -1,   308,
      -1,    -1,    -1,     2,   313,     4,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   325,   326,   948,    -1,
     950,   878,   879,    -1,    -1,   955,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   894,   512,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   577,    -1,   358,
      -1,   581,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,   593,    -1,   922,    -1,    -1,    52,    -1,
      54,    55,    56,    57,    58,  1005,   933,  1007,    -1,   609,
      -1,    -1,    81,    -1,  1014,    -1,    70,    -1,    -1,    -1,
      -1,    -1,   622,   623,    93,    94,    95,    96,    -1,    -1,
      -1,  1031,    -1,   577,     2,    -1,     4,    91,    -1,    -1,
      -1,    -1,    -1,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,  1052,    -1,    -1,    -1,   983,    -1,   985,    -1,
      -1,    -1,    -1,   442,   991,   609,   993,   667,   122,    -1,
      -1,   125,    -1,   452,    -1,    -1,    -1,    -1,   622,   623,
      -1,    -1,    -1,    51,   687,    -1,    -1,    55,    -1,   143,
     469,   571,    -1,   573,  1021,   695,    -1,    -1,    -1,   699,
     700,    -1,   702,   703,    -1,    -1,    -1,    -1,    -1,   709,
     710,    -1,    -1,    81,    -1,    -1,   716,    -1,    -1,    -1,
      -1,    -1,    -1,   667,    -1,    93,    94,    95,    52,    -1,
      54,    55,    56,    57,    58,    -1,    -1,   206,    -1,    -1,
     519,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,   695,    -1,   753,    -1,    -1,    -1,   757,   758,    -1,
     760,   761,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      -1,   240,   716,    97,    98,    99,    -1,    -1,   778,   782,
      -1,    -1,   251,   786,   253,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   571,    -1,   573,    -1,    -1,    -1,   122,    -1,
      -1,   125,    -1,    -1,    -1,   274,    -1,    -1,   688,    -1,
      -1,   691,    -1,   693,   138,    -1,   595,    -1,   818,    -1,
      -1,    -1,   822,    -1,    -1,    -1,     2,    -1,     4,    -1,
     830,    -1,    -1,    -1,   778,    -1,    -1,    -1,   206,   308,
      -1,    -1,    -1,    -1,   313,    -1,    -1,    -1,    -1,    -1,
      -1,   851,    -1,    -1,   633,    -1,   325,   326,    -1,   638,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   868,   869,
      -1,    -1,   240,    -1,   818,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   251,    -1,   253,    -1,    -1,    -1,   358,
      -1,    -1,    -1,    -1,    -1,   898,    -1,    -1,    -1,   902,
      -1,    -1,   905,    -1,   907,    -1,   274,   851,    -1,   688,
      -1,    -1,   691,    -1,   693,    -1,    -1,    93,    -1,   698,
      -1,    -1,    -1,    -1,    -1,   869,    -1,     2,    -1,     4,
      -1,    -1,    -1,    -1,    -1,    -1,   816,    -1,    -1,    -1,
     308,    -1,    -1,    -1,    -1,   313,    52,    -1,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,   325,   326,   738,
      -1,   841,    -1,    -1,    70,    -1,    -1,   746,   848,   849,
      -1,    -1,   852,   442,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,   452,    -1,    91,    -1,    -1,    -1,    -1,
     358,    97,    98,    99,    -1,    -1,    -1,    -1,   878,   879,
     469,    -1,  1005,    -1,  1007,    -1,    -1,    -1,    -1,  1012,
      -1,  1014,    -1,    -1,   894,    -1,   122,    -1,    -1,   125,
      -1,  1021,    -1,    -1,    -1,    -1,   805,    -1,    -1,    -1,
     206,    -1,    -1,    -1,    -1,    -1,    -1,   816,    -1,    -1,
      -1,    -1,   922,    -1,    -1,    -1,    -1,    -1,    -1,  1052,
     519,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   841,    -1,   240,    -1,    -1,    -1,    -1,   848,
     849,    -1,    -1,   852,   442,   251,    -1,   253,    -1,    -1,
      -1,    -1,    -1,    -1,   452,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   878,
     879,   469,   571,   983,   573,   985,    -1,    -1,    -1,    -1,
      -1,   991,    -1,    -1,    -1,   894,    -1,    -1,   897,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   595,    -1,    -1,    -1,
      -1,   206,   308,    -1,    -1,    -1,    -1,   313,    -1,   918,
      -1,    -1,    -1,   922,    -1,    -1,    -1,    -1,    -1,   325,
      -1,   519,   328,     0,   933,    -1,    -1,    -1,    -1,    -1,
      -1,     8,     9,    10,   633,   240,    13,    14,    15,   638,
      17,    -1,    -1,    -1,    -1,    -1,   251,    -1,   253,    26,
      27,    -1,   358,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,   571,   983,   573,   985,    -1,    -1,    -1,
      -1,    -1,   991,    -1,   993,    -1,    -1,    -1,    -1,   688,
      -1,    -1,   691,    -1,   693,    -1,    -1,   595,    -1,   698,
      -1,    -1,    -1,   308,    -1,    -1,    -1,    -1,   313,    -1,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     325,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    79,    80,   110,    -1,   633,   442,    85,    86,   738,
     638,    -1,    -1,    -1,    -1,    -1,   452,   746,    -1,    -1,
      -1,    -1,    -1,   358,    -1,   132,   133,    -1,   135,    -1,
      -1,   138,   139,    -1,   141,    -1,   143,    -1,    -1,    -1,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      -1,   679,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     688,    -1,    -1,   691,    44,   693,    -1,    -1,    -1,    -1,
     698,    -1,    -1,    -1,    -1,    -1,   805,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   816,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    86,   442,    -1,    -1,
     738,    -1,   841,    -1,    -1,    -1,    -1,   452,   746,   848,
     849,    -1,    -1,   852,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   571,   116,   573,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    -1,   878,
     879,    -1,    -1,    -1,    -1,    -1,   136,    -1,    -1,   595,
      -1,    -1,    -1,    -1,    -1,   894,    -1,    -1,   897,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   805,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   816,   918,
      -1,    -1,    -1,   922,    -1,    -1,    -1,   633,    -1,    -1,
      -1,    -1,     0,    -1,   933,    -1,    -1,    -1,    -1,    -1,
       8,     9,    10,   841,    -1,    -1,    14,    15,    -1,    17,
     848,   849,    -1,    -1,   852,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   571,    -1,   573,    37,
      38,    -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,
     878,   879,   688,    -1,   983,   691,   985,   693,    -1,    -1,
     595,    -1,   991,   699,   993,    -1,   894,    -1,    -1,   897,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    86,    87,
     918,    89,    -1,    -1,   922,    -1,    -1,    -1,   633,    -1,
      -1,    -1,   738,    -1,    -1,   933,    -1,    -1,    -1,    -1,
     746,    -1,   110,    -1,    -1,    -1,    -1,   115,   116,    -1,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      -1,    -1,    -1,    -1,   132,   133,   134,   135,   136,    -1,
      -1,   139,    -1,   141,    -1,   143,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   688,    -1,   983,   691,   985,   693,    -1,
      -1,    -1,    -1,   991,    -1,   993,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     816,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,   738,    -1,   841,    -1,    -1,    -1,    -1,
      -1,   746,   848,   849,    -1,    -1,   852,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
      -1,    -1,   878,   879,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   143,    -1,    52,    53,   894,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,   816,   918,    79,    80,    -1,   922,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,   933,    -1,    -1,
      -1,    97,    98,    -1,    -1,    -1,   841,    -1,    -1,    -1,
      -1,    -1,    -1,   848,   849,    -1,    -1,   852,    -1,    -1,
      -1,    -1,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,   129,   130,    -1,    -1,    -1,    -1,    -1,
      -1,   137,    -1,   878,   879,    -1,    -1,   983,    -1,   985,
      -1,    -1,    -1,    -1,    -1,   991,    -1,   993,    -1,   894,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     0,     1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    12,    -1,    -1,   922,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,   933,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    62,    -1,    64,    65,    66,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,   983,    -1,
     985,    -1,    -1,    -1,    -1,    -1,   991,    -1,   993,    -1,
      88,    -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,     0,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
       9,    10,    -1,    -1,    13,    14,    15,    -1,    17,    -1,
     128,   129,   130,    -1,    44,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,   141,    -1,   143,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    86,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    87,    -1,
      89,    90,    -1,    -1,    -1,    -1,   116,    96,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    -1,    -1,
      -1,   110,    -1,    -1,   113,    -1,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
      -1,    -1,    -1,   132,   133,   134,   135,   136,     0,    -1,
     139,   140,   141,    -1,   143,    -1,     8,     9,    10,    -1,
      -1,    13,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    25,    -1,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    -1,    85,    86,    87,    -1,    89,    90,    -1,
      -1,    -1,    -1,   116,    96,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,    -1,    -1,   110,    -1,
      -1,   113,    -1,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,
      -1,   133,   134,   135,   136,     0,    -1,   139,   140,   141,
      -1,   143,    -1,     8,     9,    10,    -1,    -1,    13,    14,
      15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    -1,
      85,    86,    87,    -1,    89,    90,    -1,    -1,    -1,    -1,
     116,    96,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,    -1,    -1,   110,    -1,    -1,   113,    -1,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    -1,    -1,    -1,    -1,    -1,   133,   134,
     135,   136,     0,    -1,   139,   140,   141,    -1,   143,    -1,
       8,     9,    10,    -1,    -1,    13,    14,    15,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    86,    87,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
      -1,    -1,   110,    -1,    -1,   113,    -1,    -1,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      -1,    -1,    -1,    -1,   132,   133,   134,   135,   136,     0,
      -1,   139,   140,   141,    -1,   143,    -1,     8,     9,    10,
      -1,    -1,    13,    14,    15,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    -1,    -1,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    85,    86,    87,    -1,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    96,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,    -1,   110,
      -1,    -1,   113,    -1,    -1,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    -1,    -1,    -1,
      -1,   132,   133,   134,   135,   136,     0,    -1,   139,   140,
     141,    -1,   143,    -1,     8,     9,    10,    -1,    -1,    13,
      14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      -1,    85,    86,    87,    -1,    89,    90,    -1,    -1,    -1,
      -1,    -1,    96,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    -1,    -1,    -1,   110,    -1,    -1,   113,
      -1,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,   133,
     134,   135,   136,     0,    -1,   139,   140,   141,    -1,   143,
      -1,     8,     9,    10,    -1,    -1,    13,    14,    15,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,    85,    86,
      87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,   116,
      -1,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,    -1,    -1,    -1,    -1,   132,   133,   134,   135,   136,
       0,   138,   139,   140,   141,    -1,   143,    -1,     8,     9,
      10,    -1,    -1,    13,    14,    15,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    85,    86,    87,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110,    -1,    -1,   113,    -1,    -1,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    -1,    -1,
      -1,    -1,    -1,   133,   134,   135,   136,     0,    -1,   139,
     140,   141,    -1,   143,    -1,     8,     9,    10,    -1,    -1,
      13,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    85,    86,    87,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,
      -1,    -1,    -1,   116,    -1,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,   132,
     133,   134,   135,   136,     0,   138,   139,   140,   141,    -1,
     143,    -1,     8,     9,    10,    -1,    -1,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      86,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,    -1,    -1,
     116,    -1,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,    -1,    -1,    -1,    -1,   133,   134,   135,
     136,     0,   138,   139,   140,   141,    -1,   143,    -1,     8,
       9,    10,    -1,    -1,    -1,    14,    15,    -1,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,    -1,    -1,    -1,    -1,   115,   116,    -1,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
      -1,    -1,    -1,    -1,   133,   134,   135,   136,    -1,    -1,
     139,    -1,   141,     1,   143,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    15,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    62,    -1,    64,    65,    66,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     128,   129,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,     1,   143,     3,     4,     5,     6,
       7,    -1,    -1,    10,    11,    12,    -1,    14,    15,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    62,    -1,    64,    65,    66,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    91,    92,    -1,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   128,   129,   130,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,     1,   143,     3,     4,     5,
       6,     7,    -1,    -1,    10,    11,    12,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    -1,    64,    65,
      66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    91,    92,    -1,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   128,   129,   130,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,     1,   143,     3,     4,
       5,     6,     7,    -1,    -1,    10,    11,    12,    -1,    -1,
      15,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    62,    -1,    64,
      65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,   128,   129,   130,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,   141,    -1,   143,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    12,   128,   129,
     130,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,   141,    -1,   143,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    62,    -1,    64,
      65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   128,   129,   130,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,   141,     1,   143,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   128,   129,   130,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    -1,   141,     1,   143,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,
      -1,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,   129,   130,    -1,    -1,
     133,     1,    -1,     3,     4,     5,     6,     7,   141,    -1,
     143,    11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,   129,
     130,    -1,    -1,   133,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,     1,   143,     3,     4,     5,     6,     7,    -1,
      -1,    10,    11,    12,    -1,    -1,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,   141,    -1,   143,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,   141,    -1,   143,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,   143,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    -1,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,   141,    -1,   143,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    -1,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,   143,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,   141,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,
     129,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   141,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    79,
      80,    -1,    -1,    83,    84,    85,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    -1,   129,
     130,    -1,    -1,    -1,    -1,    -1,    -1,   137,   138,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,   129,   130,    -1,    -1,    -1,
      -1,    -1,    -1,   137,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,    -1,    -1,    83,    84,    85,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    98,
      -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
     129,   130,    -1,    -1,    -1,    -1,    -1,    -1,   137,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    97,    98,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,   129,   130,    -1,    -1,    -1,
      -1,    -1,    -1,   137,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,    -1,    -1,    83,    84,    85,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
     129,   130,     3,     4,     5,    -1,     7,    -1,   137,    -1,
      11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      91,    92,    -1,    94,    95,    -1,    -1,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,    -1,    -1,    -1,    16,   128,    18,    19,
      20,    21,    22,    23,    24,   136,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    91,    92,    -1,    94,    95,    -1,    -1,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    16,   128,    18,
      19,    20,    21,    22,    23,    24,   136,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    98,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    98,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    -1,    98,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    -1,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    -1,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   128,
     129,   130,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    -1,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   128,   129,   130,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,   128,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    62,    -1,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    91,    92,    -1,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,
     128,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    62,    -1,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,
      -1,    88,    -1,    -1,    91,    92,    -1,    94,    95,    -1,
      -1,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,   128,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    -1,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    -1,    91,    92,    -1,    94,    95,
      -1,    -1,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,   128,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    62,    -1,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,    94,
      95,    -1,    -1,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    16,   128,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,    -1,
      94,    95,    -1,    -1,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,   128,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    91,    92,
      -1,    94,    95,    -1,    -1,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,    -1,    -1,    -1,    -1,
      52,    53,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    -1,    -1,    79,    80,    -1,
      -1,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,   129,   130,    52,
      53,    -1,    -1,    56,    -1,   137,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,
      83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,   129,   130,    52,    53,
      -1,    -1,    56,    -1,   137,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,   129,   130,    52,    53,    -1,
      -1,    56,    -1,   137,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    79,    80,    -1,    -1,    83,    84,
      85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    -1,   129,   130,    52,    53,    -1,    -1,
      56,    -1,   137,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    -1,    -1,    79,    80,    -1,    -1,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,   129,   130,    52,    53,    -1,    -1,    56,
      -1,   137,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      -1,    -1,    79,    80,    -1,    -1,    83,    84,    85,    86,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,    -1,   129,   130,    52,    53,    -1,    -1,    56,    -1,
     137,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -1,
      -1,    79,    80,    -1,    -1,    83,    84,    85,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      -1,   129,   130,    52,    53,    -1,    -1,    56,    -1,   137,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,    -1,    -1,    83,    84,    85,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    98,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
     129,   130,    52,    53,    -1,    -1,    56,    -1,   137,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    79,
      80,    -1,    -1,    83,    84,    85,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    98,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    -1,   129,
     130,    52,    53,    -1,    -1,    56,    -1,   137,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    79,    80,
      -1,    -1,    83,    84,    85,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    -1,   129,   130,
      52,    53,    -1,    -1,    56,    -1,   137,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    -1,    -1,    79,    80,    -1,
      -1,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,   129,   130,    52,
      53,    -1,    -1,    56,    -1,   137,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,
      83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,   129,   130,    -1,    -1,
      -1,    -1,    -1,    -1,   137
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   145,   146,     0,     1,     3,     4,     5,     6,     7,
      11,    12,    16,    18,    19,    20,    21,    22,    23,    24,
      30,    31,    32,    33,    34,    35,    36,    39,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    59,    60,    61,    62,    64,    65,    66,    68,    69,
      88,    91,    92,    94,    95,    97,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   128,   129,   130,   147,   148,
     149,   156,   158,   159,   161,   162,   165,   166,   167,   169,
     170,   171,   173,   174,   184,   199,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   254,   255,   269,
     270,   271,   272,   273,   274,   275,   278,   280,   281,   293,
     295,   296,   297,   298,   299,   300,   301,   302,   336,   347,
     149,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    56,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    79,    80,    83,    84,    85,    86,
      97,    98,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   129,   130,   137,   177,   178,   179,   180,   182,
     183,   293,   295,    39,    58,    88,    91,    97,    98,    99,
     129,   166,   174,   184,   186,   191,   194,   196,   218,   298,
     299,   301,   302,   334,   335,   191,   191,   138,   192,   193,
     138,   188,   192,   138,   143,   341,    54,   179,   341,   150,
     132,    21,    22,    30,    31,    32,   165,   184,   218,   184,
      56,     1,    47,    91,   152,   153,   154,   156,   168,   169,
     347,   201,   202,   187,   196,   334,   347,   186,   333,   334,
     347,    46,    88,   128,   136,   173,   199,   218,   298,   299,
     302,   246,   247,    54,    55,    57,   177,   285,   294,   284,
     285,   286,   142,   276,   142,   282,   142,   279,   142,   283,
     297,   161,   184,   184,   141,   143,   340,   345,   346,    40,
      41,    42,    43,    44,    37,    38,    26,   132,   188,   192,
     260,    28,   252,   115,   136,    91,    97,   170,   115,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    85,    86,   116,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    87,   134,   135,   200,   159,
     160,   160,   205,   207,   160,   340,   346,    88,   167,   174,
     218,   234,   298,   299,   302,    52,    56,    85,    88,   175,
     176,   218,   298,   299,   302,   176,    33,    34,    35,    36,
      49,    50,    51,    52,    56,   138,   177,   300,   331,    87,
     135,   339,   260,   272,    89,    89,   136,   186,    56,   186,
     186,   186,   115,    90,   136,   195,   347,    87,   134,   135,
      89,    89,   136,   195,   191,   341,   342,   191,   190,   191,
     196,   334,   347,   159,   342,   159,    54,    65,    66,   157,
     138,   185,   132,   152,    87,   135,    89,   156,   155,   168,
     139,   340,   346,   342,   342,   159,   140,   136,   143,   344,
     136,   344,   133,   344,   341,    56,   297,   170,   172,   136,
      87,   134,   135,   248,    63,   109,   111,   112,   287,   112,
     287,   112,    67,   287,   112,   112,   277,   287,   112,    63,
     112,   112,   112,   277,   112,    63,   112,    70,   141,   149,
     160,   160,   160,   160,   156,   159,   159,   262,   261,    96,
     163,   253,    97,   161,   186,   196,   197,   198,   168,   136,
     173,   136,   158,   161,   174,   184,   186,   198,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,    52,    53,    56,   182,   259,   337,
     338,   190,    52,    53,    56,   182,   258,   337,   151,   152,
      13,   230,   345,   230,   160,   160,   340,    17,   263,    56,
      87,   134,   135,    25,   159,    52,    56,   175,     1,   119,
     303,   345,    87,   134,   135,   214,   332,   215,   339,    52,
      56,   337,   161,   184,   161,   184,   181,   184,   186,    97,
     186,   194,   334,    52,    56,   190,    52,    56,   335,   342,
     139,   342,   136,   136,   342,   179,   204,   184,   147,   133,
     337,   337,   184,   132,   342,   154,   203,   334,   136,   172,
      52,    56,   190,    52,    56,    52,    54,    55,    56,    57,
      58,    70,    91,    97,    98,    99,   122,   125,   138,   250,
     307,   309,   310,   311,   312,   313,   314,   315,   316,   319,
     320,   321,   322,   325,   326,   327,   328,   329,   289,   288,
     142,   287,   142,   142,   142,   184,    78,   120,   241,   242,
     347,   241,   164,   241,   186,   136,   342,   172,   136,   115,
      44,   341,    89,    89,   188,   192,   257,   341,   343,    89,
      89,   188,   192,   256,    10,   229,     8,   265,   347,   152,
      13,   152,    27,   231,   345,   231,   263,   196,   229,    52,
      56,   190,    52,    56,   209,   212,   345,   304,   211,    52,
      56,   175,   190,   151,   159,   138,   305,   306,   216,   188,
     189,   192,   347,    44,   179,   186,   195,    89,    89,   343,
      89,    89,   334,   159,   133,   147,   342,   344,   170,   343,
      91,    97,   235,   236,   237,   311,   309,   249,   115,   136,
     308,   186,   136,   330,   347,    52,   136,   330,   136,   308,
      52,   136,   308,    52,   290,    54,    55,    57,   292,   302,
     238,   240,   243,   312,   314,   315,   317,   318,   321,   323,
     324,   327,   329,   341,   152,   152,   241,   152,    97,   186,
     172,   184,   117,   161,   184,   161,   184,   163,   188,   140,
      89,   161,   184,   161,   184,   163,   189,   186,   198,   266,
     347,    15,   233,   347,    14,   232,   233,   233,   206,   208,
     229,   136,   230,   343,   160,   345,   160,   151,   343,   229,
     342,   309,   151,   309,   177,   260,   252,   184,    89,   136,
     342,   133,   237,   136,   311,   136,   342,   243,    29,   113,
     251,   186,   307,   313,   325,   327,   316,   321,   329,   314,
     322,   327,   312,   314,   291,   243,   120,   115,   136,   239,
      88,   218,   136,   330,   330,   136,   239,   136,   239,   141,
      10,   133,   152,    10,   186,   184,   161,   184,    90,   267,
     347,   152,     9,   268,   347,   160,   229,   229,   152,   152,
     186,   152,   231,   213,   345,   229,   342,   229,   345,   217,
     342,   236,   136,    97,   235,   139,   152,   152,   136,   308,
     136,   308,   330,   136,   308,   136,   308,   308,   152,   120,
     218,   238,   324,   327,    56,    87,   317,   321,   314,   323,
     327,   314,    52,   244,   245,   310,   133,    88,   174,   218,
     298,   299,   302,   230,   152,   230,   229,   229,   233,   263,
     264,   210,   151,   305,   136,   236,   136,   311,    10,   133,
     314,   327,   314,   314,   110,   136,   239,   136,   239,    52,
      56,   330,   136,   239,   136,   239,   239,   136,   341,    56,
      87,   134,   135,   152,   152,   152,   229,   151,   236,   136,
     308,   136,   308,   308,   308,   314,   327,   314,   314,   245,
      52,    56,   190,    52,    56,   265,   232,   229,   229,   236,
     314,   239,   136,   239,   239,   239,   343,   308,   314,   239
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      parser_yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, parser)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, parser); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct parser_params *parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct parser_params *parser;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct parser_params *parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct parser_params *parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, struct parser_params *parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, parser)
    YYSTYPE *yyvsp;
    int yyrule;
    struct parser_params *parser;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parser); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
#ifndef yydebug
int yydebug;
#endif
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct parser_params *parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    struct parser_params *parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (struct parser_params *parser)
#else
int
yyparse (parser)
    struct parser_params *parser;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 859 "ripper.y"
    {
			lex_state = EXPR_BEG;
#if 0
			local_push(compile_for_eval || rb_parse_in_main());
#endif
			local_push(0);

		    }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 868 "ripper.y"
    {
#if 0
			if ((yyvsp[(2) - (2)].val) && !compile_for_eval) {
			    /* last expression should not be void */
			    if (nd_type((yyvsp[(2) - (2)].val)) != NODE_BLOCK) void_expr((yyvsp[(2) - (2)].val));
			    else {
				NODE *node = (yyvsp[(2) - (2)].val);
				while (node->nd_next) {
				    node = node->nd_next;
				}
				void_expr(node->nd_head);
			    }
			}
			ruby_eval_tree = NEW_SCOPE(0, block_append(ruby_eval_tree, (yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = (yyvsp[(2) - (2)].val);
			parser->result = dispatch1(program, (yyval.val));

			local_pop();
		    }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 891 "ripper.y"
    {
#if 0
			void_stmts((yyvsp[(1) - (2)].val));
			fixup_nodes(&deferred_nodes);
#endif

			(yyval.val) = (yyvsp[(1) - (2)].val);
		    }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 902 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch2(stmts_add, dispatch0(stmts_new),
						  dispatch0(void_stmt));

		    }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 911 "ripper.y"
    {
#if 0
			(yyval.val) = newline_node((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch2(stmts_add, dispatch0(stmts_new), (yyvsp[(1) - (1)].val));

		    }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 919 "ripper.y"
    {
#if 0
			(yyval.val) = block_append((yyvsp[(1) - (3)].val), newline_node((yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = dispatch2(stmts_add, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 927 "ripper.y"
    {
			(yyval.val) = remove_begin((yyvsp[(2) - (2)].val));
		    }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 934 "ripper.y"
    {
#if 0
			/* local_push(0); */
#endif

		    }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 941 "ripper.y"
    {
#if 0
			ruby_eval_tree_begin = block_append(ruby_eval_tree_begin,
							    (yyvsp[(4) - (5)].val));
			/* NEW_PREEXE($4)); */
			/* local_pop(); */
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(BEGIN, (yyvsp[(4) - (5)].val));

		    }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 958 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (4)].val);
			if ((yyvsp[(2) - (4)].val)) {
			    (yyval.val) = NEW_RESCUE((yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val));
			}
			else if ((yyvsp[(3) - (4)].val)) {
			    rb_warn0("else without rescue is useless");
			    (yyval.val) = block_append((yyval.val), (yyvsp[(3) - (4)].val));
			}
			if ((yyvsp[(4) - (4)].val)) {
			    if ((yyval.val)) {
				(yyval.val) = NEW_ENSURE((yyval.val), (yyvsp[(4) - (4)].val));
			    }
			    else {
				(yyval.val) = block_append((yyvsp[(4) - (4)].val), NEW_NIL());
			    }
			}
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch4(bodystmt,
				       escape_Qundef((yyvsp[(1) - (4)].val)),
				       escape_Qundef((yyvsp[(2) - (4)].val)),
				       escape_Qundef((yyvsp[(3) - (4)].val)),
				       escape_Qundef((yyvsp[(4) - (4)].val)));

		    }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 988 "ripper.y"
    {
#if 0
			void_stmts((yyvsp[(1) - (2)].val));
			fixup_nodes(&deferred_nodes);
#endif

			(yyval.val) = (yyvsp[(1) - (2)].val);
		    }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 999 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch2(stmts_add, dispatch0(stmts_new),
						  dispatch0(void_stmt));

		    }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 1008 "ripper.y"
    {
#if 0
			(yyval.val) = newline_node((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch2(stmts_add, dispatch0(stmts_new), (yyvsp[(1) - (1)].val));

		    }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 1016 "ripper.y"
    {
#if 0
			(yyval.val) = block_append((yyvsp[(1) - (3)].val), newline_node((yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = dispatch2(stmts_add, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 1024 "ripper.y"
    {
			(yyval.val) = remove_begin((yyvsp[(2) - (2)].val));
		    }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 1030 "ripper.y"
    {
			(yyval.val) = (yyvsp[(1) - (1)].val);
		    }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 1034 "ripper.y"
    {
			yyerror("BEGIN is permitted only at toplevel");
#if 0
			/* local_push(0); */
#endif

		    }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 1042 "ripper.y"
    {
#if 0
			ruby_eval_tree_begin = block_append(ruby_eval_tree_begin,
							    (yyvsp[(4) - (5)].val));
			/* NEW_PREEXE($4)); */
			/* local_pop(); */
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(BEGIN, (yyvsp[(4) - (5)].val));

		    }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 1054 "ripper.y"
    {lex_state = EXPR_FNAME;}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 1055 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ALIAS((yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch2(alias, (yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 1063 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_VALIAS((yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(var_alias, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 1071 "ripper.y"
    {
#if 0
			char buf[2];
			buf[0] = '$';
			buf[1] = (char)(yyvsp[(3) - (3)].val)->nd_nth;
			(yyval.val) = NEW_VALIAS((yyvsp[(2) - (3)].val), rb_intern2(buf, 2));
#endif
			(yyval.val) = dispatch2(var_alias, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 1082 "ripper.y"
    {
#if 0
			yyerror("can't make alias for the number variables");
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch2(var_alias, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
			(yyval.val) = dispatch1(alias_error, (yyval.val));

		    }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 1092 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(undef, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 1100 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_IF(cond((yyvsp[(3) - (3)].val)), remove_begin((yyvsp[(1) - (3)].val)), 0);
			fixpos((yyval.val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(if_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 1109 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_UNLESS(cond((yyvsp[(3) - (3)].val)), remove_begin((yyvsp[(1) - (3)].val)), 0);
			fixpos((yyval.val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(unless_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 1118 "ripper.y"
    {
#if 0
			if ((yyvsp[(1) - (3)].val) && nd_type((yyvsp[(1) - (3)].val)) == NODE_BEGIN) {
			    (yyval.val) = NEW_WHILE(cond((yyvsp[(3) - (3)].val)), (yyvsp[(1) - (3)].val)->nd_body, 0);
			}
			else {
			    (yyval.val) = NEW_WHILE(cond((yyvsp[(3) - (3)].val)), (yyvsp[(1) - (3)].val), 1);
			}
#endif
			(yyval.val) = dispatch2(while_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 1131 "ripper.y"
    {
#if 0
			if ((yyvsp[(1) - (3)].val) && nd_type((yyvsp[(1) - (3)].val)) == NODE_BEGIN) {
			    (yyval.val) = NEW_UNTIL(cond((yyvsp[(3) - (3)].val)), (yyvsp[(1) - (3)].val)->nd_body, 0);
			}
			else {
			    (yyval.val) = NEW_UNTIL(cond((yyvsp[(3) - (3)].val)), (yyvsp[(1) - (3)].val), 1);
			}
#endif
			(yyval.val) = dispatch2(until_mod, (yyvsp[(3) - (3)].val), (yyvsp[(1) - (3)].val));

		    }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 1144 "ripper.y"
    {
#if 0
			NODE *resq = NEW_RESBODY(0, remove_begin((yyvsp[(3) - (3)].val)), 0);
			(yyval.val) = NEW_RESCUE(remove_begin((yyvsp[(1) - (3)].val)), resq, 0);
#endif
			(yyval.val) = dispatch2(rescue_mod, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 1153 "ripper.y"
    {
			if (in_def || in_single) {
			    rb_warn0("END in method; use at_exit");
			}
#if 0
			(yyval.val) = NEW_POSTEXE(NEW_NODE(
			    NODE_SCOPE, 0 /* tbl */, (yyvsp[(3) - (4)].val) /* body */, 0 /* args */));
#endif
			(yyval.val) = dispatch1(END, (yyvsp[(3) - (4)].val));

		    }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 1166 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = dispatch2(massign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 1176 "ripper.y"
    {
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = new_op_assign((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
		    }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 1181 "ripper.y"
    {
#if 0
			NODE *args;

			value_expr((yyvsp[(6) - (6)].val));
			if (!(yyvsp[(3) - (6)].val)) (yyvsp[(3) - (6)].val) = NEW_ZARRAY();
			args = arg_concat((yyvsp[(3) - (6)].val), (yyvsp[(6) - (6)].val));
			if ((yyvsp[(5) - (6)].val) == tOROP) {
			    (yyvsp[(5) - (6)].val) = 0;
			}
			else if ((yyvsp[(5) - (6)].val) == tANDOP) {
			    (yyvsp[(5) - (6)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN1((yyvsp[(1) - (6)].val), (yyvsp[(5) - (6)].val), args);
			fixpos((yyval.val), (yyvsp[(1) - (6)].val));
#endif
			(yyval.val) = dispatch2(aref_field, (yyvsp[(1) - (6)].val), escape_Qundef((yyvsp[(3) - (6)].val)));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));

		    }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 1202 "ripper.y"
    {
			value_expr((yyvsp[(5) - (5)].val));
			(yyval.val) = new_attr_op_assign((yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
		    }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 1207 "ripper.y"
    {
			value_expr((yyvsp[(5) - (5)].val));
			(yyval.val) = new_attr_op_assign((yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
		    }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 1212 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON2((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val));
			(yyval.val) = new_const_op_assign((yyval.val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
#endif
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));

		    }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 1222 "ripper.y"
    {
			value_expr((yyvsp[(5) - (5)].val));
			(yyval.val) = new_attr_op_assign((yyvsp[(1) - (5)].val), ripper_intern("::"), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
		    }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 1227 "ripper.y"
    {
#if 0
			rb_backref_error((yyvsp[(1) - (3)].val));
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch2(assign, dispatch1(var_field, (yyvsp[(1) - (3)].val)), (yyvsp[(3) - (3)].val));
			(yyval.val) = dispatch1(assign_error, (yyval.val));

		    }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 1237 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = node_assign((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 1246 "ripper.y"
    {
#if 0
			(yyvsp[(1) - (3)].val)->nd_value = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = dispatch2(massign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 1258 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = node_assign((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 1267 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = node_assign((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 1280 "ripper.y"
    {
#if 0
			(yyval.val) = logop(NODE_AND, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("and"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 1288 "ripper.y"
    {
#if 0
			(yyval.val) = logop(NODE_OR, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("or"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 1296 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op(cond((yyvsp[(3) - (3)].val)), '!');
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("not"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 1304 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op(cond((yyvsp[(2) - (2)].val)), '!');
#endif
			(yyval.val) = dispatch2(unary, ripper_id2sym('!'), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 1315 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		        if (!(yyval.val)) (yyval.val) = NEW_NIL();
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 1332 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val));
			(yyval.val) = method_arg((yyval.val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 1343 "ripper.y"
    {
			(yyvsp[(1) - (1)].vars) = dyna_push();
#if 0
			(yyval.num) = ruby_sourceline;
#endif

		    }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 1353 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ITER((yyvsp[(3) - (5)].val),(yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(2) - (5)].num));
#endif
			(yyval.val) = dispatch2(brace_block, escape_Qundef((yyvsp[(3) - (5)].val)), (yyvsp[(4) - (5)].val));

			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 1365 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_FCALL((yyvsp[(1) - (1)].val), 0);
			nd_set_line((yyval.val), tokline);
#endif

		    }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 1375 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (2)].val);
			(yyval.val)->nd_args = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch2(command, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 1384 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(2) - (3)].val),(yyvsp[(3) - (3)].val));
			(yyvsp[(1) - (3)].val)->nd_args = (yyvsp[(2) - (3)].val);
		        (yyvsp[(3) - (3)].val)->nd_iter = (yyvsp[(1) - (3)].val);
			(yyval.val) = (yyvsp[(3) - (3)].val);
			fixpos((yyval.val), (yyvsp[(1) - (3)].val));
#endif
			(yyval.val) = dispatch2(command, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 1397 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (4)].val), ripper_id2sym('.'), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 1406 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(4) - (5)].val),(yyvsp[(5) - (5)].val));
		        (yyvsp[(5) - (5)].val)->nd_iter = NEW_CALL((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = (yyvsp[(5) - (5)].val);
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(5) - (5)].val));

		   }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 1418 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (4)].val), ripper_intern("::"), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 1427 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(4) - (5)].val),(yyvsp[(5) - (5)].val));
		        (yyvsp[(5) - (5)].val)->nd_iter = NEW_CALL((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = (yyvsp[(5) - (5)].val);
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (5)].val), ripper_intern("::"), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(5) - (5)].val));

		   }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 1439 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SUPER((yyvsp[(2) - (2)].val));
			fixpos((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(super, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 1448 "ripper.y"
    {
#if 0
			(yyval.val) = new_yield((yyvsp[(2) - (2)].val));
			fixpos((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(yield, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 1457 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_RETURN(ret_args((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(return, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 1465 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BREAK(ret_args((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(break, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 1473 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_NEXT(ret_args((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(next, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 1484 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 1495 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(NEW_LIST((yyvsp[(2) - (3)].val)), 0);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 1505 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 1513 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(list_append((yyvsp[(1) - (2)].val),(yyvsp[(2) - (2)].val)), 0);
#endif
			(yyval.val) = mlhs_add((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 1521 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 1529 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (5)].val), NEW_POSTARG((yyvsp[(3) - (5)].val),(yyvsp[(5) - (5)].val)));
#endif
			(yyvsp[(1) - (5)].val) = mlhs_add_star((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val));
			(yyval.val) = mlhs_add((yyvsp[(1) - (5)].val), (yyvsp[(5) - (5)].val));

		    }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 1538 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (2)].val), -1);
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (2)].val), Qnil);

		    }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 1546 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (4)].val), NEW_POSTARG(-1, (yyvsp[(4) - (4)].val)));
#endif
			(yyvsp[(1) - (4)].val) = mlhs_add_star((yyvsp[(1) - (4)].val), Qnil);
			(yyval.val) = mlhs_add((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 1555 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 1563 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, NEW_POSTARG((yyvsp[(2) - (4)].val),(yyvsp[(4) - (4)].val)));
#endif
			(yyvsp[(2) - (4)].val) = mlhs_add_star(mlhs_new(), (yyvsp[(2) - (4)].val));
			(yyval.val) = mlhs_add((yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 1572 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, -1);
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), Qnil);

		    }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 1580 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, NEW_POSTARG(-1, (yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), Qnil);
			(yyval.val) = mlhs_add((yyval.val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 1592 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 1602 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (2)].val));
#endif
			(yyval.val) = mlhs_add(mlhs_new(), (yyvsp[(1) - (2)].val));

		    }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 1610 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = mlhs_add((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));

		    }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 1620 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = mlhs_add(mlhs_new(), (yyvsp[(1) - (1)].val));

		    }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 1628 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = mlhs_add((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 1638 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
		    }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 1642 "ripper.y"
    {
		        (yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
		    }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 1646 "ripper.y"
    {
#if 0
			(yyval.val) = aryset((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch2(aref_field, (yyvsp[(1) - (4)].val), escape_Qundef((yyvsp[(3) - (4)].val)));

		    }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 1654 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_id2sym('.'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 1662 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 1670 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_id2sym('.'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 1678 "ripper.y"
    {
#if 0
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = NEW_CDECL(0, 0, NEW_COLON2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			if (in_def || in_single) {
			    (yyval.val) = dispatch1(assign_error, (yyval.val));
			}

		    }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 1691 "ripper.y"
    {
#if 0
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = NEW_CDECL(0, 0, NEW_COLON3((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(top_const_field, (yyvsp[(2) - (2)].val));
			if (in_def || in_single) {
			    (yyval.val) = dispatch1(assign_error, (yyval.val));
			}

		    }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 1704 "ripper.y"
    {
#if 0
			rb_backref_error((yyvsp[(1) - (1)].val));
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(var_field, (yyvsp[(1) - (1)].val));
			(yyval.val) = dispatch1(assign_error, (yyval.val));

		    }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 1716 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
#if 0
			if (!(yyval.val)) (yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(var_field, (yyval.val));

		    }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 1725 "ripper.y"
    {
		        (yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
#if 0
		        if (!(yyval.val)) (yyval.val) = NEW_BEGIN(0);
#endif
		        (yyval.val) = dispatch1(var_field, (yyval.val));

		    }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 1734 "ripper.y"
    {
#if 0
			(yyval.val) = aryset((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch2(aref_field, (yyvsp[(1) - (4)].val), escape_Qundef((yyvsp[(3) - (4)].val)));

		    }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 1742 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_id2sym('.'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 1750 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_intern("::"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 1758 "ripper.y"
    {
#if 0
			(yyval.val) = attrset((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(field, (yyvsp[(1) - (3)].val), ripper_id2sym('.'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 1766 "ripper.y"
    {
#if 0
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = NEW_CDECL(0, 0, NEW_COLON2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			if (in_def || in_single) {
			    (yyval.val) = dispatch1(assign_error, (yyval.val));
			}

		    }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 1779 "ripper.y"
    {
#if 0
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.val) = NEW_CDECL(0, 0, NEW_COLON3((yyvsp[(2) - (2)].val)));
#endif
			(yyval.val) = dispatch1(top_const_field, (yyvsp[(2) - (2)].val));
			if (in_def || in_single) {
			    (yyval.val) = dispatch1(assign_error, (yyval.val));
			}

		    }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 1792 "ripper.y"
    {
#if 0
			rb_backref_error((yyvsp[(1) - (1)].val));
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(assign_error, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 1803 "ripper.y"
    {
#if 0
			yyerror("class/module name must be CONSTANT");
#endif
			(yyval.val) = dispatch1(class_name_error, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 1814 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON3((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(top_const_ref, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 1822 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON2(0, (yyval.val));
#endif
			(yyval.val) = dispatch1(const_ref, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 1830 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(const_path_ref, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 1843 "ripper.y"
    {
			lex_state = EXPR_ENDFN;
			(yyval.val) = (yyvsp[(1) - (1)].val);
		    }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 1848 "ripper.y"
    {
			lex_state = EXPR_ENDFN;
#if 0
			(yyval.val) = (yyvsp[(1) - (1)].id);
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 1863 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIT(ID2SYM((yyvsp[(1) - (1)].val)));
#endif
			(yyval.val) = dispatch1(symbol_literal, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 1874 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_UNDEF((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 1881 "ripper.y"
    {lex_state = EXPR_FNAME;}
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 1882 "ripper.y"
    {
#if 0
			(yyval.val) = block_append((yyvsp[(1) - (4)].val), NEW_UNDEF((yyvsp[(4) - (4)].val)));
#endif
			rb_ary_push((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 1891 "ripper.y"
    { ifndef_ripper((yyval.val) = '|'); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 1892 "ripper.y"
    { ifndef_ripper((yyval.val) = '^'); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 1893 "ripper.y"
    { ifndef_ripper((yyval.val) = '&'); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 1894 "ripper.y"
    { ifndef_ripper((yyval.val) = tCMP); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 1895 "ripper.y"
    { ifndef_ripper((yyval.val) = tEQ); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 1896 "ripper.y"
    { ifndef_ripper((yyval.val) = tEQQ); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 1897 "ripper.y"
    { ifndef_ripper((yyval.val) = tMATCH); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 1898 "ripper.y"
    { ifndef_ripper((yyval.val) = tNMATCH); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 1899 "ripper.y"
    { ifndef_ripper((yyval.val) = '>'); }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 1900 "ripper.y"
    { ifndef_ripper((yyval.val) = tGEQ); }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 1901 "ripper.y"
    { ifndef_ripper((yyval.val) = '<'); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 1902 "ripper.y"
    { ifndef_ripper((yyval.val) = tLEQ); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 1903 "ripper.y"
    { ifndef_ripper((yyval.val) = tNEQ); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 1904 "ripper.y"
    { ifndef_ripper((yyval.val) = tLSHFT); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 1905 "ripper.y"
    { ifndef_ripper((yyval.val) = tRSHFT); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 1906 "ripper.y"
    { ifndef_ripper((yyval.val) = '+'); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 1907 "ripper.y"
    { ifndef_ripper((yyval.val) = '-'); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 1908 "ripper.y"
    { ifndef_ripper((yyval.val) = '*'); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 1909 "ripper.y"
    { ifndef_ripper((yyval.val) = '*'); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 1910 "ripper.y"
    { ifndef_ripper((yyval.val) = '/'); }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 1911 "ripper.y"
    { ifndef_ripper((yyval.val) = '%'); }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 1912 "ripper.y"
    { ifndef_ripper((yyval.val) = tPOW); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 1913 "ripper.y"
    { ifndef_ripper((yyval.val) = tDSTAR); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 1914 "ripper.y"
    { ifndef_ripper((yyval.val) = '!'); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 1915 "ripper.y"
    { ifndef_ripper((yyval.val) = '~'); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 1916 "ripper.y"
    { ifndef_ripper((yyval.val) = tUPLUS); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 1917 "ripper.y"
    { ifndef_ripper((yyval.val) = tUMINUS); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 1918 "ripper.y"
    { ifndef_ripper((yyval.val) = tAREF); }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 1919 "ripper.y"
    { ifndef_ripper((yyval.val) = tASET); }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 1920 "ripper.y"
    { ifndef_ripper((yyval.val) = '`'); }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 1938 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = node_assign((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 1947 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (5)].val));
		        (yyvsp[(3) - (5)].val) = NEW_RESCUE((yyvsp[(3) - (5)].val), NEW_RESBODY(0,(yyvsp[(5) - (5)].val),0), 0);
			(yyval.val) = node_assign((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val));
#endif
			(yyval.val) = dispatch2(assign, (yyvsp[(1) - (5)].val), dispatch2(rescue_mod, (yyvsp[(3) - (5)].val), (yyvsp[(5) - (5)].val)));

		    }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 1957 "ripper.y"
    {
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = new_op_assign((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
		    }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 1962 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(3) - (5)].val));
		        (yyvsp[(3) - (5)].val) = NEW_RESCUE((yyvsp[(3) - (5)].val), NEW_RESBODY(0,(yyvsp[(5) - (5)].val),0), 0);
#endif
			(yyvsp[(3) - (5)].val) = dispatch2(rescue_mod, (yyvsp[(3) - (5)].val), (yyvsp[(5) - (5)].val));

			(yyval.val) = new_op_assign((yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val));
		    }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 1972 "ripper.y"
    {
#if 0
			NODE *args;

			value_expr((yyvsp[(6) - (6)].val));
			if (!(yyvsp[(3) - (6)].val)) (yyvsp[(3) - (6)].val) = NEW_ZARRAY();
			if (nd_type((yyvsp[(3) - (6)].val)) == NODE_BLOCK_PASS) {
			    args = NEW_ARGSCAT((yyvsp[(3) - (6)].val), (yyvsp[(6) - (6)].val));
			}
		        else {
			    args = arg_concat((yyvsp[(3) - (6)].val), (yyvsp[(6) - (6)].val));
		        }
			if ((yyvsp[(5) - (6)].val) == tOROP) {
			    (yyvsp[(5) - (6)].val) = 0;
			}
			else if ((yyvsp[(5) - (6)].val) == tANDOP) {
			    (yyvsp[(5) - (6)].val) = 1;
			}
			(yyval.val) = NEW_OP_ASGN1((yyvsp[(1) - (6)].val), (yyvsp[(5) - (6)].val), args);
			fixpos((yyval.val), (yyvsp[(1) - (6)].val));
#endif
			(yyvsp[(1) - (6)].val) = dispatch2(aref_field, (yyvsp[(1) - (6)].val), escape_Qundef((yyvsp[(3) - (6)].val)));
			(yyval.val) = dispatch3(opassign, (yyvsp[(1) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));

		    }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 1998 "ripper.y"
    {
			value_expr((yyvsp[(5) - (5)].val));
			(yyval.val) = new_attr_op_assign((yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
		    }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 2003 "ripper.y"
    {
			value_expr((yyvsp[(5) - (5)].val));
			(yyval.val) = new_attr_op_assign((yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
		    }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 2008 "ripper.y"
    {
			value_expr((yyvsp[(5) - (5)].val));
			(yyval.val) = new_attr_op_assign((yyvsp[(1) - (5)].val), ripper_intern("::"), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
		    }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 2013 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON2((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val));
			(yyval.val) = new_const_op_assign((yyval.val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
#endif
			(yyval.val) = dispatch2(const_path_field, (yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));

		    }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 2023 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON3((yyvsp[(2) - (4)].val));
			(yyval.val) = new_const_op_assign((yyval.val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch1(top_const_field, (yyvsp[(2) - (4)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 2033 "ripper.y"
    {
#if 0
			rb_backref_error((yyvsp[(1) - (3)].val));
			(yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(var_field, (yyvsp[(1) - (3)].val));
			(yyval.val) = dispatch3(opassign, (yyval.val), (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));
			(yyval.val) = dispatch1(assign_error, (yyval.val));

		    }
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 2044 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (3)].val));
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = NEW_DOT2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			if (nd_type((yyvsp[(1) - (3)].val)) == NODE_LIT && FIXNUM_P((yyvsp[(1) - (3)].val)->nd_lit) &&
			    nd_type((yyvsp[(3) - (3)].val)) == NODE_LIT && FIXNUM_P((yyvsp[(3) - (3)].val)->nd_lit)) {
			    deferred_nodes = list_append(deferred_nodes, (yyval.val));
			}
#endif
			(yyval.val) = dispatch2(dot2, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 2058 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (3)].val));
			value_expr((yyvsp[(3) - (3)].val));
			(yyval.val) = NEW_DOT3((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			if (nd_type((yyvsp[(1) - (3)].val)) == NODE_LIT && FIXNUM_P((yyvsp[(1) - (3)].val)->nd_lit) &&
			    nd_type((yyvsp[(3) - (3)].val)) == NODE_LIT && FIXNUM_P((yyvsp[(3) - (3)].val)->nd_lit)) {
			    deferred_nodes = list_append(deferred_nodes, (yyval.val));
			}
#endif
			(yyval.val) = dispatch2(dot3, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 2072 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '+', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('+'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 2080 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '-', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('-'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 2088 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '*', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('*'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 2096 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '/', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('/'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 2104 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '%', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('%'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 2112 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tPOW, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("**"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 2120 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL(call_bin_op((yyvsp[(2) - (4)].val), tPOW, (yyvsp[(4) - (4)].val)), tUMINUS, 0);
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(2) - (4)].val), ripper_intern("**"), (yyvsp[(4) - (4)].val));
			(yyval.val) = dispatch2(unary, ripper_intern("-@"), (yyval.val));

		    }
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 2129 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op((yyvsp[(2) - (2)].val), tUPLUS);
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("+@"), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 2137 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op((yyvsp[(2) - (2)].val), tUMINUS);
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("-@"), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 2145 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '|', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('|'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 2153 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '^', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('^'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 2161 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '&', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('&'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 2169 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tCMP, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("<=>"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 224:
/* Line 1787 of yacc.c  */
#line 2177 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '>', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('>'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 2185 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tGEQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern(">="), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 2193 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), '<', (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ID2SYM('<'), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 2201 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tLEQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("<="), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 2209 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tEQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("=="), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 2217 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tEQQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("==="), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 2225 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tNEQ, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("!="), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 2233 "ripper.y"
    {
#if 0
			(yyval.val) = match_op((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
                        if (nd_type((yyvsp[(1) - (3)].val)) == NODE_LIT && RB_TYPE_P((yyvsp[(1) - (3)].val)->nd_lit, T_REGEXP)) {
                            (yyval.val) = reg_named_capture_assign((yyvsp[(1) - (3)].val)->nd_lit, (yyval.val));
                        }
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("=~"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 2244 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tNMATCH, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("!~"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 2252 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op(cond((yyvsp[(2) - (2)].val)), '!');
#endif
			(yyval.val) = dispatch2(unary, ID2SYM('!'), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 2260 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op((yyvsp[(2) - (2)].val), '~');
#endif
			(yyval.val) = dispatch2(unary, ID2SYM('~'), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 2268 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tLSHFT, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("<<"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 2276 "ripper.y"
    {
#if 0
			(yyval.val) = call_bin_op((yyvsp[(1) - (3)].val), tRSHFT, (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern(">>"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 2284 "ripper.y"
    {
#if 0
			(yyval.val) = logop(NODE_AND, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("&&"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 238:
/* Line 1787 of yacc.c  */
#line 2292 "ripper.y"
    {
#if 0
			(yyval.val) = logop(NODE_OR, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch3(binary, (yyvsp[(1) - (3)].val), ripper_intern("||"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 2299 "ripper.y"
    {in_defined = 1;}
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 2300 "ripper.y"
    {
			in_defined = 0;
#if 0
			(yyval.val) = new_defined((yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch1(defined, (yyvsp[(4) - (4)].val));

		    }
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 2309 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (6)].val));
			(yyval.val) = NEW_IF(cond((yyvsp[(1) - (6)].val)), (yyvsp[(3) - (6)].val), (yyvsp[(6) - (6)].val));
			fixpos((yyval.val), (yyvsp[(1) - (6)].val));
#endif
			(yyval.val) = dispatch3(ifop, (yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(6) - (6)].val));

		    }
    break;

  case 242:
/* Line 1787 of yacc.c  */
#line 2319 "ripper.y"
    {
			(yyval.val) = (yyvsp[(1) - (1)].val);
		    }
    break;

  case 243:
/* Line 1787 of yacc.c  */
#line 2325 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		        if (!(yyval.val)) (yyval.val) = NEW_NIL();
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 2338 "ripper.y"
    {
			(yyval.val) = (yyvsp[(1) - (2)].val);
		    }
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 2342 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append((yyvsp[(1) - (4)].val), NEW_HASH((yyvsp[(3) - (4)].val)));
#endif
			(yyval.val) = arg_add_assocs((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val));

		    }
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 2350 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].val)));
#endif
			(yyval.val) = arg_add_assocs(arg_new(), (yyvsp[(1) - (2)].val));

		    }
    break;

  case 248:
/* Line 1787 of yacc.c  */
#line 2360 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(arg_paren, escape_Qundef((yyvsp[(2) - (3)].val)));

		    }
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 2376 "ripper.y"
    {
		      (yyval.val) = (yyvsp[(1) - (2)].val);
		    }
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 2380 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append((yyvsp[(1) - (4)].val), NEW_HASH((yyvsp[(3) - (4)].val)));
#endif
			(yyval.val) = arg_add_assocs((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val));

		    }
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 2388 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].val)));
#endif
			(yyval.val) = arg_add_assocs(arg_new(), (yyvsp[(1) - (2)].val));

		    }
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 2398 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = arg_add(arg_new(), (yyvsp[(1) - (1)].val));

		    }
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 2407 "ripper.y"
    {
#if 0
			(yyval.val) = arg_blk_pass((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = arg_add_optblock((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 2415 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST(NEW_HASH((yyvsp[(1) - (2)].val)));
			(yyval.val) = arg_blk_pass((yyval.val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = arg_add_assocs(arg_new(), (yyvsp[(1) - (2)].val));
			(yyval.val) = arg_add_optblock((yyval.val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 2425 "ripper.y"
    {
#if 0
			(yyval.val) = arg_append((yyvsp[(1) - (4)].val), NEW_HASH((yyvsp[(3) - (4)].val)));
			(yyval.val) = arg_blk_pass((yyval.val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = arg_add_optblock(arg_add_assocs((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val)), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 2436 "ripper.y"
    {
			(yyval.val) = arg_add_block(arg_new(), (yyvsp[(1) - (1)].val));
		    }
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 2442 "ripper.y"
    {
			(yyval.val) = cmdarg_stack;
			CMDARG_PUSH(1);
		    }
    break;

  case 262:
/* Line 1787 of yacc.c  */
#line 2447 "ripper.y"
    {
			/* CMDARG_POP() */
			cmdarg_stack = (yyvsp[(1) - (2)].val);
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    }
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 2455 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BLOCK_PASS((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = (yyvsp[(2) - (2)].val);

		    }
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 2465 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    }
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 2469 "ripper.y"
    {
			(yyval.val) = 0;
		    }
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 2475 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = arg_add(arg_new(), (yyvsp[(1) - (1)].val));

		    }
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 2483 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SPLAT((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = arg_add_star(arg_new(), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 268:
/* Line 1787 of yacc.c  */
#line 2491 "ripper.y"
    {
#if 0
			NODE *n1;
			if ((n1 = splat_array((yyvsp[(1) - (3)].val))) != 0) {
			    (yyval.val) = list_append(n1, (yyvsp[(3) - (3)].val));
			}
			else {
			    (yyval.val) = arg_append((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			}
#endif
			(yyval.val) = arg_add((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 2505 "ripper.y"
    {
#if 0
			NODE *n1;
			if ((nd_type((yyvsp[(4) - (4)].val)) == NODE_ARRAY) && (n1 = splat_array((yyvsp[(1) - (4)].val))) != 0) {
			    (yyval.val) = list_concat(n1, (yyvsp[(4) - (4)].val));
			}
			else {
			    (yyval.val) = arg_concat((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));
			}
#endif
			(yyval.val) = arg_add_star((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 272:
/* Line 1787 of yacc.c  */
#line 2525 "ripper.y"
    {
#if 0
			NODE *n1;
			if ((n1 = splat_array((yyvsp[(1) - (3)].val))) != 0) {
			    (yyval.val) = list_append(n1, (yyvsp[(3) - (3)].val));
			}
			else {
			    (yyval.val) = arg_append((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
			}
#endif
			(yyval.val) = mrhs_add(args2mrhs((yyvsp[(1) - (3)].val)), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 273:
/* Line 1787 of yacc.c  */
#line 2539 "ripper.y"
    {
#if 0
			NODE *n1;
			if (nd_type((yyvsp[(4) - (4)].val)) == NODE_ARRAY &&
			    (n1 = splat_array((yyvsp[(1) - (4)].val))) != 0) {
			    (yyval.val) = list_concat(n1, (yyvsp[(4) - (4)].val));
			}
			else {
			    (yyval.val) = arg_concat((yyvsp[(1) - (4)].val), (yyvsp[(4) - (4)].val));
			}
#endif
			(yyval.val) = mrhs_add_star(args2mrhs((yyvsp[(1) - (4)].val)), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 274:
/* Line 1787 of yacc.c  */
#line 2554 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SPLAT((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = mrhs_add_star(mrhs_new(), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 285:
/* Line 1787 of yacc.c  */
#line 2574 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_FCALL((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = method_arg(dispatch1(fcall, (yyvsp[(1) - (1)].val)), arg_new());

		    }
    break;

  case 286:
/* Line 1787 of yacc.c  */
#line 2582 "ripper.y"
    {
			(yyvsp[(1) - (1)].val) = cmdarg_stack;
			cmdarg_stack = 0;
#if 0
			(yyval.num) = ruby_sourceline;
#endif

		    }
    break;

  case 287:
/* Line 1787 of yacc.c  */
#line 2592 "ripper.y"
    {
			cmdarg_stack = (yyvsp[(1) - (4)].val);
#if 0
			if ((yyvsp[(3) - (4)].val) == NULL) {
			    (yyval.val) = NEW_NIL();
			}
			else {
			    if (nd_type((yyvsp[(3) - (4)].val)) == NODE_RESCUE ||
				nd_type((yyvsp[(3) - (4)].val)) == NODE_ENSURE)
				nd_set_line((yyvsp[(3) - (4)].val), (yyvsp[(2) - (4)].num));
			    (yyval.val) = NEW_BEGIN((yyvsp[(3) - (4)].val));
			}
			nd_set_line((yyval.val), (yyvsp[(2) - (4)].num));
#endif
			(yyval.val) = dispatch1(begin, (yyvsp[(3) - (4)].val));

		    }
    break;

  case 288:
/* Line 1787 of yacc.c  */
#line 2609 "ripper.y"
    {lex_state = EXPR_ENDARG;}
    break;

  case 289:
/* Line 1787 of yacc.c  */
#line 2610 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(paren, 0);

		    }
    break;

  case 290:
/* Line 1787 of yacc.c  */
#line 2618 "ripper.y"
    {
			(yyvsp[(1) - (1)].val) = cmdarg_stack;
			cmdarg_stack = 0;
		    }
    break;

  case 291:
/* Line 1787 of yacc.c  */
#line 2622 "ripper.y"
    {lex_state = EXPR_ENDARG;}
    break;

  case 292:
/* Line 1787 of yacc.c  */
#line 2623 "ripper.y"
    {
			cmdarg_stack = (yyvsp[(1) - (5)].val);
#if 0
			(yyval.val) = (yyvsp[(3) - (5)].val);
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(3) - (5)].val));

		    }
    break;

  case 293:
/* Line 1787 of yacc.c  */
#line 2632 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 294:
/* Line 1787 of yacc.c  */
#line 2640 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON2((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(const_path_ref, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 295:
/* Line 1787 of yacc.c  */
#line 2648 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_COLON3((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(top_const_ref, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 296:
/* Line 1787 of yacc.c  */
#line 2656 "ripper.y"
    {
#if 0
			if ((yyvsp[(2) - (3)].val) == 0) {
			    (yyval.val) = NEW_ZARRAY(); /* zero length array*/
			}
			else {
			    (yyval.val) = (yyvsp[(2) - (3)].val);
			}
#endif
			(yyval.val) = dispatch1(array, escape_Qundef((yyvsp[(2) - (3)].val)));

		    }
    break;

  case 297:
/* Line 1787 of yacc.c  */
#line 2669 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_HASH((yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = dispatch1(hash, escape_Qundef((yyvsp[(2) - (3)].val)));

		    }
    break;

  case 298:
/* Line 1787 of yacc.c  */
#line 2677 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_RETURN(0);
#endif
			(yyval.val) = dispatch0(return0);

		    }
    break;

  case 299:
/* Line 1787 of yacc.c  */
#line 2685 "ripper.y"
    {
#if 0
			(yyval.val) = new_yield((yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch1(yield, dispatch1(paren, (yyvsp[(3) - (4)].val)));

		    }
    break;

  case 300:
/* Line 1787 of yacc.c  */
#line 2693 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_YIELD(0);
#endif
			(yyval.val) = dispatch1(yield, dispatch1(paren, arg_new()));

		    }
    break;

  case 301:
/* Line 1787 of yacc.c  */
#line 2701 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_YIELD(0);
#endif
			(yyval.val) = dispatch0(yield0);

		    }
    break;

  case 302:
/* Line 1787 of yacc.c  */
#line 2708 "ripper.y"
    {in_defined = 1;}
    break;

  case 303:
/* Line 1787 of yacc.c  */
#line 2709 "ripper.y"
    {
			in_defined = 0;
#if 0
			(yyval.val) = new_defined((yyvsp[(5) - (6)].val));
#endif
			(yyval.val) = dispatch1(defined, (yyvsp[(5) - (6)].val));

		    }
    break;

  case 304:
/* Line 1787 of yacc.c  */
#line 2718 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op(cond((yyvsp[(3) - (4)].val)), '!');
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("not"), (yyvsp[(3) - (4)].val));

		    }
    break;

  case 305:
/* Line 1787 of yacc.c  */
#line 2726 "ripper.y"
    {
#if 0
			(yyval.val) = call_uni_op(cond(NEW_NIL()), '!');
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("not"), Qnil);

		    }
    break;

  case 306:
/* Line 1787 of yacc.c  */
#line 2734 "ripper.y"
    {
#if 0
			(yyvsp[(2) - (2)].val)->nd_iter = (yyvsp[(1) - (2)].val);
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = method_arg(dispatch1(fcall, (yyvsp[(1) - (2)].val)), arg_new());
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 308:
/* Line 1787 of yacc.c  */
#line 2745 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(1) - (2)].val)->nd_args, (yyvsp[(2) - (2)].val));
			(yyvsp[(2) - (2)].val)->nd_iter = (yyvsp[(1) - (2)].val);
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = method_add_block((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 309:
/* Line 1787 of yacc.c  */
#line 2755 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    }
    break;

  case 310:
/* Line 1787 of yacc.c  */
#line 2762 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_IF(cond((yyvsp[(2) - (6)].val)), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val));
			fixpos((yyval.val), (yyvsp[(2) - (6)].val));
#endif
			(yyval.val) = dispatch3(if, (yyvsp[(2) - (6)].val), (yyvsp[(4) - (6)].val), escape_Qundef((yyvsp[(5) - (6)].val)));

		    }
    break;

  case 311:
/* Line 1787 of yacc.c  */
#line 2774 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_UNLESS(cond((yyvsp[(2) - (6)].val)), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val));
			fixpos((yyval.val), (yyvsp[(2) - (6)].val));
#endif
			(yyval.val) = dispatch3(unless, (yyvsp[(2) - (6)].val), (yyvsp[(4) - (6)].val), escape_Qundef((yyvsp[(5) - (6)].val)));

		    }
    break;

  case 312:
/* Line 1787 of yacc.c  */
#line 2782 "ripper.y"
    {COND_PUSH(1);}
    break;

  case 313:
/* Line 1787 of yacc.c  */
#line 2782 "ripper.y"
    {COND_POP();}
    break;

  case 314:
/* Line 1787 of yacc.c  */
#line 2785 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_WHILE(cond((yyvsp[(3) - (7)].val)), (yyvsp[(6) - (7)].val), 1);
			fixpos((yyval.val), (yyvsp[(3) - (7)].val));
#endif
			(yyval.val) = dispatch2(while, (yyvsp[(3) - (7)].val), (yyvsp[(6) - (7)].val));

		    }
    break;

  case 315:
/* Line 1787 of yacc.c  */
#line 2793 "ripper.y"
    {COND_PUSH(1);}
    break;

  case 316:
/* Line 1787 of yacc.c  */
#line 2793 "ripper.y"
    {COND_POP();}
    break;

  case 317:
/* Line 1787 of yacc.c  */
#line 2796 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_UNTIL(cond((yyvsp[(3) - (7)].val)), (yyvsp[(6) - (7)].val), 1);
			fixpos((yyval.val), (yyvsp[(3) - (7)].val));
#endif
			(yyval.val) = dispatch2(until, (yyvsp[(3) - (7)].val), (yyvsp[(6) - (7)].val));

		    }
    break;

  case 318:
/* Line 1787 of yacc.c  */
#line 2807 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CASE((yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val));
			fixpos((yyval.val), (yyvsp[(2) - (5)].val));
#endif
			(yyval.val) = dispatch2(case, (yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val));

		    }
    break;

  case 319:
/* Line 1787 of yacc.c  */
#line 2816 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CASE(0, (yyvsp[(3) - (4)].val));
#endif
			(yyval.val) = dispatch2(case, Qnil, (yyvsp[(3) - (4)].val));

		    }
    break;

  case 320:
/* Line 1787 of yacc.c  */
#line 2824 "ripper.y"
    {COND_PUSH(1);}
    break;

  case 321:
/* Line 1787 of yacc.c  */
#line 2826 "ripper.y"
    {COND_POP();}
    break;

  case 322:
/* Line 1787 of yacc.c  */
#line 2829 "ripper.y"
    {
#if 0
			/*
			 *  for a, b, c in e
			 *  #=>
			 *  e.each{|*x| a, b, c = x
			 *
			 *  for a in e
			 *  #=>
			 *  e.each{|x| a, = x}
			 */
			ID id = internal_id();
			ID *tbl = ALLOC_N(ID, 2);
			NODE *m = NEW_ARGS_AUX(0, 0);
			NODE *args, *scope;

			if (nd_type((yyvsp[(2) - (9)].val)) == NODE_MASGN) {
			    /* if args.length == 1 && args[0].kind_of?(Array)
			     *   args = args[0]
			     * end
			     */
			    NODE *one = NEW_LIST(NEW_LIT(INT2FIX(1)));
			    NODE *zero = NEW_LIST(NEW_LIT(INT2FIX(0)));
			    m->nd_next = block_append(
				NEW_IF(
				    NEW_NODE(NODE_AND,
					     NEW_CALL(NEW_CALL(NEW_DVAR(id), idLength, 0),
						      idEq, one),
					     NEW_CALL(NEW_CALL(NEW_DVAR(id), idAREF, zero),
						      rb_intern("kind_of?"), NEW_LIST(NEW_LIT(rb_cArray))),
					     0),
				    NEW_DASGN_CURR(id,
						   NEW_CALL(NEW_DVAR(id), idAREF, zero)),
				    0),
				node_assign((yyvsp[(2) - (9)].val), NEW_DVAR(id)));

			    args = new_args(m, 0, id, 0, new_args_tail(0, 0, 0));
			}
			else {
			    if (nd_type((yyvsp[(2) - (9)].val)) == NODE_LASGN ||
				nd_type((yyvsp[(2) - (9)].val)) == NODE_DASGN ||
				nd_type((yyvsp[(2) - (9)].val)) == NODE_DASGN_CURR) {
				(yyvsp[(2) - (9)].val)->nd_value = NEW_DVAR(id);
				m->nd_plen = 1;
				m->nd_next = (yyvsp[(2) - (9)].val);
				args = new_args(m, 0, 0, 0, new_args_tail(0, 0, 0));
			    }
			    else {
				m->nd_next = node_assign(NEW_MASGN(NEW_LIST((yyvsp[(2) - (9)].val)), 0), NEW_DVAR(id));
				args = new_args(m, 0, id, 0, new_args_tail(0, 0, 0));
			    }
			}
			scope = NEW_NODE(NODE_SCOPE, tbl, (yyvsp[(8) - (9)].val), args);
			tbl[0] = 1; tbl[1] = id;
			(yyval.val) = NEW_FOR(0, (yyvsp[(5) - (9)].val), scope);
			fixpos((yyval.val), (yyvsp[(2) - (9)].val));
#endif
			(yyval.val) = dispatch3(for, (yyvsp[(2) - (9)].val), (yyvsp[(5) - (9)].val), (yyvsp[(8) - (9)].val));

		    }
    break;

  case 323:
/* Line 1787 of yacc.c  */
#line 2890 "ripper.y"
    {
			if (in_def || in_single)
			    yyerror("class definition in method body");
			local_push(0);
#if 0
			(yyval.num) = ruby_sourceline;
#endif

		    }
    break;

  case 324:
/* Line 1787 of yacc.c  */
#line 2901 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CLASS((yyvsp[(2) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(3) - (6)].val));
			nd_set_line((yyval.val), (yyvsp[(4) - (6)].num));
#endif
			(yyval.val) = dispatch3(class, (yyvsp[(2) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val));

			local_pop();
		    }
    break;

  case 325:
/* Line 1787 of yacc.c  */
#line 2911 "ripper.y"
    {
			(yyval.num) = in_def;
			in_def = 0;
		    }
    break;

  case 326:
/* Line 1787 of yacc.c  */
#line 2916 "ripper.y"
    {
			(yyval.num) = in_single;
			in_single = 0;
			local_push(0);
		    }
    break;

  case 327:
/* Line 1787 of yacc.c  */
#line 2923 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SCLASS((yyvsp[(3) - (8)].val), (yyvsp[(7) - (8)].val));
			fixpos((yyval.val), (yyvsp[(3) - (8)].val));
#endif
			(yyval.val) = dispatch2(sclass, (yyvsp[(3) - (8)].val), (yyvsp[(7) - (8)].val));

			local_pop();
			in_def = (yyvsp[(4) - (8)].num);
			in_single = (yyvsp[(6) - (8)].num);
		    }
    break;

  case 328:
/* Line 1787 of yacc.c  */
#line 2935 "ripper.y"
    {
			if (in_def || in_single)
			    yyerror("module definition in method body");
			local_push(0);
#if 0
			(yyval.num) = ruby_sourceline;
#endif

		    }
    break;

  case 329:
/* Line 1787 of yacc.c  */
#line 2946 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MODULE((yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(3) - (5)].num));
#endif
			(yyval.val) = dispatch2(module, (yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val));

			local_pop();
		    }
    break;

  case 330:
/* Line 1787 of yacc.c  */
#line 2956 "ripper.y"
    {
			(yyval.id) = cur_mid;
			cur_mid = (yyvsp[(2) - (2)].val);
			in_def++;
			local_push(0);
		    }
    break;

  case 331:
/* Line 1787 of yacc.c  */
#line 2965 "ripper.y"
    {
#if 0
			NODE *body = remove_begin((yyvsp[(5) - (6)].val));
			reduce_nodes(&body);
			(yyval.val) = NEW_DEFN((yyvsp[(2) - (6)].val), (yyvsp[(4) - (6)].val), body, NOEX_PRIVATE);
			nd_set_line((yyval.val), (yyvsp[(1) - (6)].num));
#endif
			(yyval.val) = dispatch3(def, (yyvsp[(2) - (6)].val), (yyvsp[(4) - (6)].val), (yyvsp[(5) - (6)].val));

			local_pop();
			in_def--;
			cur_mid = (yyvsp[(3) - (6)].id);
		    }
    break;

  case 332:
/* Line 1787 of yacc.c  */
#line 2978 "ripper.y"
    {lex_state = EXPR_FNAME;}
    break;

  case 333:
/* Line 1787 of yacc.c  */
#line 2979 "ripper.y"
    {
			in_single++;
			lex_state = EXPR_ENDFN; /* force for args */
			local_push(0);
		    }
    break;

  case 334:
/* Line 1787 of yacc.c  */
#line 2987 "ripper.y"
    {
#if 0
			NODE *body = remove_begin((yyvsp[(8) - (9)].val));
			reduce_nodes(&body);
			(yyval.val) = NEW_DEFS((yyvsp[(2) - (9)].val), (yyvsp[(5) - (9)].val), (yyvsp[(7) - (9)].val), body);
			nd_set_line((yyval.val), (yyvsp[(1) - (9)].num));
#endif
			(yyval.val) = dispatch5(defs, (yyvsp[(2) - (9)].val), (yyvsp[(3) - (9)].val), (yyvsp[(5) - (9)].val), (yyvsp[(7) - (9)].val), (yyvsp[(8) - (9)].val));

			local_pop();
			in_single--;
		    }
    break;

  case 335:
/* Line 1787 of yacc.c  */
#line 3000 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_BREAK(0);
#endif
			(yyval.val) = dispatch1(break, arg_new());

		    }
    break;

  case 336:
/* Line 1787 of yacc.c  */
#line 3008 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_NEXT(0);
#endif
			(yyval.val) = dispatch1(next, arg_new());

		    }
    break;

  case 337:
/* Line 1787 of yacc.c  */
#line 3016 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_REDO();
#endif
			(yyval.val) = dispatch0(redo);

		    }
    break;

  case 338:
/* Line 1787 of yacc.c  */
#line 3024 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_RETRY();
#endif
			(yyval.val) = dispatch0(retry);

		    }
    break;

  case 339:
/* Line 1787 of yacc.c  */
#line 3034 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		        if (!(yyval.val)) (yyval.val) = NEW_NIL();
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 340:
/* Line 1787 of yacc.c  */
#line 3046 "ripper.y"
    {
			token_info_push("begin");
		    }
    break;

  case 341:
/* Line 1787 of yacc.c  */
#line 3052 "ripper.y"
    {
			token_info_push("if");
		    }
    break;

  case 342:
/* Line 1787 of yacc.c  */
#line 3058 "ripper.y"
    {
			token_info_push("unless");
		    }
    break;

  case 343:
/* Line 1787 of yacc.c  */
#line 3064 "ripper.y"
    {
			token_info_push("while");
		    }
    break;

  case 344:
/* Line 1787 of yacc.c  */
#line 3070 "ripper.y"
    {
			token_info_push("until");
		    }
    break;

  case 345:
/* Line 1787 of yacc.c  */
#line 3076 "ripper.y"
    {
			token_info_push("case");
		    }
    break;

  case 346:
/* Line 1787 of yacc.c  */
#line 3082 "ripper.y"
    {
			token_info_push("for");
		    }
    break;

  case 347:
/* Line 1787 of yacc.c  */
#line 3088 "ripper.y"
    {
			token_info_push("class");
		    }
    break;

  case 348:
/* Line 1787 of yacc.c  */
#line 3094 "ripper.y"
    {
			token_info_push("module");
		    }
    break;

  case 349:
/* Line 1787 of yacc.c  */
#line 3100 "ripper.y"
    {
			token_info_push("def");
#if 0
			(yyval.num) = ruby_sourceline;
#endif

		    }
    break;

  case 350:
/* Line 1787 of yacc.c  */
#line 3110 "ripper.y"
    {
			token_info_pop("end");
		    }
    break;

  case 351:
/* Line 1787 of yacc.c  */
#line 3118 "ripper.y"
    { (yyval.val) = Qnil; }
    break;

  case 353:
/* Line 1787 of yacc.c  */
#line 3124 "ripper.y"
    { (yyval.val) = (yyvsp[(2) - (2)].val); }
    break;

  case 354:
/* Line 1787 of yacc.c  */
#line 3131 "ripper.y"
    { (yyval.val) = Qnil; }
    break;

  case 357:
/* Line 1787 of yacc.c  */
#line 3140 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_IF(cond((yyvsp[(2) - (5)].val)), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			fixpos((yyval.val), (yyvsp[(2) - (5)].val));
#endif
			(yyval.val) = dispatch3(elsif, (yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val), escape_Qundef((yyvsp[(5) - (5)].val)));

		    }
    break;

  case 359:
/* Line 1787 of yacc.c  */
#line 3152 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(else, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 362:
/* Line 1787 of yacc.c  */
#line 3166 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
#if 0
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyval.val));

		    }
    break;

  case 363:
/* Line 1787 of yacc.c  */
#line 3174 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 364:
/* Line 1787 of yacc.c  */
#line 3184 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = mlhs_add(mlhs_new(), (yyvsp[(1) - (1)].val));

		    }
    break;

  case 365:
/* Line 1787 of yacc.c  */
#line 3192 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = mlhs_add((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 366:
/* Line 1787 of yacc.c  */
#line 3202 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (1)].val), 0);
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 367:
/* Line 1787 of yacc.c  */
#line 3210 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(4) - (4)].val), 0);
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (4)].val), (yyval.val));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (4)].val), (yyval.val));

		    }
    break;

  case 368:
/* Line 1787 of yacc.c  */
#line 3219 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(4) - (6)].val), 0);
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (6)].val), NEW_POSTARG((yyval.val), (yyvsp[(6) - (6)].val)));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (6)].val), (yyval.val));

		    }
    break;

  case 369:
/* Line 1787 of yacc.c  */
#line 3228 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (3)].val), -1);
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (3)].val), Qnil);

		    }
    break;

  case 370:
/* Line 1787 of yacc.c  */
#line 3236 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN((yyvsp[(1) - (5)].val), NEW_POSTARG(-1, (yyvsp[(5) - (5)].val)));
#endif
			(yyval.val) = mlhs_add_star((yyvsp[(1) - (5)].val), (yyvsp[(5) - (5)].val));

		    }
    break;

  case 371:
/* Line 1787 of yacc.c  */
#line 3244 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(2) - (2)].val), 0);
#if 0
			(yyval.val) = NEW_MASGN(0, (yyval.val));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), (yyval.val));

		    }
    break;

  case 372:
/* Line 1787 of yacc.c  */
#line 3253 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(2) - (4)].val), 0);
#if 0
			(yyval.val) = NEW_MASGN(0, NEW_POSTARG((yyval.val), (yyvsp[(4) - (4)].val)));
#endif
		      #if 0
		      TODO: Check me
		      #endif
			(yyval.val) = mlhs_add_star((yyval.val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 373:
/* Line 1787 of yacc.c  */
#line 3265 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, -1);
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), Qnil);

		    }
    break;

  case 374:
/* Line 1787 of yacc.c  */
#line 3273 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_MASGN(0, NEW_POSTARG(-1, (yyvsp[(3) - (3)].val)));
#endif
			(yyval.val) = mlhs_add_star(mlhs_new(), Qnil);

		    }
    break;

  case 375:
/* Line 1787 of yacc.c  */
#line 3284 "ripper.y"
    {
			(yyval.val) = new_args_tail((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
		    }
    break;

  case 376:
/* Line 1787 of yacc.c  */
#line 3288 "ripper.y"
    {
			(yyval.val) = new_args_tail((yyvsp[(1) - (2)].val), Qnone, (yyvsp[(2) - (2)].val));
		    }
    break;

  case 377:
/* Line 1787 of yacc.c  */
#line 3292 "ripper.y"
    {
			(yyval.val) = new_args_tail(Qnone, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
		    }
    break;

  case 378:
/* Line 1787 of yacc.c  */
#line 3296 "ripper.y"
    {
			(yyval.val) = new_args_tail(Qnone, Qnone, (yyvsp[(1) - (1)].val));
		    }
    break;

  case 379:
/* Line 1787 of yacc.c  */
#line 3302 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    }
    break;

  case 380:
/* Line 1787 of yacc.c  */
#line 3306 "ripper.y"
    {
			(yyval.val) = new_args_tail(Qnone, Qnone, Qnone);
		    }
    break;

  case 381:
/* Line 1787 of yacc.c  */
#line 3312 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), Qnone, (yyvsp[(6) - (6)].val));
		    }
    break;

  case 382:
/* Line 1787 of yacc.c  */
#line 3316 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (8)].val), (yyvsp[(3) - (8)].val), (yyvsp[(5) - (8)].val), (yyvsp[(7) - (8)].val), (yyvsp[(8) - (8)].val));
		    }
    break;

  case 383:
/* Line 1787 of yacc.c  */
#line 3320 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), Qnone, Qnone, (yyvsp[(4) - (4)].val));
		    }
    break;

  case 384:
/* Line 1787 of yacc.c  */
#line 3324 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), Qnone, (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
		    }
    break;

  case 385:
/* Line 1787 of yacc.c  */
#line 3328 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (4)].val), Qnone, (yyvsp[(3) - (4)].val), Qnone, (yyvsp[(4) - (4)].val));
		    }
    break;

  case 386:
/* Line 1787 of yacc.c  */
#line 3332 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (2)].val), Qnone, 1, Qnone, new_args_tail(Qnone, Qnone, Qnone));
#if 0
#endif
                        dispatch1(excessed_comma, (yyval.val));

		    }
    break;

  case 387:
/* Line 1787 of yacc.c  */
#line 3340 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), Qnone, (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
		    }
    break;

  case 388:
/* Line 1787 of yacc.c  */
#line 3344 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (2)].val), Qnone, Qnone, Qnone, (yyvsp[(2) - (2)].val));
		    }
    break;

  case 389:
/* Line 1787 of yacc.c  */
#line 3348 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), Qnone, (yyvsp[(4) - (4)].val));
		    }
    break;

  case 390:
/* Line 1787 of yacc.c  */
#line 3352 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, (yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
		    }
    break;

  case 391:
/* Line 1787 of yacc.c  */
#line 3356 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, (yyvsp[(1) - (2)].val), Qnone, Qnone, (yyvsp[(2) - (2)].val));
		    }
    break;

  case 392:
/* Line 1787 of yacc.c  */
#line 3360 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, (yyvsp[(1) - (4)].val), Qnone, (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
		    }
    break;

  case 393:
/* Line 1787 of yacc.c  */
#line 3364 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, Qnone, (yyvsp[(1) - (2)].val), Qnone, (yyvsp[(2) - (2)].val));
		    }
    break;

  case 394:
/* Line 1787 of yacc.c  */
#line 3368 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, Qnone, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
		    }
    break;

  case 395:
/* Line 1787 of yacc.c  */
#line 3372 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, Qnone, Qnone, Qnone, (yyvsp[(1) - (1)].val));
		    }
    break;

  case 397:
/* Line 1787 of yacc.c  */
#line 3379 "ripper.y"
    {
			command_start = TRUE;
		    }
    break;

  case 398:
/* Line 1787 of yacc.c  */
#line 3385 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = blockvar_new(params_new(Qnil,Qnil,Qnil,Qnil,Qnil,Qnil,Qnil),
                                          escape_Qundef((yyvsp[(2) - (3)].val)));

		    }
    break;

  case 399:
/* Line 1787 of yacc.c  */
#line 3394 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = blockvar_new(params_new(Qnil,Qnil,Qnil,Qnil,Qnil,Qnil,Qnil),
                                          Qnil);

		    }
    break;

  case 400:
/* Line 1787 of yacc.c  */
#line 3403 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (4)].val);
#endif
			(yyval.val) = blockvar_new(escape_Qundef((yyvsp[(2) - (4)].val)), escape_Qundef((yyvsp[(3) - (4)].val)));

		    }
    break;

  case 401:
/* Line 1787 of yacc.c  */
#line 3414 "ripper.y"
    {
		      (yyval.val) = 0;
		    }
    break;

  case 402:
/* Line 1787 of yacc.c  */
#line 3418 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = (yyvsp[(3) - (4)].val);

		    }
    break;

  case 403:
/* Line 1787 of yacc.c  */
#line 3430 "ripper.y"
    {
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));
		    }
    break;

  case 404:
/* Line 1787 of yacc.c  */
#line 3437 "ripper.y"
    {
			rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
		    }
    break;

  case 405:
/* Line 1787 of yacc.c  */
#line 3444 "ripper.y"
    {
			new_bv(get_id((yyvsp[(1) - (1)].val)));
#if 0
#endif
			(yyval.val) = get_value((yyvsp[(1) - (1)].val));

		    }
    break;

  case 406:
/* Line 1787 of yacc.c  */
#line 3452 "ripper.y"
    {
			(yyval.val) = 0;
		    }
    break;

  case 407:
/* Line 1787 of yacc.c  */
#line 3457 "ripper.y"
    {
			(yyval.vars) = dyna_push();
		    }
    break;

  case 408:
/* Line 1787 of yacc.c  */
#line 3460 "ripper.y"
    {
			(yyval.num) = lpar_beg;
			lpar_beg = ++paren_nest;
		    }
    break;

  case 409:
/* Line 1787 of yacc.c  */
#line 3465 "ripper.y"
    {
			(yyval.num) = ruby_sourceline;
		    }
    break;

  case 410:
/* Line 1787 of yacc.c  */
#line 3469 "ripper.y"
    {
			lpar_beg = (yyvsp[(2) - (5)].num);
#if 0
			(yyval.val) = NEW_LAMBDA((yyvsp[(3) - (5)].val), (yyvsp[(5) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(4) - (5)].num));
#endif
			(yyval.val) = dispatch2(lambda, (yyvsp[(3) - (5)].val), (yyvsp[(5) - (5)].val));

			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 411:
/* Line 1787 of yacc.c  */
#line 3482 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (4)].val);
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(2) - (4)].val));

		    }
    break;

  case 412:
/* Line 1787 of yacc.c  */
#line 3490 "ripper.y"
    {
			(yyval.val) = (yyvsp[(1) - (1)].val);
		    }
    break;

  case 413:
/* Line 1787 of yacc.c  */
#line 3496 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (3)].val);
		    }
    break;

  case 414:
/* Line 1787 of yacc.c  */
#line 3500 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (3)].val);
		    }
    break;

  case 415:
/* Line 1787 of yacc.c  */
#line 3506 "ripper.y"
    {
			(yyvsp[(1) - (1)].vars) = dyna_push();
#if 0
			(yyval.num) = ruby_sourceline;
#endif
		    }
    break;

  case 416:
/* Line 1787 of yacc.c  */
#line 3515 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ITER((yyvsp[(3) - (5)].val),(yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(2) - (5)].num));
#endif
			(yyval.val) = dispatch2(do_block, escape_Qundef((yyvsp[(3) - (5)].val)), (yyvsp[(4) - (5)].val));

			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 417:
/* Line 1787 of yacc.c  */
#line 3527 "ripper.y"
    {
#if 0
			if (nd_type((yyvsp[(1) - (2)].val)) == NODE_YIELD) {
			    compile_error(PARSER_ARG "block given to yield");
			}
			else {
			    block_dup_check((yyvsp[(1) - (2)].val)->nd_args, (yyvsp[(2) - (2)].val));
			}
			(yyvsp[(2) - (2)].val)->nd_iter = (yyvsp[(1) - (2)].val);
			(yyval.val) = (yyvsp[(2) - (2)].val);
			fixpos((yyval.val), (yyvsp[(1) - (2)].val));
#endif
			(yyval.val) = method_add_block((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 418:
/* Line 1787 of yacc.c  */
#line 3543 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), (yyvsp[(2) - (4)].val), (yyvsp[(3) - (4)].val));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 419:
/* Line 1787 of yacc.c  */
#line 3552 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			(yyvsp[(5) - (5)].val)->nd_iter = NEW_CALL((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = (yyvsp[(5) - (5)].val);
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(5) - (5)].val));

		    }
    break;

  case 420:
/* Line 1787 of yacc.c  */
#line 3564 "ripper.y"
    {
#if 0
			block_dup_check((yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
			(yyvsp[(5) - (5)].val)->nd_iter = NEW_CALL((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = (yyvsp[(5) - (5)].val);
			fixpos((yyval.val), (yyvsp[(1) - (5)].val));
#endif
			(yyval.val) = dispatch4(command_call, (yyvsp[(1) - (5)].val), (yyvsp[(2) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(4) - (5)].val));
			(yyval.val) = method_add_block((yyval.val), (yyvsp[(5) - (5)].val));

		    }
    break;

  case 421:
/* Line 1787 of yacc.c  */
#line 3578 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (2)].val);
			(yyval.val)->nd_args = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = method_arg(dispatch1(fcall, (yyvsp[(1) - (2)].val)), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 422:
/* Line 1787 of yacc.c  */
#line 3587 "ripper.y"
    {
#if 0
			(yyval.num) = ruby_sourceline;
#endif
		    }
    break;

  case 423:
/* Line 1787 of yacc.c  */
#line 3593 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(5) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(4) - (5)].num));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(5) - (5)].val));

		    }
    break;

  case 424:
/* Line 1787 of yacc.c  */
#line 3603 "ripper.y"
    {
#if 0
			(yyval.num) = ruby_sourceline;
#endif
		    }
    break;

  case 425:
/* Line 1787 of yacc.c  */
#line 3609 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (5)].val), (yyvsp[(3) - (5)].val), (yyvsp[(5) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(4) - (5)].num));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (5)].val), ripper_id2sym('.'), (yyvsp[(3) - (5)].val));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(5) - (5)].val));

		    }
    break;

  case 426:
/* Line 1787 of yacc.c  */
#line 3619 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val), 0);
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (3)].val), ripper_intern("::"), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 427:
/* Line 1787 of yacc.c  */
#line 3627 "ripper.y"
    {
#if 0
			(yyval.num) = ruby_sourceline;
#endif
		    }
    break;

  case 428:
/* Line 1787 of yacc.c  */
#line 3633 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), rb_intern("call"), (yyvsp[(4) - (4)].val));
			nd_set_line((yyval.val), (yyvsp[(3) - (4)].num));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), ripper_id2sym('.'),
				       ripper_intern("call"));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 429:
/* Line 1787 of yacc.c  */
#line 3644 "ripper.y"
    {
#if 0
			(yyval.num) = ruby_sourceline;
#endif
		    }
    break;

  case 430:
/* Line 1787 of yacc.c  */
#line 3650 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), rb_intern("call"), (yyvsp[(4) - (4)].val));
			nd_set_line((yyval.val), (yyvsp[(3) - (4)].num));
#endif
			(yyval.val) = dispatch3(call, (yyvsp[(1) - (4)].val), ripper_intern("::"),
				       ripper_intern("call"));
			(yyval.val) = method_optarg((yyval.val), (yyvsp[(4) - (4)].val));

		    }
    break;

  case 431:
/* Line 1787 of yacc.c  */
#line 3661 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_SUPER((yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(super, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 432:
/* Line 1787 of yacc.c  */
#line 3669 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ZSUPER();
#endif
			(yyval.val) = dispatch0(zsuper);

		    }
    break;

  case 433:
/* Line 1787 of yacc.c  */
#line 3677 "ripper.y"
    {
#if 0
			if ((yyvsp[(1) - (4)].val) && nd_type((yyvsp[(1) - (4)].val)) == NODE_SELF)
			    (yyval.val) = NEW_FCALL(tAREF, (yyvsp[(3) - (4)].val));
			else
			    (yyval.val) = NEW_CALL((yyvsp[(1) - (4)].val), tAREF, (yyvsp[(3) - (4)].val));
			fixpos((yyval.val), (yyvsp[(1) - (4)].val));
#endif
			(yyval.val) = dispatch2(aref, (yyvsp[(1) - (4)].val), escape_Qundef((yyvsp[(3) - (4)].val)));

		    }
    break;

  case 434:
/* Line 1787 of yacc.c  */
#line 3691 "ripper.y"
    {
			(yyvsp[(1) - (1)].vars) = dyna_push();
#if 0
			(yyval.num) = ruby_sourceline;
#endif

		    }
    break;

  case 435:
/* Line 1787 of yacc.c  */
#line 3700 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ITER((yyvsp[(3) - (5)].val),(yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(2) - (5)].num));
#endif
			(yyval.val) = dispatch2(brace_block, escape_Qundef((yyvsp[(3) - (5)].val)), (yyvsp[(4) - (5)].val));

			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 436:
/* Line 1787 of yacc.c  */
#line 3710 "ripper.y"
    {
			(yyvsp[(1) - (1)].vars) = dyna_push();
#if 0
			(yyval.num) = ruby_sourceline;
#endif

		    }
    break;

  case 437:
/* Line 1787 of yacc.c  */
#line 3719 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ITER((yyvsp[(3) - (5)].val),(yyvsp[(4) - (5)].val));
			nd_set_line((yyval.val), (yyvsp[(2) - (5)].num));
#endif
			(yyval.val) = dispatch2(do_block, escape_Qundef((yyvsp[(3) - (5)].val)), (yyvsp[(4) - (5)].val));

			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 438:
/* Line 1787 of yacc.c  */
#line 3733 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_WHEN((yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val), (yyvsp[(5) - (5)].val));
#endif
			(yyval.val) = dispatch3(when, (yyvsp[(2) - (5)].val), (yyvsp[(4) - (5)].val), escape_Qundef((yyvsp[(5) - (5)].val)));

		    }
    break;

  case 441:
/* Line 1787 of yacc.c  */
#line 3749 "ripper.y"
    {
#if 0
			if ((yyvsp[(3) - (6)].val)) {
			    (yyvsp[(3) - (6)].val) = node_assign((yyvsp[(3) - (6)].val), NEW_ERRINFO());
			    (yyvsp[(5) - (6)].val) = block_append((yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val));
			}
			(yyval.val) = NEW_RESBODY((yyvsp[(2) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
			fixpos((yyval.val), (yyvsp[(2) - (6)].val)?(yyvsp[(2) - (6)].val):(yyvsp[(5) - (6)].val));
#endif
			(yyval.val) = dispatch4(rescue,
				       escape_Qundef((yyvsp[(2) - (6)].val)),
				       escape_Qundef((yyvsp[(3) - (6)].val)),
				       escape_Qundef((yyvsp[(5) - (6)].val)),
				       escape_Qundef((yyvsp[(6) - (6)].val)));

		    }
    break;

  case 443:
/* Line 1787 of yacc.c  */
#line 3769 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIST((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 444:
/* Line 1787 of yacc.c  */
#line 3777 "ripper.y"
    {
#if 0
			if (!((yyval.val) = splat_array((yyvsp[(1) - (1)].val)))) (yyval.val) = (yyvsp[(1) - (1)].val);
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 446:
/* Line 1787 of yacc.c  */
#line 3788 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    }
    break;

  case 448:
/* Line 1787 of yacc.c  */
#line 3795 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(ensure, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 451:
/* Line 1787 of yacc.c  */
#line 3807 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_LIT(ID2SYM((yyvsp[(1) - (1)].val)));
#endif
			(yyval.val) = dispatch1(symbol_literal, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 453:
/* Line 1787 of yacc.c  */
#line 3818 "ripper.y"
    {
#if 0
			NODE *node = (yyvsp[(1) - (1)].val);
			if (!node) {
			    node = NEW_STR(STR_NEW0());
			}
			else {
			    node = evstr2dstr(node);
			}
			(yyval.val) = node;
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 456:
/* Line 1787 of yacc.c  */
#line 3837 "ripper.y"
    {
#if 0
			(yyval.val) = literal_concat((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(string_concat, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 457:
/* Line 1787 of yacc.c  */
#line 3847 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(string_literal, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 458:
/* Line 1787 of yacc.c  */
#line 3857 "ripper.y"
    {
#if 0
			NODE *node = (yyvsp[(2) - (3)].val);
			if (!node) {
			    node = NEW_XSTR(STR_NEW0());
			}
			else {
			    switch (nd_type(node)) {
			      case NODE_STR:
				nd_set_type(node, NODE_XSTR);
				break;
			      case NODE_DSTR:
				nd_set_type(node, NODE_DXSTR);
				break;
			      default:
				node = NEW_NODE(NODE_DXSTR, Qnil, 1, NEW_LIST(node));
				break;
			    }
			}
			(yyval.val) = node;
#endif
			(yyval.val) = dispatch1(xstring_literal, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 459:
/* Line 1787 of yacc.c  */
#line 3884 "ripper.y"
    {
#if 0
			int options = (yyvsp[(3) - (3)].val);
			NODE *node = (yyvsp[(2) - (3)].val);
			NODE *list, *prev;
			if (!node) {
			    node = NEW_LIT(reg_compile(STR_NEW0(), options));
			}
			else switch (nd_type(node)) {
			  case NODE_STR:
			    {
				VALUE src = node->nd_lit;
				nd_set_type(node, NODE_LIT);
				node->nd_lit = reg_compile(src, options);
			    }
			    break;
			  default:
			    node = NEW_NODE(NODE_DSTR, STR_NEW0(), 1, NEW_LIST(node));
			  case NODE_DSTR:
			    if (options & RE_OPTION_ONCE) {
				nd_set_type(node, NODE_DREGX_ONCE);
			    }
			    else {
				nd_set_type(node, NODE_DREGX);
			    }
			    node->nd_cflag = options & RE_OPTION_MASK;
			    if (!NIL_P(node->nd_lit)) reg_fragment_check(node->nd_lit, options);
			    for (list = (prev = node)->nd_next; list; list = list->nd_next) {
				if (nd_type(list->nd_head) == NODE_STR) {
				    VALUE tail = list->nd_head->nd_lit;
				    if (reg_fragment_check(tail, options) && prev && !NIL_P(prev->nd_lit)) {
					VALUE lit = prev == node ? prev->nd_lit : prev->nd_head->nd_lit;
					if (!literal_concat0(parser, lit, tail)) {
					    node = 0;
					    break;
					}
					rb_str_resize(tail, 0);
					prev->nd_next = list->nd_next;
					rb_gc_force_recycle((VALUE)list->nd_head);
					rb_gc_force_recycle((VALUE)list);
					list = prev;
				    }
				    else {
					prev = list;
				    }
                                }
				else {
				    prev = 0;
				}
                            }
			    if (!node->nd_next) {
				VALUE src = node->nd_lit;
				nd_set_type(node, NODE_LIT);
				node->nd_lit = reg_compile(src, options);
			    }
			    break;
			}
			(yyval.val) = node;
#endif
			(yyval.val) = dispatch2(regexp_literal, (yyvsp[(2) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 460:
/* Line 1787 of yacc.c  */
#line 3949 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ZARRAY();
#endif
			(yyval.val) = dispatch0(words_new);
			(yyval.val) = dispatch1(array, (yyval.val));

		    }
    break;

  case 461:
/* Line 1787 of yacc.c  */
#line 3958 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(array, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 462:
/* Line 1787 of yacc.c  */
#line 3968 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(words_new);

		    }
    break;

  case 463:
/* Line 1787 of yacc.c  */
#line 3976 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), evstr2dstr((yyvsp[(2) - (3)].val)));
#endif
			(yyval.val) = dispatch2(words_add, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));

		    }
    break;

  case 464:
/* Line 1787 of yacc.c  */
#line 3988 "ripper.y"
    {
			(yyval.val) = dispatch0(word_new);
			(yyval.val) = dispatch2(word_add, (yyval.val), (yyvsp[(1) - (1)].val));
		    }
    break;

  case 465:
/* Line 1787 of yacc.c  */
#line 3994 "ripper.y"
    {
#if 0
			(yyval.val) = literal_concat((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(word_add, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 466:
/* Line 1787 of yacc.c  */
#line 4004 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ZARRAY();
#endif
			(yyval.val) = dispatch0(symbols_new);
			(yyval.val) = dispatch1(array, (yyval.val));

		    }
    break;

  case 467:
/* Line 1787 of yacc.c  */
#line 4013 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(array, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 468:
/* Line 1787 of yacc.c  */
#line 4023 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(symbols_new);

		    }
    break;

  case 469:
/* Line 1787 of yacc.c  */
#line 4031 "ripper.y"
    {
#if 0
			(yyvsp[(2) - (3)].val) = evstr2dstr((yyvsp[(2) - (3)].val));
			nd_set_type((yyvsp[(2) - (3)].val), NODE_DSYM);
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = dispatch2(symbols_add, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));

		    }
    break;

  case 470:
/* Line 1787 of yacc.c  */
#line 4043 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ZARRAY();
#endif
			(yyval.val) = dispatch0(qwords_new);
			(yyval.val) = dispatch1(array, (yyval.val));

		    }
    break;

  case 471:
/* Line 1787 of yacc.c  */
#line 4052 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(array, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 472:
/* Line 1787 of yacc.c  */
#line 4062 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ZARRAY();
#endif
			(yyval.val) = dispatch0(qsymbols_new);
			(yyval.val) = dispatch1(array, (yyval.val));

		    }
    break;

  case 473:
/* Line 1787 of yacc.c  */
#line 4071 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(array, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 474:
/* Line 1787 of yacc.c  */
#line 4081 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(qwords_new);

		    }
    break;

  case 475:
/* Line 1787 of yacc.c  */
#line 4089 "ripper.y"
    {
#if 0
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = dispatch2(qwords_add, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));

		    }
    break;

  case 476:
/* Line 1787 of yacc.c  */
#line 4099 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(qsymbols_new);

		    }
    break;

  case 477:
/* Line 1787 of yacc.c  */
#line 4107 "ripper.y"
    {
#if 0
			VALUE lit;
			lit = (yyvsp[(2) - (3)].val)->nd_lit;
			(yyvsp[(2) - (3)].val)->nd_lit = ID2SYM(rb_intern_str(lit));
			nd_set_type((yyvsp[(2) - (3)].val), NODE_LIT);
			(yyval.val) = list_append((yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = dispatch2(qsymbols_add, (yyvsp[(1) - (3)].val), (yyvsp[(2) - (3)].val));

		    }
    break;

  case 478:
/* Line 1787 of yacc.c  */
#line 4121 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(string_content);

		    }
    break;

  case 479:
/* Line 1787 of yacc.c  */
#line 4129 "ripper.y"
    {
#if 0
			(yyval.val) = literal_concat((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(string_add, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 480:
/* Line 1787 of yacc.c  */
#line 4139 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(xstring_new);

		    }
    break;

  case 481:
/* Line 1787 of yacc.c  */
#line 4147 "ripper.y"
    {
#if 0
			(yyval.val) = literal_concat((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(xstring_add, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 482:
/* Line 1787 of yacc.c  */
#line 4157 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch0(regexp_new);

		    }
    break;

  case 483:
/* Line 1787 of yacc.c  */
#line 4165 "ripper.y"
    {
#if 0
			NODE *head = (yyvsp[(1) - (2)].val), *tail = (yyvsp[(2) - (2)].val);
			if (!head) {
			    (yyval.val) = tail;
			}
			else if (!tail) {
			    (yyval.val) = head;
			}
			else {
			    switch (nd_type(head)) {
			      case NODE_STR:
				nd_set_type(head, NODE_DSTR);
				break;
			      case NODE_DSTR:
				break;
			      default:
				head = list_append(NEW_DSTR(Qnil), head);
				break;
			    }
			    (yyval.val) = list_append(head, tail);
			}
#endif
			(yyval.val) = dispatch2(regexp_add, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 485:
/* Line 1787 of yacc.c  */
#line 4195 "ripper.y"
    {
			(yyval.node) = lex_strterm;
			lex_strterm = 0;
			lex_state = EXPR_BEG;
		    }
    break;

  case 486:
/* Line 1787 of yacc.c  */
#line 4201 "ripper.y"
    {
#if 0
			lex_strterm = (yyvsp[(2) - (3)].node);
			(yyval.val) = NEW_EVSTR((yyvsp[(3) - (3)].val));
#endif
			lex_strterm = (yyvsp[(2) - (3)].node);
			(yyval.val) = dispatch1(string_dvar, (yyvsp[(3) - (3)].val));

		    }
    break;

  case 487:
/* Line 1787 of yacc.c  */
#line 4211 "ripper.y"
    {
			(yyvsp[(1) - (1)].val) = cond_stack;
			(yyval.val) = cmdarg_stack;
			cond_stack = 0;
			cmdarg_stack = 0;
		    }
    break;

  case 488:
/* Line 1787 of yacc.c  */
#line 4217 "ripper.y"
    {
			(yyval.node) = lex_strterm;
			lex_strterm = 0;
			lex_state = EXPR_BEG;
		    }
    break;

  case 489:
/* Line 1787 of yacc.c  */
#line 4222 "ripper.y"
    {
			(yyval.num) = brace_nest;
			brace_nest = 0;
		    }
    break;

  case 490:
/* Line 1787 of yacc.c  */
#line 4227 "ripper.y"
    {
			cond_stack = (yyvsp[(1) - (6)].val);
			cmdarg_stack = (yyvsp[(2) - (6)].val);
			lex_strterm = (yyvsp[(3) - (6)].node);
			brace_nest = (yyvsp[(4) - (6)].num);
#if 0
			if ((yyvsp[(5) - (6)].val)) (yyvsp[(5) - (6)].val)->flags &= ~NODE_FL_NEWLINE;
			(yyval.val) = new_evstr((yyvsp[(5) - (6)].val));
#endif
			(yyval.val) = dispatch1(string_embexpr, (yyvsp[(5) - (6)].val));

		    }
    break;

  case 491:
/* Line 1787 of yacc.c  */
#line 4242 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_GVAR((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 492:
/* Line 1787 of yacc.c  */
#line 4250 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_IVAR((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 493:
/* Line 1787 of yacc.c  */
#line 4258 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_CVAR((yyvsp[(1) - (1)].val));
#endif
			(yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 495:
/* Line 1787 of yacc.c  */
#line 4269 "ripper.y"
    {
			lex_state = EXPR_END;
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(symbol, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 500:
/* Line 1787 of yacc.c  */
#line 4286 "ripper.y"
    {
			lex_state = EXPR_END;
#if 0
			(yyval.val) = dsym_node((yyvsp[(2) - (3)].val));
#endif
			(yyval.val) = dispatch1(dyna_symbol, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 502:
/* Line 1787 of yacc.c  */
#line 4298 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
			(yyval.val)->nd_lit = negate_lit((yyval.val)->nd_lit);
#endif
			(yyval.val) = dispatch2(unary, ripper_intern("-@"), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 512:
/* Line 1787 of yacc.c  */
#line 4321 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword_nil);}
    break;

  case 513:
/* Line 1787 of yacc.c  */
#line 4322 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword_self);}
    break;

  case 514:
/* Line 1787 of yacc.c  */
#line 4323 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword_true);}
    break;

  case 515:
/* Line 1787 of yacc.c  */
#line 4324 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword_false);}
    break;

  case 516:
/* Line 1787 of yacc.c  */
#line 4325 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword__FILE__);}
    break;

  case 517:
/* Line 1787 of yacc.c  */
#line 4326 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword__LINE__);}
    break;

  case 518:
/* Line 1787 of yacc.c  */
#line 4327 "ripper.y"
    {ifndef_ripper((yyval.val) = keyword__ENCODING__);}
    break;

  case 519:
/* Line 1787 of yacc.c  */
#line 4331 "ripper.y"
    {
#if 0
			if (!((yyval.val) = gettable((yyvsp[(1) - (1)].val)))) (yyval.val) = NEW_BEGIN(0);
#endif
			if (id_is_var(get_id((yyvsp[(1) - (1)].val)))) {
			    (yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));
			}
			else {
			    (yyval.val) = dispatch1(vcall, (yyvsp[(1) - (1)].val));
			}

		    }
    break;

  case 520:
/* Line 1787 of yacc.c  */
#line 4344 "ripper.y"
    {
#if 0
			if (!((yyval.val) = gettable((yyvsp[(1) - (1)].val)))) (yyval.val) = NEW_BEGIN(0);
#endif
			(yyval.val) = dispatch1(var_ref, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 521:
/* Line 1787 of yacc.c  */
#line 4354 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
#if 0
#endif
			(yyval.val) = dispatch1(var_field, (yyval.val));

		    }
    break;

  case 522:
/* Line 1787 of yacc.c  */
#line 4362 "ripper.y"
    {
		        (yyval.val) = assignable((yyvsp[(1) - (1)].val), 0);
#if 0
#endif
			(yyval.val) = dispatch1(var_field, (yyval.val));

		    }
    break;

  case 525:
/* Line 1787 of yacc.c  */
#line 4376 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = Qnil;

		    }
    break;

  case 526:
/* Line 1787 of yacc.c  */
#line 4384 "ripper.y"
    {
			lex_state = EXPR_BEG;
			command_start = TRUE;
		    }
    break;

  case 527:
/* Line 1787 of yacc.c  */
#line 4389 "ripper.y"
    {
			(yyval.val) = (yyvsp[(3) - (4)].val);
		    }
    break;

  case 528:
/* Line 1787 of yacc.c  */
#line 4393 "ripper.y"
    {
#if 0
			yyerrok;
			(yyval.val) = 0;
#endif
			yyerrok;
			(yyval.val) = Qnil;

		    }
    break;

  case 529:
/* Line 1787 of yacc.c  */
#line 4405 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(2) - (3)].val));

			lex_state = EXPR_BEG;
			command_start = TRUE;
		    }
    break;

  case 530:
/* Line 1787 of yacc.c  */
#line 4414 "ripper.y"
    {
			(yyval.num) = parser->parser_in_kwarg;
			parser->parser_in_kwarg = 1;
		    }
    break;

  case 531:
/* Line 1787 of yacc.c  */
#line 4419 "ripper.y"
    {
			parser->parser_in_kwarg = (yyvsp[(1) - (3)].num);
			(yyval.val) = (yyvsp[(2) - (3)].val);
			lex_state = EXPR_BEG;
			command_start = TRUE;
		    }
    break;

  case 532:
/* Line 1787 of yacc.c  */
#line 4428 "ripper.y"
    {
			(yyval.val) = new_args_tail((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
		    }
    break;

  case 533:
/* Line 1787 of yacc.c  */
#line 4432 "ripper.y"
    {
			(yyval.val) = new_args_tail((yyvsp[(1) - (2)].val), Qnone, (yyvsp[(2) - (2)].val));
		    }
    break;

  case 534:
/* Line 1787 of yacc.c  */
#line 4436 "ripper.y"
    {
			(yyval.val) = new_args_tail(Qnone, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
		    }
    break;

  case 535:
/* Line 1787 of yacc.c  */
#line 4440 "ripper.y"
    {
			(yyval.val) = new_args_tail(Qnone, Qnone, (yyvsp[(1) - (1)].val));
		    }
    break;

  case 536:
/* Line 1787 of yacc.c  */
#line 4446 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    }
    break;

  case 537:
/* Line 1787 of yacc.c  */
#line 4450 "ripper.y"
    {
			(yyval.val) = new_args_tail(Qnone, Qnone, Qnone);
		    }
    break;

  case 538:
/* Line 1787 of yacc.c  */
#line 4456 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), Qnone, (yyvsp[(6) - (6)].val));
		    }
    break;

  case 539:
/* Line 1787 of yacc.c  */
#line 4460 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (8)].val), (yyvsp[(3) - (8)].val), (yyvsp[(5) - (8)].val), (yyvsp[(7) - (8)].val), (yyvsp[(8) - (8)].val));
		    }
    break;

  case 540:
/* Line 1787 of yacc.c  */
#line 4464 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), Qnone, Qnone, (yyvsp[(4) - (4)].val));
		    }
    break;

  case 541:
/* Line 1787 of yacc.c  */
#line 4468 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), Qnone, (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
		    }
    break;

  case 542:
/* Line 1787 of yacc.c  */
#line 4472 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (4)].val), Qnone, (yyvsp[(3) - (4)].val), Qnone, (yyvsp[(4) - (4)].val));
		    }
    break;

  case 543:
/* Line 1787 of yacc.c  */
#line 4476 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (6)].val), Qnone, (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
		    }
    break;

  case 544:
/* Line 1787 of yacc.c  */
#line 4480 "ripper.y"
    {
			(yyval.val) = new_args((yyvsp[(1) - (2)].val), Qnone, Qnone, Qnone, (yyvsp[(2) - (2)].val));
		    }
    break;

  case 545:
/* Line 1787 of yacc.c  */
#line 4484 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), Qnone, (yyvsp[(4) - (4)].val));
		    }
    break;

  case 546:
/* Line 1787 of yacc.c  */
#line 4488 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, (yyvsp[(1) - (6)].val), (yyvsp[(3) - (6)].val), (yyvsp[(5) - (6)].val), (yyvsp[(6) - (6)].val));
		    }
    break;

  case 547:
/* Line 1787 of yacc.c  */
#line 4492 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, (yyvsp[(1) - (2)].val), Qnone, Qnone, (yyvsp[(2) - (2)].val));
		    }
    break;

  case 548:
/* Line 1787 of yacc.c  */
#line 4496 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, (yyvsp[(1) - (4)].val), Qnone, (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
		    }
    break;

  case 549:
/* Line 1787 of yacc.c  */
#line 4500 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, Qnone, (yyvsp[(1) - (2)].val), Qnone, (yyvsp[(2) - (2)].val));
		    }
    break;

  case 550:
/* Line 1787 of yacc.c  */
#line 4504 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, Qnone, (yyvsp[(1) - (4)].val), (yyvsp[(3) - (4)].val), (yyvsp[(4) - (4)].val));
		    }
    break;

  case 551:
/* Line 1787 of yacc.c  */
#line 4508 "ripper.y"
    {
			(yyval.val) = new_args(Qnone, Qnone, Qnone, Qnone, (yyvsp[(1) - (1)].val));
		    }
    break;

  case 552:
/* Line 1787 of yacc.c  */
#line 4512 "ripper.y"
    {
			(yyval.val) = new_args_tail(Qnone, Qnone, Qnone);
			(yyval.val) = new_args(Qnone, Qnone, Qnone, Qnone, (yyval.val));
		    }
    break;

  case 553:
/* Line 1787 of yacc.c  */
#line 4519 "ripper.y"
    {
#if 0
			yyerror("formal argument cannot be a constant");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(param_error, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 554:
/* Line 1787 of yacc.c  */
#line 4528 "ripper.y"
    {
#if 0
			yyerror("formal argument cannot be an instance variable");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(param_error, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 555:
/* Line 1787 of yacc.c  */
#line 4537 "ripper.y"
    {
#if 0
			yyerror("formal argument cannot be a global variable");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(param_error, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 556:
/* Line 1787 of yacc.c  */
#line 4546 "ripper.y"
    {
#if 0
			yyerror("formal argument cannot be a class variable");
			(yyval.val) = 0;
#endif
			(yyval.val) = dispatch1(param_error, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 558:
/* Line 1787 of yacc.c  */
#line 4558 "ripper.y"
    {
			formal_argument(get_id((yyvsp[(1) - (1)].val)));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		    }
    break;

  case 559:
/* Line 1787 of yacc.c  */
#line 4565 "ripper.y"
    {
			arg_var(get_id((yyvsp[(1) - (1)].val)));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		    }
    break;

  case 560:
/* Line 1787 of yacc.c  */
#line 4572 "ripper.y"
    {
#if 0
			(yyval.val) = NEW_ARGS_AUX((yyvsp[(1) - (1)].val), 1);
#endif
			(yyval.val) = get_value((yyvsp[(1) - (1)].val));

		    }
    break;

  case 561:
/* Line 1787 of yacc.c  */
#line 4580 "ripper.y"
    {
			ID tid = internal_id();
			arg_var(tid);
#if 0
			if (dyna_in_block()) {
			    (yyvsp[(2) - (3)].val)->nd_value = NEW_DVAR(tid);
			}
			else {
			    (yyvsp[(2) - (3)].val)->nd_value = NEW_LVAR(tid);
			}
			(yyval.val) = NEW_ARGS_AUX(tid, 1);
			(yyval.val)->nd_next = (yyvsp[(2) - (3)].val);
#endif
			(yyval.val) = dispatch1(mlhs_paren, (yyvsp[(2) - (3)].val));

		    }
    break;

  case 562:
/* Line 1787 of yacc.c  */
#line 4601 "ripper.y"
    {
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));
		    }
    break;

  case 563:
/* Line 1787 of yacc.c  */
#line 4606 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (3)].val);
			(yyval.val)->nd_plen++;
			(yyval.val)->nd_next = block_append((yyval.val)->nd_next, (yyvsp[(3) - (3)].val)->nd_next);
			rb_gc_force_recycle((VALUE)(yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 564:
/* Line 1787 of yacc.c  */
#line 4620 "ripper.y"
    {
			arg_var(formal_argument(get_id((yyvsp[(1) - (1)].val))));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		    }
    break;

  case 565:
/* Line 1787 of yacc.c  */
#line 4627 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#if 0
			(yyval.val) = NEW_KW_ARG(0, (yyval.val));
#endif
			(yyval.val) = rb_assoc_new((yyval.val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 566:
/* Line 1787 of yacc.c  */
#line 4636 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), (NODE *)-1);
#if 0
			(yyval.val) = NEW_KW_ARG(0, (yyval.val));
#endif
			(yyval.val) = rb_assoc_new((yyval.val), 0);

		    }
    break;

  case 567:
/* Line 1787 of yacc.c  */
#line 4647 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));
#if 0
			(yyval.val) = NEW_KW_ARG(0, (yyval.val));
#endif
			(yyval.val) = rb_assoc_new((yyval.val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 568:
/* Line 1787 of yacc.c  */
#line 4656 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (1)].val), (NODE *)-1);
#if 0
			(yyval.val) = NEW_KW_ARG(0, (yyval.val));
#endif
			(yyval.val) = rb_assoc_new((yyval.val), 0);

		    }
    break;

  case 569:
/* Line 1787 of yacc.c  */
#line 4667 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (1)].val);
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 570:
/* Line 1787 of yacc.c  */
#line 4675 "ripper.y"
    {
#if 0
			NODE *kws = (yyvsp[(1) - (3)].val);

			while (kws->nd_next) {
			    kws = kws->nd_next;
			}
			kws->nd_next = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 571:
/* Line 1787 of yacc.c  */
#line 4692 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (1)].val);
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 572:
/* Line 1787 of yacc.c  */
#line 4700 "ripper.y"
    {
#if 0
			NODE *kws = (yyvsp[(1) - (3)].val);

			while (kws->nd_next) {
			    kws = kws->nd_next;
			}
			kws->nd_next = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 575:
/* Line 1787 of yacc.c  */
#line 4720 "ripper.y"
    {
			shadowing_lvar(get_id((yyvsp[(2) - (2)].val)));
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    }
    break;

  case 576:
/* Line 1787 of yacc.c  */
#line 4725 "ripper.y"
    {
			(yyval.val) = internal_id();
		    }
    break;

  case 577:
/* Line 1787 of yacc.c  */
#line 4731 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#if 0
			(yyval.val) = NEW_OPT_ARG(0, (yyval.val));
#endif
			(yyval.val) = rb_assoc_new((yyval.val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 578:
/* Line 1787 of yacc.c  */
#line 4742 "ripper.y"
    {
			(yyval.val) = assignable((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#if 0
			(yyval.val) = NEW_OPT_ARG(0, (yyval.val));
#endif
			(yyval.val) = rb_assoc_new((yyval.val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 579:
/* Line 1787 of yacc.c  */
#line 4753 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (1)].val);
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 580:
/* Line 1787 of yacc.c  */
#line 4761 "ripper.y"
    {
#if 0
			NODE *opts = (yyvsp[(1) - (3)].val);

			while (opts->nd_next) {
			    opts = opts->nd_next;
			}
			opts->nd_next = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 581:
/* Line 1787 of yacc.c  */
#line 4777 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (1)].val);
#endif
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));

		    }
    break;

  case 582:
/* Line 1787 of yacc.c  */
#line 4785 "ripper.y"
    {
#if 0
			NODE *opts = (yyvsp[(1) - (3)].val);

			while (opts->nd_next) {
			    opts = opts->nd_next;
			}
			opts->nd_next = (yyvsp[(3) - (3)].val);
			(yyval.val) = (yyvsp[(1) - (3)].val);
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 585:
/* Line 1787 of yacc.c  */
#line 4805 "ripper.y"
    {
#if 0
			if (!is_local_id((yyvsp[(2) - (2)].val)))
			    yyerror("rest argument must be local variable");
#endif
			arg_var(shadowing_lvar(get_id((yyvsp[(2) - (2)].val))));
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(rest_param, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 586:
/* Line 1787 of yacc.c  */
#line 4818 "ripper.y"
    {
#if 0
			(yyval.val) = internal_id();
			arg_var((yyval.val));
#endif
			(yyval.val) = dispatch1(rest_param, Qnil);

		    }
    break;

  case 589:
/* Line 1787 of yacc.c  */
#line 4833 "ripper.y"
    {
#if 0
			if (!is_local_id((yyvsp[(2) - (2)].val)))
			    yyerror("block argument must be local variable");
			else if (!dyna_in_block() && local_id((yyvsp[(2) - (2)].val)))
			    yyerror("duplicated block argument name");
#endif
			arg_var(shadowing_lvar(get_id((yyvsp[(2) - (2)].val))));
#if 0
			(yyval.val) = (yyvsp[(2) - (2)].val);
#endif
			(yyval.val) = dispatch1(blockarg, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 590:
/* Line 1787 of yacc.c  */
#line 4850 "ripper.y"
    {
			(yyval.val) = (yyvsp[(2) - (2)].val);
		    }
    break;

  case 591:
/* Line 1787 of yacc.c  */
#line 4854 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = Qundef;

		    }
    break;

  case 592:
/* Line 1787 of yacc.c  */
#line 4864 "ripper.y"
    {
#if 0
			value_expr((yyvsp[(1) - (1)].val));
			(yyval.val) = (yyvsp[(1) - (1)].val);
		        if (!(yyval.val)) (yyval.val) = NEW_NIL();
#endif
			(yyval.val) = (yyvsp[(1) - (1)].val);

		    }
    break;

  case 593:
/* Line 1787 of yacc.c  */
#line 4873 "ripper.y"
    {lex_state = EXPR_BEG;}
    break;

  case 594:
/* Line 1787 of yacc.c  */
#line 4874 "ripper.y"
    {
#if 0
			if ((yyvsp[(3) - (4)].val) == 0) {
			    yyerror("can't define singleton method for ().");
			}
			else {
			    switch (nd_type((yyvsp[(3) - (4)].val))) {
			      case NODE_STR:
			      case NODE_DSTR:
			      case NODE_XSTR:
			      case NODE_DXSTR:
			      case NODE_DREGX:
			      case NODE_LIT:
			      case NODE_ARRAY:
			      case NODE_ZARRAY:
				yyerror("can't define singleton method for literals");
			      default:
				value_expr((yyvsp[(3) - (4)].val));
				break;
			    }
			}
			(yyval.val) = (yyvsp[(3) - (4)].val);
#endif
			(yyval.val) = dispatch1(paren, (yyvsp[(3) - (4)].val));

		    }
    break;

  case 596:
/* Line 1787 of yacc.c  */
#line 4904 "ripper.y"
    {
#if 0
			(yyval.val) = (yyvsp[(1) - (2)].val);
#endif
			(yyval.val) = dispatch1(assoclist_from_args, (yyvsp[(1) - (2)].val));

		    }
    break;

  case 597:
/* Line 1787 of yacc.c  */
#line 4916 "ripper.y"
    {
			(yyval.val) = rb_ary_new3(1, (yyvsp[(1) - (1)].val));
		    }
    break;

  case 598:
/* Line 1787 of yacc.c  */
#line 4921 "ripper.y"
    {
#if 0
			(yyval.val) = list_concat((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = rb_ary_push((yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 599:
/* Line 1787 of yacc.c  */
#line 4931 "ripper.y"
    {
#if 0
			if (nd_type((yyvsp[(1) - (3)].val)) == NODE_STR) {
			    nd_set_type((yyvsp[(1) - (3)].val), NODE_LIT);
			    (yyvsp[(1) - (3)].val)->nd_lit = rb_fstring((yyvsp[(1) - (3)].val)->nd_lit);
			}
			(yyval.val) = list_append(NEW_LIST((yyvsp[(1) - (3)].val)), (yyvsp[(3) - (3)].val));
#endif
			(yyval.val) = dispatch2(assoc_new, (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val));

		    }
    break;

  case 600:
/* Line 1787 of yacc.c  */
#line 4943 "ripper.y"
    {
#if 0
			(yyval.val) = list_append(NEW_LIST(NEW_LIT(ID2SYM((yyvsp[(1) - (2)].val)))), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch2(assoc_new, (yyvsp[(1) - (2)].val), (yyvsp[(2) - (2)].val));

		    }
    break;

  case 601:
/* Line 1787 of yacc.c  */
#line 4951 "ripper.y"
    {
#if 0
			(yyval.val) = list_append(NEW_LIST(0), (yyvsp[(2) - (2)].val));
#endif
			(yyval.val) = dispatch1(assoc_splat, (yyvsp[(2) - (2)].val));

		    }
    break;

  case 612:
/* Line 1787 of yacc.c  */
#line 4979 "ripper.y"
    { (yyval.val) = (yyvsp[(1) - (1)].val); }
    break;

  case 613:
/* Line 1787 of yacc.c  */
#line 4984 "ripper.y"
    { (yyval.val) = (yyvsp[(1) - (1)].val); }
    break;

  case 623:
/* Line 1787 of yacc.c  */
#line 5007 "ripper.y"
    {yyerrok;}
    break;

  case 626:
/* Line 1787 of yacc.c  */
#line 5012 "ripper.y"
    {yyerrok;}
    break;

  case 627:
/* Line 1787 of yacc.c  */
#line 5016 "ripper.y"
    {
#if 0
			(yyval.val) = 0;
#endif
			(yyval.val) = Qundef;

		    }
    break;


/* Line 1787 of yacc.c  */
#line 10832 "parse.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      parser_yyerror (parser, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        parser_yyerror (parser, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, parser);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  parser_yyerror (parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, parser);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 5024 "ripper.y"

# undef parser
# undef yylex
# undef yylval
# define yylval  (*((YYSTYPE*)(parser->parser_yylval)))

static int parser_regx_options(struct parser_params*);
static int parser_tokadd_string(struct parser_params*,int,int,int,long*,rb_encoding**);
static void parser_tokaddmbc(struct parser_params *parser, int c, rb_encoding *enc);
static int parser_parse_string(struct parser_params*,NODE*);
static int parser_here_document(struct parser_params*,NODE*);


# define nextc()                      parser_nextc(parser)
# define pushback(c)                  parser_pushback(parser, (c))
# define newtok()                     parser_newtok(parser)
# define tokspace(n)                  parser_tokspace(parser, (n))
# define tokadd(c)                    parser_tokadd(parser, (c))
# define tok_hex(numlen)              parser_tok_hex(parser, (numlen))
# define read_escape(flags,e)         parser_read_escape(parser, (flags), (e))
# define tokadd_escape(e)             parser_tokadd_escape(parser, (e))
# define regx_options()               parser_regx_options(parser)
# define tokadd_string(f,t,p,n,e)     parser_tokadd_string(parser,(f),(t),(p),(n),(e))
# define parse_string(n)              parser_parse_string(parser,(n))
# define tokaddmbc(c, enc)            parser_tokaddmbc(parser, (c), (enc))
# define here_document(n)             parser_here_document(parser,(n))
# define heredoc_identifier()         parser_heredoc_identifier(parser)
# define heredoc_restore(n)           parser_heredoc_restore(parser,(n))
# define whole_match_p(e,l,i)         parser_whole_match_p(parser,(e),(l),(i))
# define number_literal_suffix(f)     parser_number_literal_suffix(parser, (f))
# define set_number_literal(v, t, f)  parser_set_number_literal(parser, (v), (t), (f))
# define set_integer_literal(v, f)    parser_set_integer_literal(parser, (v), (f))

#ifndef RIPPER
# define set_yylval_str(x) (yylval.node = NEW_STR(x))
# define set_yylval_num(x) (yylval.num = (x))
# define set_yylval_id(x)  (yylval.id = (x))
# define set_yylval_name(x)  (yylval.id = (x))
# define set_yylval_literal(x) (yylval.node = NEW_LIT(x))
# define set_yylval_node(x) (yylval.node = (x))
# define yylval_id() (yylval.id)
#else
static inline VALUE
ripper_yylval_id(ID x)
{
    return (VALUE)NEW_LASGN(x, ID2SYM(x));
}
# define set_yylval_str(x) (void)(x)
# define set_yylval_num(x) (void)(x)
# define set_yylval_id(x)  (void)(x)
# define set_yylval_name(x) (void)(yylval.val = ripper_yylval_id(x))
# define set_yylval_literal(x) (void)(x)
# define set_yylval_node(x) (void)(x)
# define yylval_id() yylval.id
#endif

#ifndef RIPPER
#define ripper_flush(p) (void)(p)
#else
#define ripper_flush(p) ((p)->tokp = (p)->parser_lex_p)

#define yylval_rval (*(RB_TYPE_P(yylval.val, T_NODE) ? &yylval.node->nd_rval : &yylval.val))

static int
ripper_has_scan_event(struct parser_params *parser)
{

    if (lex_p < parser->tokp) rb_raise(rb_eRuntimeError, "lex_p < tokp");
    return lex_p > parser->tokp;
}

static VALUE
ripper_scan_event_val(struct parser_params *parser, int t)
{
    VALUE str = STR_NEW(parser->tokp, lex_p - parser->tokp);
    VALUE rval = ripper_dispatch1(parser, ripper_token2eventid(t), str);
    ripper_flush(parser);
    return rval;
}

static void
ripper_dispatch_scan_event(struct parser_params *parser, int t)
{
    if (!ripper_has_scan_event(parser)) return;
    yylval_rval = ripper_scan_event_val(parser, t);
}

static void
ripper_dispatch_ignored_scan_event(struct parser_params *parser, int t)
{
    if (!ripper_has_scan_event(parser)) return;
    (void)ripper_scan_event_val(parser, t);
}

static void
ripper_dispatch_delayed_token(struct parser_params *parser, int t)
{
    int saved_line = ruby_sourceline;
    const char *saved_tokp = parser->tokp;

    ruby_sourceline = parser->delayed_line;
    parser->tokp = lex_pbeg + parser->delayed_col;
    yylval_rval = ripper_dispatch1(parser, ripper_token2eventid(t), parser->delayed);
    parser->delayed = Qnil;
    ruby_sourceline = saved_line;
    parser->tokp = saved_tokp;
}
#endif /* RIPPER */

#include "ruby/regex.h"
#include "ruby/util.h"

/* We remove any previous definition of `SIGN_EXTEND_CHAR',
   since ours (we hope) works properly with all combinations of
   machines, compilers, `char' and `unsigned char' argument types.
   (Per Bothner suggested the basic approach.)  */
#undef SIGN_EXTEND_CHAR
#if __STDC__
# define SIGN_EXTEND_CHAR(c) ((signed char)(c))
#else  /* not __STDC__ */
/* As in Harbison and Steele.  */
# define SIGN_EXTEND_CHAR(c) ((((unsigned char)(c)) ^ 128) - 128)
#endif

#define parser_encoding_name()  (current_enc->name)
#define parser_mbclen()  mbclen((lex_p-1),lex_pend,current_enc)
#define parser_precise_mbclen()  rb_enc_precise_mbclen((lex_p-1),lex_pend,current_enc)
#define is_identchar(p,e,enc) (rb_enc_isalnum((unsigned char)(*(p)),(enc)) || (*(p)) == '_' || !ISASCII(*(p)))
#define parser_is_identchar() (!parser->eofp && is_identchar((lex_p-1),lex_pend,current_enc))

#define parser_isascii() ISASCII(*(lex_p-1))

#ifndef RIPPER
static int
token_info_get_column(struct parser_params *parser, const char *token)
{
    int column = 1;
    const char *p, *pend = lex_p - strlen(token);
    for (p = lex_pbeg; p < pend; p++) {
	if (*p == '\t') {
	    column = (((column - 1) / 8) + 1) * 8;
	}
	column++;
    }
    return column;
}

static int
token_info_has_nonspaces(struct parser_params *parser, const char *token)
{
    const char *p, *pend = lex_p - strlen(token);
    for (p = lex_pbeg; p < pend; p++) {
	if (*p != ' ' && *p != '\t') {
	    return 1;
	}
    }
    return 0;
}

#undef token_info_push
static void
token_info_push(struct parser_params *parser, const char *token)
{
    token_info *ptinfo;

    if (!parser->parser_token_info_enabled) return;
    ptinfo = ALLOC(token_info);
    ptinfo->token = token;
    ptinfo->linenum = ruby_sourceline;
    ptinfo->column = token_info_get_column(parser, token);
    ptinfo->nonspc = token_info_has_nonspaces(parser, token);
    ptinfo->next = parser->parser_token_info;

    parser->parser_token_info = ptinfo;
}

#undef token_info_pop
static void
token_info_pop(struct parser_params *parser, const char *token)
{
    int linenum;
    token_info *ptinfo = parser->parser_token_info;

    if (!ptinfo) return;
    parser->parser_token_info = ptinfo->next;
    if (token_info_get_column(parser, token) == ptinfo->column) { /* OK */
	goto finish;
    }
    linenum = ruby_sourceline;
    if (linenum == ptinfo->linenum) { /* SKIP */
	goto finish;
    }
    if (token_info_has_nonspaces(parser, token) || ptinfo->nonspc) { /* SKIP */
	goto finish;
    }
    if (parser->parser_token_info_enabled) {
	rb_compile_warn(ruby_sourcefile, linenum,
			"mismatched indentations at '%s' with '%s' at %d",
			token, ptinfo->token, ptinfo->linenum);
    }

  finish:
    xfree(ptinfo);
}
#endif	/* RIPPER */

static int
parser_yyerror(struct parser_params *parser, const char *msg)
{
#ifndef RIPPER
    const int max_line_margin = 30;
    const char *p, *pe;
    char *buf;
    long len;
    int i;

    compile_error(PARSER_ARG "%s", msg);
    p = lex_p;
    while (lex_pbeg <= p) {
	if (*p == '\n') break;
	p--;
    }
    p++;

    pe = lex_p;
    while (pe < lex_pend) {
	if (*pe == '\n') break;
	pe++;
    }

    len = pe - p;
    if (len > 4) {
	char *p2;
	const char *pre = "", *post = "";

	if (len > max_line_margin * 2 + 10) {
	    if (lex_p - p > max_line_margin) {
		p = rb_enc_prev_char(p, lex_p - max_line_margin, pe, rb_enc_get(lex_lastline));
		pre = "...";
	    }
	    if (pe - lex_p > max_line_margin) {
		pe = rb_enc_prev_char(lex_p, lex_p + max_line_margin, pe, rb_enc_get(lex_lastline));
		post = "...";
	    }
	    len = pe - p;
	}
	buf = ALLOCA_N(char, len+2);
	MEMCPY(buf, p, char, len);
	buf[len] = '\0';
	rb_compile_error_with_enc(NULL, 0, (void *)current_enc, "%s%s%s", pre, buf, post);

	i = (int)(lex_p - p);
	p2 = buf; pe = buf + len;

	while (p2 < pe) {
	    if (*p2 != '\t') *p2 = ' ';
	    p2++;
	}
	buf[i] = '^';
	buf[i+1] = '\0';
	rb_compile_error_append("%s%s", pre, buf);
    }
#else
    dispatch1(parse_error, STR_NEW2(msg));
#endif /* !RIPPER */
    return 0;
}

static void parser_prepare(struct parser_params *parser);

#ifndef RIPPER
static VALUE
debug_lines(VALUE fname)
{
    ID script_lines;
    CONST_ID(script_lines, "SCRIPT_LINES__");
    if (rb_const_defined_at(rb_cObject, script_lines)) {
	VALUE hash = rb_const_get_at(rb_cObject, script_lines);
	if (RB_TYPE_P(hash, T_HASH)) {
	    VALUE lines = rb_ary_new();
	    rb_hash_aset(hash, fname, lines);
	    return lines;
	}
    }
    return 0;
}

static VALUE
coverage(VALUE fname, int n)
{
    VALUE coverages = rb_get_coverages();
    if (RTEST(coverages) && RBASIC(coverages)->klass == 0) {
	VALUE lines = rb_ary_tmp_new_fill(n);
	rb_hash_aset(coverages, fname, lines);
	return lines;
    }
    return 0;
}

static int
e_option_supplied(struct parser_params *parser)
{
    return strcmp(ruby_sourcefile, "-e") == 0;
}

static VALUE
yycompile0(VALUE arg)
{
    int n;
    NODE *tree;
    struct parser_params *parser = (struct parser_params *)arg;

    if (!compile_for_eval && rb_safe_level() == 0) {
	ruby_debug_lines = debug_lines(ruby_sourcefile_string);
	if (ruby_debug_lines && ruby_sourceline > 0) {
	    VALUE str = STR_NEW0();
	    n = ruby_sourceline;
	    do {
		rb_ary_push(ruby_debug_lines, str);
	    } while (--n);
	}

	if (!e_option_supplied(parser)) {
	    ruby_coverage = coverage(ruby_sourcefile_string, ruby_sourceline);
	}
    }
    parser->last_cr_line = ruby_sourceline - 1;

    parser_prepare(parser);
    deferred_nodes = 0;
#ifndef RIPPER
    parser->parser_token_info_enabled = !compile_for_eval && RTEST(ruby_verbose);
#endif
#ifndef RIPPER
    if (RUBY_DTRACE_PARSE_BEGIN_ENABLED()) {
	RUBY_DTRACE_PARSE_BEGIN(parser->parser_ruby_sourcefile,
				parser->parser_ruby_sourceline);
    }
#endif
    n = yyparse((void*)parser);
#ifndef RIPPER
    if (RUBY_DTRACE_PARSE_END_ENABLED()) {
	RUBY_DTRACE_PARSE_END(parser->parser_ruby_sourcefile,
			      parser->parser_ruby_sourceline);
    }
#endif
    ruby_debug_lines = 0;
    ruby_coverage = 0;
    compile_for_eval = 0;

    lex_strterm = 0;
    lex_p = lex_pbeg = lex_pend = 0;
    lex_lastline = lex_nextline = 0;
    if (parser->nerr) {
	return 0;
    }
    tree = ruby_eval_tree;
    if (!tree) {
	tree = NEW_NIL();
    }
    else if (ruby_eval_tree_begin) {
	tree->nd_body = NEW_PRELUDE(ruby_eval_tree_begin, tree->nd_body);
    }
    return (VALUE)tree;
}

static NODE*
yycompile(struct parser_params *parser, VALUE fname, int line)
{
    ruby_sourcefile_string = rb_str_new_frozen(fname);
    ruby_sourcefile = RSTRING_PTR(fname);
    ruby_sourceline = line - 1;
    return (NODE *)rb_suppress_tracing(yycompile0, (VALUE)parser);
}
#endif /* !RIPPER */

static rb_encoding *
must_be_ascii_compatible(VALUE s)
{
    rb_encoding *enc = rb_enc_get(s);
    if (!rb_enc_asciicompat(enc)) {
	rb_raise(rb_eArgError, "invalid source encoding");
    }
    return enc;
}

static VALUE
lex_get_str(struct parser_params *parser, VALUE s)
{
    char *beg, *end, *start;
    long len;

    beg = RSTRING_PTR(s);
    len = RSTRING_LEN(s);
    start = beg;
    if (lex_gets_ptr) {
	if (len == lex_gets_ptr) return Qnil;
	beg += lex_gets_ptr;
	len -= lex_gets_ptr;
    }
    end = memchr(beg, '\n', len);
    if (end) len = ++end - beg;
    lex_gets_ptr += len;
    return rb_str_subseq(s, beg - start, len);
}

static VALUE
lex_getline(struct parser_params *parser)
{
    VALUE line = (*parser->parser_lex_gets)(parser, parser->parser_lex_input);
    if (NIL_P(line)) return line;
    must_be_ascii_compatible(line);
#ifndef RIPPER
    if (ruby_debug_lines) {
	rb_enc_associate(line, current_enc);
	rb_ary_push(ruby_debug_lines, line);
    }
    if (ruby_coverage) {
	rb_ary_push(ruby_coverage, Qnil);
    }
#endif
    return line;
}

#ifdef RIPPER
static rb_data_type_t parser_data_type;
#else
static const rb_data_type_t parser_data_type;

static NODE*
parser_compile_string(volatile VALUE vparser, VALUE fname, VALUE s, int line)
{
    struct parser_params *parser;
    NODE *node;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    lex_gets = lex_get_str;
    lex_gets_ptr = 0;
    lex_input = rb_str_new_frozen(s);
    lex_pbeg = lex_p = lex_pend = 0;
    compile_for_eval = rb_parse_in_eval();

    node = yycompile(parser, fname, line);
    RB_GC_GUARD(vparser); /* prohibit tail call optimization */

    return node;
}

NODE*
rb_compile_string(const char *f, VALUE s, int line)
{
    must_be_ascii_compatible(s);
    return parser_compile_string(rb_parser_new(), rb_filesystem_str_new_cstr(f), s, line);
}

NODE*
rb_parser_compile_string(volatile VALUE vparser, const char *f, VALUE s, int line)
{
    return rb_parser_compile_string_path(vparser, rb_filesystem_str_new_cstr(f), s, line);
}

NODE*
rb_parser_compile_string_path(volatile VALUE vparser, VALUE f, VALUE s, int line)
{
    must_be_ascii_compatible(s);
    return parser_compile_string(vparser, f, s, line);
}

NODE*
rb_compile_cstr(const char *f, const char *s, int len, int line)
{
    VALUE str = rb_str_new(s, len);
    return parser_compile_string(rb_parser_new(), rb_filesystem_str_new_cstr(f), str, line);
}

NODE*
rb_parser_compile_cstr(volatile VALUE vparser, const char *f, const char *s, int len, int line)
{
    VALUE str = rb_str_new(s, len);
    return parser_compile_string(vparser, rb_filesystem_str_new_cstr(f), str, line);
}

static VALUE
lex_io_gets(struct parser_params *parser, VALUE io)
{
    return rb_io_gets(io);
}

NODE*
rb_compile_file(const char *f, VALUE file, int start)
{
    VALUE volatile vparser = rb_parser_new();

    return rb_parser_compile_file(vparser, f, file, start);
}

NODE*
rb_parser_compile_file(volatile VALUE vparser, const char *f, VALUE file, int start)
{
    return rb_parser_compile_file_path(vparser, rb_filesystem_str_new_cstr(f), file, start);
}

NODE*
rb_parser_compile_file_path(volatile VALUE vparser, VALUE fname, VALUE file, int start)
{
    struct parser_params *parser;
    NODE *node;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    lex_gets = lex_io_gets;
    lex_input = file;
    lex_pbeg = lex_p = lex_pend = 0;
    compile_for_eval = rb_parse_in_eval();

    node = yycompile(parser, fname, start);
    RB_GC_GUARD(vparser); /* prohibit tail call optimization */

    return node;
}
#endif  /* !RIPPER */

#define STR_FUNC_ESCAPE 0x01
#define STR_FUNC_EXPAND 0x02
#define STR_FUNC_REGEXP 0x04
#define STR_FUNC_QWORDS 0x08
#define STR_FUNC_SYMBOL 0x10
#define STR_FUNC_INDENT 0x20

enum string_type {
    str_squote = (0),
    str_dquote = (STR_FUNC_EXPAND),
    str_xquote = (STR_FUNC_EXPAND),
    str_regexp = (STR_FUNC_REGEXP|STR_FUNC_ESCAPE|STR_FUNC_EXPAND),
    str_sword  = (STR_FUNC_QWORDS),
    str_dword  = (STR_FUNC_QWORDS|STR_FUNC_EXPAND),
    str_ssym   = (STR_FUNC_SYMBOL),
    str_dsym   = (STR_FUNC_SYMBOL|STR_FUNC_EXPAND)
};

static VALUE
parser_str_new(const char *p, long n, rb_encoding *enc, int func, rb_encoding *enc0)
{
    VALUE str;

    str = rb_enc_str_new(p, n, enc);
    if (!(func & STR_FUNC_REGEXP) && rb_enc_asciicompat(enc)) {
	if (rb_enc_str_coderange(str) == ENC_CODERANGE_7BIT) {
	}
	else if (enc0 == rb_usascii_encoding() && enc != rb_utf8_encoding()) {
	    rb_enc_associate(str, rb_ascii8bit_encoding());
	}
    }

    return str;
}

#define lex_goto_eol(parser) ((parser)->parser_lex_p = (parser)->parser_lex_pend)
#define lex_eol_p() (lex_p >= lex_pend)
#define peek(c) peek_n((c), 0)
#define peek_n(c,n) (lex_p+(n) < lex_pend && (c) == (unsigned char)lex_p[n])
#define peekc() peekc_n(0)
#define peekc_n(n) (lex_p+(n) < lex_pend ? (unsigned char)lex_p[n] : -1)

static inline int
parser_nextc(struct parser_params *parser)
{
    int c;

    if (lex_p == lex_pend) {
	VALUE v = lex_nextline;
	lex_nextline = 0;
	if (!v) {
	    if (parser->eofp)
		return -1;

	    if (!lex_input || NIL_P(v = lex_getline(parser))) {
		parser->eofp = Qtrue;
		lex_goto_eol(parser);
		return -1;
	    }
	}
	{
#ifdef RIPPER
	    if (parser->tokp < lex_pend) {
		if (NIL_P(parser->delayed)) {
		    parser->delayed = rb_str_buf_new(1024);
		    rb_enc_associate(parser->delayed, current_enc);
		    rb_str_buf_cat(parser->delayed,
				   parser->tokp, lex_pend - parser->tokp);
		    parser->delayed_line = ruby_sourceline;
		    parser->delayed_col = (int)(parser->tokp - lex_pbeg);
		}
		else {
		    rb_str_buf_cat(parser->delayed,
				   parser->tokp, lex_pend - parser->tokp);
		}
	    }
#endif
	    if (heredoc_end > 0) {
		ruby_sourceline = heredoc_end;
		heredoc_end = 0;
	    }
	    ruby_sourceline++;
	    parser->line_count++;
	    lex_pbeg = lex_p = RSTRING_PTR(v);
	    lex_pend = lex_p + RSTRING_LEN(v);
	    ripper_flush(parser);
	    lex_lastline = v;
	}
    }
    c = (unsigned char)*lex_p++;
    if (c == '\r') {
	if (peek('\n')) {
	    lex_p++;
	    c = '\n';
	}
	else if (ruby_sourceline > parser->last_cr_line) {
	    parser->last_cr_line = ruby_sourceline;
	    rb_compile_warn(ruby_sourcefile, ruby_sourceline, "encountered \\r in middle of line, treated as a mere space");
	}
    }

    return c;
}

static void
parser_pushback(struct parser_params *parser, int c)
{
    if (c == -1) return;
    lex_p--;
    if (lex_p > lex_pbeg && lex_p[0] == '\n' && lex_p[-1] == '\r') {
	lex_p--;
    }
}

#define was_bol() (lex_p == lex_pbeg + 1)

#define tokfix() (tokenbuf[tokidx]='\0')
#define tok() tokenbuf
#define toklen() tokidx
#define toklast() (tokidx>0?tokenbuf[tokidx-1]:0)

static char*
parser_newtok(struct parser_params *parser)
{
    tokidx = 0;
    tokline = ruby_sourceline;
    if (!tokenbuf) {
	toksiz = 60;
	tokenbuf = ALLOC_N(char, 60);
    }
    if (toksiz > 4096) {
	toksiz = 60;
	REALLOC_N(tokenbuf, char, 60);
    }
    return tokenbuf;
}

static char *
parser_tokspace(struct parser_params *parser, int n)
{
    tokidx += n;

    if (tokidx >= toksiz) {
	do {toksiz *= 2;} while (toksiz < tokidx);
	REALLOC_N(tokenbuf, char, toksiz);
    }
    return &tokenbuf[tokidx-n];
}

static void
parser_tokadd(struct parser_params *parser, int c)
{
    tokenbuf[tokidx++] = (char)c;
    if (tokidx >= toksiz) {
	toksiz *= 2;
	REALLOC_N(tokenbuf, char, toksiz);
    }
}

static int
parser_tok_hex(struct parser_params *parser, size_t *numlen)
{
    int c;

    c = scan_hex(lex_p, 2, numlen);
    if (!*numlen) {
	yyerror("invalid hex escape");
	return 0;
    }
    lex_p += *numlen;
    return c;
}

#define tokcopy(n) memcpy(tokspace(n), lex_p - (n), (n))

/* return value is for ?\u3042 */
static int
parser_tokadd_utf8(struct parser_params *parser, rb_encoding **encp,
                   int string_literal, int symbol_literal, int regexp_literal)
{
    /*
     * If string_literal is true, then we allow multiple codepoints
     * in \u{}, and add the codepoints to the current token.
     * Otherwise we're parsing a character literal and return a single
     * codepoint without adding it
     */

    int codepoint;
    size_t numlen;

    if (regexp_literal) { tokadd('\\'); tokadd('u'); }

    if (peek('{')) {  /* handle \u{...} form */
	do {
            if (regexp_literal) { tokadd(*lex_p); }
	    nextc();
	    codepoint = scan_hex(lex_p, 6, &numlen);
	    if (numlen == 0)  {
		yyerror("invalid Unicode escape");
		return 0;
	    }
	    if (codepoint > 0x10ffff) {
		yyerror("invalid Unicode codepoint (too large)");
		return 0;
	    }
	    lex_p += numlen;
            if (regexp_literal) {
                tokcopy((int)numlen);
            }
            else if (codepoint >= 0x80) {
		*encp = rb_utf8_encoding();
		if (string_literal) tokaddmbc(codepoint, *encp);
	    }
	    else if (string_literal) {
		tokadd(codepoint);
	    }
	} while (string_literal && (peek(' ') || peek('\t')));

	if (!peek('}')) {
	    yyerror("unterminated Unicode escape");
	    return 0;
	}

        if (regexp_literal) { tokadd('}'); }
	nextc();
    }
    else {			/* handle \uxxxx form */
	codepoint = scan_hex(lex_p, 4, &numlen);
	if (numlen < 4) {
	    yyerror("invalid Unicode escape");
	    return 0;
	}
	lex_p += 4;
        if (regexp_literal) {
            tokcopy(4);
        }
	else if (codepoint >= 0x80) {
	    *encp = rb_utf8_encoding();
	    if (string_literal) tokaddmbc(codepoint, *encp);
	}
	else if (string_literal) {
	    tokadd(codepoint);
	}
    }

    return codepoint;
}

#define ESCAPE_CONTROL 1
#define ESCAPE_META    2

static int
parser_read_escape(struct parser_params *parser, int flags,
		   rb_encoding **encp)
{
    int c;
    size_t numlen;

    switch (c = nextc()) {
      case '\\':	/* Backslash */
	return c;

      case 'n':	/* newline */
	return '\n';

      case 't':	/* horizontal tab */
	return '\t';

      case 'r':	/* carriage-return */
	return '\r';

      case 'f':	/* form-feed */
	return '\f';

      case 'v':	/* vertical tab */
	return '\13';

      case 'a':	/* alarm(bell) */
	return '\007';

      case 'e':	/* escape */
	return 033;

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	pushback(c);
	c = scan_oct(lex_p, 3, &numlen);
	lex_p += numlen;
	return c;

      case 'x':	/* hex constant */
	c = tok_hex(&numlen);
	if (numlen == 0) return 0;
	return c;

      case 'b':	/* backspace */
	return '\010';

      case 's':	/* space */
	return ' ';

      case 'M':
	if (flags & ESCAPE_META) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	if ((c = nextc()) == '\\') {
	    if (peek('u')) goto eof;
	    return read_escape(flags|ESCAPE_META, encp) | 0x80;
	}
	else if (c == -1 || !ISASCII(c)) goto eof;
	else {
	    return ((c & 0xff) | 0x80);
	}

      case 'C':
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
      case 'c':
	if (flags & ESCAPE_CONTROL) goto eof;
	if ((c = nextc())== '\\') {
	    if (peek('u')) goto eof;
	    c = read_escape(flags|ESCAPE_CONTROL, encp);
	}
	else if (c == '?')
	    return 0177;
	else if (c == -1 || !ISASCII(c)) goto eof;
	return c & 0x9f;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return '\0';

      default:
	return c;
    }
}

static void
parser_tokaddmbc(struct parser_params *parser, int c, rb_encoding *enc)
{
    int len = rb_enc_codelen(c, enc);
    rb_enc_mbcput(c, tokspace(len), enc);
}

static int
parser_tokadd_escape(struct parser_params *parser, rb_encoding **encp)
{
    int c;
    int flags = 0;
    size_t numlen;

  first:
    switch (c = nextc()) {
      case '\n':
	return 0;		/* just ignore */

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	{
	    ruby_scan_oct(--lex_p, 3, &numlen);
	    if (numlen == 0) goto eof;
	    lex_p += numlen;
	    tokcopy((int)numlen + 1);
	}
	return 0;

      case 'x':	/* hex constant */
	{
	    tok_hex(&numlen);
	    if (numlen == 0) return -1;
	    tokcopy((int)numlen + 2);
	}
	return 0;

      case 'M':
	if (flags & ESCAPE_META) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	tokcopy(3);
	flags |= ESCAPE_META;
	goto escaped;

      case 'C':
	if (flags & ESCAPE_CONTROL) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	tokcopy(3);
	goto escaped;

      case 'c':
	if (flags & ESCAPE_CONTROL) goto eof;
	tokcopy(2);
	flags |= ESCAPE_CONTROL;
      escaped:
	if ((c = nextc()) == '\\') {
	    goto first;
	}
	else if (c == -1) goto eof;
	tokadd(c);
	return 0;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return -1;

      default:
        tokadd('\\');
	tokadd(c);
    }
    return 0;
}

static int
parser_regx_options(struct parser_params *parser)
{
    int kcode = 0;
    int kopt = 0;
    int options = 0;
    int c, opt, kc;

    newtok();
    while (c = nextc(), ISALPHA(c)) {
        if (c == 'o') {
            options |= RE_OPTION_ONCE;
        }
        else if (rb_char_to_option_kcode(c, &opt, &kc)) {
	    if (kc >= 0) {
		if (kc != rb_ascii8bit_encindex()) kcode = c;
		kopt = opt;
	    }
	    else {
		options |= opt;
	    }
        }
        else {
	    tokadd(c);
        }
    }
    options |= kopt;
    pushback(c);
    if (toklen()) {
	tokfix();
	compile_error(PARSER_ARG "unknown regexp option%s - %s",
		      toklen() > 1 ? "s" : "", tok());
    }
    return options | RE_OPTION_ENCODING(kcode);
}

static void
dispose_string(VALUE str)
{
    rb_str_free(str);
    rb_gc_force_recycle(str);
}

static int
parser_tokadd_mbchar(struct parser_params *parser, int c)
{
    int len = parser_precise_mbclen();
    if (!MBCLEN_CHARFOUND_P(len)) {
	compile_error(PARSER_ARG "invalid multibyte char (%s)", parser_encoding_name());
	return -1;
    }
    tokadd(c);
    lex_p += --len;
    if (len > 0) tokcopy(len);
    return c;
}

#define tokadd_mbchar(c) parser_tokadd_mbchar(parser, (c))

static inline int
simple_re_meta(int c)
{
    switch (c) {
      case '$': case '*': case '+': case '.':
      case '?': case '^': case '|':
      case ')': case ']': case '}': case '>':
	return TRUE;
      default:
	return FALSE;
    }
}

static int
parser_tokadd_string(struct parser_params *parser,
		     int func, int term, int paren, long *nest,
		     rb_encoding **encp)
{
    int c;
    int has_nonascii = 0;
    rb_encoding *enc = *encp;
    char *errbuf = 0;
    static const char mixed_msg[] = "%s mixed within %s source";

#define mixed_error(enc1, enc2) if (!errbuf) {	\
	size_t len = sizeof(mixed_msg) - 4;	\
	len += strlen(rb_enc_name(enc1));	\
	len += strlen(rb_enc_name(enc2));	\
	errbuf = ALLOCA_N(char, len);		\
	snprintf(errbuf, len, mixed_msg,	\
		 rb_enc_name(enc1),		\
		 rb_enc_name(enc2));		\
	yyerror(errbuf);			\
    }
#define mixed_escape(beg, enc1, enc2) do {	\
	const char *pos = lex_p;		\
	lex_p = (beg);				\
	mixed_error((enc1), (enc2));		\
	lex_p = pos;				\
    } while (0)

    while ((c = nextc()) != -1) {
	if (paren && c == paren) {
	    ++*nest;
	}
	else if (c == term) {
	    if (!nest || !*nest) {
		pushback(c);
		break;
	    }
	    --*nest;
	}
	else if ((func & STR_FUNC_EXPAND) && c == '#' && lex_p < lex_pend) {
	    int c2 = *lex_p;
	    if (c2 == '$' || c2 == '@' || c2 == '{') {
		pushback(c);
		break;
	    }
	}
	else if (c == '\\') {
	    const char *beg = lex_p - 1;
	    c = nextc();
	    switch (c) {
	      case '\n':
		if (func & STR_FUNC_QWORDS) break;
		if (func & STR_FUNC_EXPAND) continue;
		tokadd('\\');
		break;

	      case '\\':
		if (func & STR_FUNC_ESCAPE) tokadd(c);
		break;

	      case 'u':
		if ((func & STR_FUNC_EXPAND) == 0) {
		    tokadd('\\');
		    break;
		}
		parser_tokadd_utf8(parser, &enc, 1,
				   func & STR_FUNC_SYMBOL,
                                   func & STR_FUNC_REGEXP);
		if (has_nonascii && enc != *encp) {
		    mixed_escape(beg, enc, *encp);
		}
		continue;

	      default:
		if (c == -1) return -1;
		if (!ISASCII(c)) {
		    if ((func & STR_FUNC_EXPAND) == 0) tokadd('\\');
		    goto non_ascii;
		}
		if (func & STR_FUNC_REGEXP) {
		    if (c == term && !simple_re_meta(c)) {
			tokadd(c);
			continue;
		    }
		    pushback(c);
		    if ((c = tokadd_escape(&enc)) < 0)
			return -1;
		    if (has_nonascii && enc != *encp) {
			mixed_escape(beg, enc, *encp);
		    }
		    continue;
		}
		else if (func & STR_FUNC_EXPAND) {
		    pushback(c);
		    if (func & STR_FUNC_ESCAPE) tokadd('\\');
		    c = read_escape(0, &enc);
		}
		else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
		    /* ignore backslashed spaces in %w */
		}
		else if (c != term && !(paren && c == paren)) {
		    tokadd('\\');
		    pushback(c);
		    continue;
		}
	    }
	}
	else if (!parser_isascii()) {
	  non_ascii:
	    has_nonascii = 1;
	    if (enc != *encp) {
		mixed_error(enc, *encp);
		continue;
	    }
	    if (tokadd_mbchar(c) == -1) return -1;
	    continue;
	}
	else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	    pushback(c);
	    break;
	}
        if (c & 0x80) {
	    has_nonascii = 1;
	    if (enc != *encp) {
		mixed_error(enc, *encp);
		continue;
	    }
        }
	tokadd(c);
    }
    *encp = enc;
    return c;
}

#define NEW_STRTERM(func, term, paren) \
	rb_node_newnode(NODE_STRTERM, (func), (term) | ((paren) << (CHAR_BIT * 2)), 0)

#ifdef RIPPER
static void
ripper_flush_string_content(struct parser_params *parser, rb_encoding *enc)
{
    if (!NIL_P(parser->delayed)) {
	ptrdiff_t len = lex_p - parser->tokp;
	if (len > 0) {
	    rb_enc_str_buf_cat(parser->delayed, parser->tokp, len, enc);
	}
	ripper_dispatch_delayed_token(parser, tSTRING_CONTENT);
	parser->tokp = lex_p;
    }
}

#define flush_string_content(enc) ripper_flush_string_content(parser, (enc))
#else
#define flush_string_content(enc) ((void)(enc))
#endif

RUBY_FUNC_EXPORTED const unsigned int ruby_global_name_punct_bits[(0x7e - 0x20 + 31) / 32];
/* this can be shared with ripper, since it's independent from struct
 * parser_params. */
#ifndef RIPPER
#define BIT(c, idx) (((c) / 32 - 1 == idx) ? (1U << ((c) % 32)) : 0)
#define SPECIAL_PUNCT(idx) ( \
	BIT('~', idx) | BIT('*', idx) | BIT('$', idx) | BIT('?', idx) | \
	BIT('!', idx) | BIT('@', idx) | BIT('/', idx) | BIT('\\', idx) | \
	BIT(';', idx) | BIT(',', idx) | BIT('.', idx) | BIT('=', idx) | \
	BIT(':', idx) | BIT('<', idx) | BIT('>', idx) | BIT('\"', idx) | \
	BIT('&', idx) | BIT('`', idx) | BIT('\'', idx) | BIT('+', idx) | \
	BIT('0', idx))
const unsigned int ruby_global_name_punct_bits[] = {
    SPECIAL_PUNCT(0),
    SPECIAL_PUNCT(1),
    SPECIAL_PUNCT(2),
};
#undef BIT
#undef SPECIAL_PUNCT
#endif

static int
parser_peek_variable_name(struct parser_params *parser)
{
    int c;
    const char *p = lex_p;

    if (p + 1 >= lex_pend) return 0;
    c = *p++;
    switch (c) {
      case '$':
	if ((c = *p) == '-') {
	    if (++p >= lex_pend) return 0;
	    c = *p;
	}
	else if (is_global_name_punct(c) || ISDIGIT(c)) {
	    return tSTRING_DVAR;
	}
	break;
      case '@':
	if ((c = *p) == '@') {
	    if (++p >= lex_pend) return 0;
	    c = *p;
	}
	break;
      case '{':
	lex_p = p;
	command_start = TRUE;
	return tSTRING_DBEG;
      default:
	return 0;
    }
    if (!ISASCII(c) || c == '_' || ISALPHA(c))
	return tSTRING_DVAR;
    return 0;
}

static int
parser_parse_string(struct parser_params *parser, NODE *quote)
{
    int func = (int)quote->nd_func;
    int term = nd_term(quote);
    int paren = nd_paren(quote);
    int c, space = 0;
    rb_encoding *enc = current_enc;

    if (func == -1) return tSTRING_END;
    c = nextc();
    if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	do {c = nextc();} while (ISSPACE(c));
	space = 1;
    }
    if (c == term && !quote->nd_nest) {
	if (func & STR_FUNC_QWORDS) {
	    quote->nd_func = -1;
	    return ' ';
	}
	if (!(func & STR_FUNC_REGEXP)) return tSTRING_END;
        set_yylval_num(regx_options());
	return tREGEXP_END;
    }
    if (space) {
	pushback(c);
	return ' ';
    }
    newtok();
    if ((func & STR_FUNC_EXPAND) && c == '#') {
	int t = parser_peek_variable_name(parser);
	if (t) return t;
	tokadd('#');
	c = nextc();
    }
    pushback(c);
    if (tokadd_string(func, term, paren, &quote->nd_nest,
		      &enc) == -1) {
	ruby_sourceline = nd_line(quote);
	if (func & STR_FUNC_REGEXP) {
	    if (parser->eofp)
		compile_error(PARSER_ARG "unterminated regexp meets end of file");
	    return tREGEXP_END;
	}
	else {
	    if (parser->eofp)
		compile_error(PARSER_ARG "unterminated string meets end of file");
	    return tSTRING_END;
	}
    }

    tokfix();
    set_yylval_str(STR_NEW3(tok(), toklen(), enc, func));
    flush_string_content(enc);

    return tSTRING_CONTENT;
}

static int
parser_heredoc_identifier(struct parser_params *parser)
{
    int c = nextc(), term, func = 0;
    long len;

    if (c == '-') {
	c = nextc();
	func = STR_FUNC_INDENT;
    }
    switch (c) {
      case '\'':
	func |= str_squote; goto quoted;
      case '"':
	func |= str_dquote; goto quoted;
      case '`':
	func |= str_xquote;
      quoted:
	newtok();
	tokadd(func);
	term = c;
	while ((c = nextc()) != -1 && c != term) {
	    if (tokadd_mbchar(c) == -1) return 0;
	}
	if (c == -1) {
	    compile_error(PARSER_ARG "unterminated here document identifier");
	    return 0;
	}
	break;

      default:
	if (!parser_is_identchar()) {
	    pushback(c);
	    if (func & STR_FUNC_INDENT) {
		pushback('-');
	    }
	    return 0;
	}
	newtok();
	term = '"';
	tokadd(func |= str_dquote);
	do {
	    if (tokadd_mbchar(c) == -1) return 0;
	} while ((c = nextc()) != -1 && parser_is_identchar());
	pushback(c);
	break;
    }

    tokfix();
#ifdef RIPPER
    ripper_dispatch_scan_event(parser, tHEREDOC_BEG);
#endif
    len = lex_p - lex_pbeg;
    lex_goto_eol(parser);
    lex_strterm = rb_node_newnode(NODE_HEREDOC,
				  STR_NEW(tok(), toklen()),	/* nd_lit */
				  len,				/* nd_nth */
				  lex_lastline);		/* nd_orig */
    nd_set_line(lex_strterm, ruby_sourceline);
    ripper_flush(parser);
    return term == '`' ? tXSTRING_BEG : tSTRING_BEG;
}

static void
parser_heredoc_restore(struct parser_params *parser, NODE *here)
{
    VALUE line;

    lex_strterm = 0;
    line = here->nd_orig;
    lex_lastline = line;
    lex_pbeg = RSTRING_PTR(line);
    lex_pend = lex_pbeg + RSTRING_LEN(line);
    lex_p = lex_pbeg + here->nd_nth;
    heredoc_end = ruby_sourceline;
    ruby_sourceline = nd_line(here);
    dispose_string(here->nd_lit);
    rb_gc_force_recycle((VALUE)here);
    ripper_flush(parser);
}

static int
parser_whole_match_p(struct parser_params *parser,
    const char *eos, long len, int indent)
{
    const char *p = lex_pbeg;
    long n;

    if (indent) {
	while (*p && ISSPACE(*p)) p++;
    }
    n = lex_pend - (p + len);
    if (n < 0) return FALSE;
    if (n > 0 && p[len] != '\n') {
	if (p[len] != '\r') return FALSE;
	if (n <= 1 || p[len+1] != '\n') return FALSE;
    }
    return strncmp(eos, p, len) == 0;
}

#define NUM_SUFFIX_R   (1<<0)
#define NUM_SUFFIX_I   (1<<1)
#define NUM_SUFFIX_ALL 3

static int
parser_number_literal_suffix(struct parser_params *parser, int mask)
{
    int c, result = 0;
    const char *lastp = lex_p;

    while ((c = nextc()) != -1) {
	if ((mask & NUM_SUFFIX_I) && c == 'i') {
	    result |= (mask & NUM_SUFFIX_I);
	    mask &= ~NUM_SUFFIX_I;
	    /* r after i, rational of complex is disallowed */
	    mask &= ~NUM_SUFFIX_R;
	    continue;
	}
	if ((mask & NUM_SUFFIX_R) && c == 'r') {
	    result |= (mask & NUM_SUFFIX_R);
	    mask &= ~NUM_SUFFIX_R;
	    continue;
	}
	if (!ISASCII(c) || ISALPHA(c) || c == '_') {
	    lex_p = lastp;
	    return 0;
	}
	pushback(c);
	if (c == '.') {
	    c = peekc_n(1);
	    if (ISDIGIT(c)) {
		yyerror("unexpected fraction part after numeric literal");
		lex_p += 2;
		while (parser_is_identchar()) nextc();
	    }
	}
	break;
    }
    return result;
}

static int
parser_set_number_literal(struct parser_params *parser, VALUE v, int type, int suffix)
{
    if (suffix & NUM_SUFFIX_I) {
	v = rb_complex_raw(INT2FIX(0), v);
	type = tIMAGINARY;
    }
    set_yylval_literal(v);
    return type;
}

static int
parser_set_integer_literal(struct parser_params *parser, VALUE v, int suffix)
{
    int type = tINTEGER;
    if (suffix & NUM_SUFFIX_R) {
	v = rb_rational_raw1(v);
	type = tRATIONAL;
    }
    return set_number_literal(v, type, suffix);
}

#ifdef RIPPER
static void
ripper_dispatch_heredoc_end(struct parser_params *parser)
{
    if (!NIL_P(parser->delayed))
	ripper_dispatch_delayed_token(parser, tSTRING_CONTENT);
    lex_goto_eol(parser);
    ripper_dispatch_ignored_scan_event(parser, tHEREDOC_END);
}

#define dispatch_heredoc_end() ripper_dispatch_heredoc_end(parser)
#else
#define dispatch_heredoc_end() ((void)0)
#endif

static int
parser_here_document(struct parser_params *parser, NODE *here)
{
    int c, func, indent = 0;
    const char *eos, *p, *pend;
    long len;
    VALUE str = 0;
    rb_encoding *enc = current_enc;

    eos = RSTRING_PTR(here->nd_lit);
    len = RSTRING_LEN(here->nd_lit) - 1;
    indent = (func = *eos++) & STR_FUNC_INDENT;

    if ((c = nextc()) == -1) {
      error:
	compile_error(PARSER_ARG "can't find string \"%s\" anywhere before EOF", eos);
#ifdef RIPPER
	if (NIL_P(parser->delayed)) {
	    ripper_dispatch_scan_event(parser, tSTRING_CONTENT);
	}
	else {
	    if (str ||
		((len = lex_p - parser->tokp) > 0 &&
		 (str = STR_NEW3(parser->tokp, len, enc, func), 1))) {
		rb_str_append(parser->delayed, str);
	    }
	    ripper_dispatch_delayed_token(parser, tSTRING_CONTENT);
	}
	lex_goto_eol(parser);
#endif
      restore:
	heredoc_restore(lex_strterm);
	return 0;
    }
    if (was_bol() && whole_match_p(eos, len, indent)) {
	dispatch_heredoc_end();
	heredoc_restore(lex_strterm);
	return tSTRING_END;
    }

    if (!(func & STR_FUNC_EXPAND)) {
	do {
	    p = RSTRING_PTR(lex_lastline);
	    pend = lex_pend;
	    if (pend > p) {
		switch (pend[-1]) {
		  case '\n':
		    if (--pend == p || pend[-1] != '\r') {
			pend++;
			break;
		    }
		  case '\r':
		    --pend;
		}
	    }
	    if (str)
		rb_str_cat(str, p, pend - p);
	    else
		str = STR_NEW(p, pend - p);
	    if (pend < lex_pend) rb_str_cat(str, "\n", 1);
	    lex_goto_eol(parser);
	    if (nextc() == -1) {
		if (str) dispose_string(str);
		goto error;
	    }
	} while (!whole_match_p(eos, len, indent));
    }
    else {
	/*	int mb = ENC_CODERANGE_7BIT, *mbp = &mb;*/
	newtok();
	if (c == '#') {
	    int t = parser_peek_variable_name(parser);
	    if (t) return t;
	    tokadd('#');
	    c = nextc();
	}
	do {
	    pushback(c);
	    if ((c = tokadd_string(func, '\n', 0, NULL, &enc)) == -1) {
		if (parser->eofp) goto error;
		goto restore;
	    }
	    if (c != '\n') {
		set_yylval_str(STR_NEW3(tok(), toklen(), enc, func));
		flush_string_content(enc);
		return tSTRING_CONTENT;
	    }
	    tokadd(nextc());
	    /*	    if (mbp && mb == ENC_CODERANGE_UNKNOWN) mbp = 0;*/
	    if ((c = nextc()) == -1) goto error;
	} while (!whole_match_p(eos, len, indent));
	str = STR_NEW3(tok(), toklen(), enc, func);
    }
    dispatch_heredoc_end();
    heredoc_restore(lex_strterm);
    lex_strterm = NEW_STRTERM(-1, 0, 0);
    set_yylval_str(str);
    return tSTRING_CONTENT;
}

#include "lex.c"

static void
arg_ambiguous_gen(struct parser_params *parser, char c)
{
#ifndef RIPPER
    rb_warningS("ambiguous first argument; put parentheses or a space even after `%c' operator", c);
#else
    dispatch1(arg_ambiguous, rb_usascii_str_new(&c, 1));
#endif
}
#define arg_ambiguous(c) (arg_ambiguous_gen(parser, (c)), 1)

static ID
formal_argument_gen(struct parser_params *parser, ID lhs)
{
#ifndef RIPPER
    if (!is_local_id(lhs))
	yyerror("formal argument must be local variable");
#endif
    shadowing_lvar(lhs);
    return lhs;
}

static int
lvar_defined_gen(struct parser_params *parser, ID id)
{
    return (dyna_in_block() && dvar_defined_get(id)) || local_id(id);
}

/* emacsen -*- hack */
static long
parser_encode_length(struct parser_params *parser, const char *name, long len)
{
    long nlen;

    if (len > 5 && name[nlen = len - 5] == '-') {
	if (rb_memcicmp(name + nlen + 1, "unix", 4) == 0)
	    return nlen;
    }
    if (len > 4 && name[nlen = len - 4] == '-') {
	if (rb_memcicmp(name + nlen + 1, "dos", 3) == 0)
	    return nlen;
	if (rb_memcicmp(name + nlen + 1, "mac", 3) == 0 &&
	    !(len == 8 && rb_memcicmp(name, "utf8-mac", len) == 0))
	    /* exclude UTF8-MAC because the encoding named "UTF8" doesn't exist in Ruby */
	    return nlen;
    }
    return len;
}

static void
parser_set_encode(struct parser_params *parser, const char *name)
{
    int idx = rb_enc_find_index(name);
    rb_encoding *enc;
    VALUE excargs[3];

    if (idx < 0) {
	excargs[1] = rb_sprintf("unknown encoding name: %s", name);
      error:
	excargs[0] = rb_eArgError;
	excargs[2] = rb_make_backtrace();
	rb_ary_unshift(excargs[2], rb_sprintf("%s:%d", ruby_sourcefile, ruby_sourceline));
	rb_exc_raise(rb_make_exception(3, excargs));
    }
    enc = rb_enc_from_index(idx);
    if (!rb_enc_asciicompat(enc)) {
	excargs[1] = rb_sprintf("%s is not ASCII compatible", rb_enc_name(enc));
	goto error;
    }
    parser->enc = enc;
#ifndef RIPPER
    if (ruby_debug_lines) {
	VALUE lines = ruby_debug_lines;
	long i, n = RARRAY_LEN(lines);
	for (i = 0; i < n; ++i) {
	    rb_enc_associate_index(RARRAY_AREF(lines, i), idx);
	}
    }
#endif
}

static int
comment_at_top(struct parser_params *parser)
{
    const char *p = lex_pbeg, *pend = lex_p - 1;
    if (parser->line_count != (parser->has_shebang ? 2 : 1)) return 0;
    while (p < pend) {
	if (!ISSPACE(*p)) return 0;
	p++;
    }
    return 1;
}

#ifndef RIPPER
typedef long (*rb_magic_comment_length_t)(struct parser_params *parser, const char *name, long len);
typedef void (*rb_magic_comment_setter_t)(struct parser_params *parser, const char *name, const char *val);

static void
magic_comment_encoding(struct parser_params *parser, const char *name, const char *val)
{
    if (!comment_at_top(parser)) {
	return;
    }
    parser_set_encode(parser, val);
}

static void
parser_set_token_info(struct parser_params *parser, const char *name, const char *val)
{
    int *p = &parser->parser_token_info_enabled;

    switch (*val) {
      case 't': case 'T':
	if (strcasecmp(val, "true") == 0) {
	    *p = TRUE;
	    return;
	}
	break;
      case 'f': case 'F':
	if (strcasecmp(val, "false") == 0) {
	    *p = FALSE;
	    return;
	}
	break;
    }
    rb_compile_warning(ruby_sourcefile, ruby_sourceline, "invalid value for %s: %s", name, val);
}

struct magic_comment {
    const char *name;
    rb_magic_comment_setter_t func;
    rb_magic_comment_length_t length;
};

static const struct magic_comment magic_comments[] = {
    {"coding", magic_comment_encoding, parser_encode_length},
    {"encoding", magic_comment_encoding, parser_encode_length},
    {"warn_indent", parser_set_token_info},
};
#endif

static const char *
magic_comment_marker(const char *str, long len)
{
    long i = 2;

    while (i < len) {
	switch (str[i]) {
	  case '-':
	    if (str[i-1] == '*' && str[i-2] == '-') {
		return str + i + 1;
	    }
	    i += 2;
	    break;
	  case '*':
	    if (i + 1 >= len) return 0;
	    if (str[i+1] != '-') {
		i += 4;
	    }
	    else if (str[i-1] != '-') {
		i += 2;
	    }
	    else {
		return str + i + 2;
	    }
	    break;
	  default:
	    i += 3;
	    break;
	}
    }
    return 0;
}

static int
parser_magic_comment(struct parser_params *parser, const char *str, long len)
{
    VALUE name = 0, val = 0;
    const char *beg, *end, *vbeg, *vend;
#define str_copy(_s, _p, _n) ((_s) \
	? (void)(rb_str_resize((_s), (_n)), \
	   MEMCPY(RSTRING_PTR(_s), (_p), char, (_n)), (_s)) \
	: (void)((_s) = STR_NEW((_p), (_n))))

    if (len <= 7) return FALSE;
    if (!(beg = magic_comment_marker(str, len))) return FALSE;
    if (!(end = magic_comment_marker(beg, str + len - beg))) return FALSE;
    str = beg;
    len = end - beg - 3;

    /* %r"([^\\s\'\":;]+)\\s*:\\s*(\"(?:\\\\.|[^\"])*\"|[^\"\\s;]+)[\\s;]*" */
    while (len > 0) {
#ifndef RIPPER
	const struct magic_comment *p = magic_comments;
#endif
	char *s;
	int i;
	long n = 0;

	for (; len > 0 && *str; str++, --len) {
	    switch (*str) {
	      case '\'': case '"': case ':': case ';':
		continue;
	    }
	    if (!ISSPACE(*str)) break;
	}
	for (beg = str; len > 0; str++, --len) {
	    switch (*str) {
	      case '\'': case '"': case ':': case ';':
		break;
	      default:
		if (ISSPACE(*str)) break;
		continue;
	    }
	    break;
	}
	for (end = str; len > 0 && ISSPACE(*str); str++, --len);
	if (!len) break;
	if (*str != ':') continue;

	do str++; while (--len > 0 && ISSPACE(*str));
	if (!len) break;
	if (*str == '"') {
	    for (vbeg = ++str; --len > 0 && *str != '"'; str++) {
		if (*str == '\\') {
		    --len;
		    ++str;
		}
	    }
	    vend = str;
	    if (len) {
		--len;
		++str;
	    }
	}
	else {
	    for (vbeg = str; len > 0 && *str != '"' && *str != ';' && !ISSPACE(*str); --len, str++);
	    vend = str;
	}
	while (len > 0 && (*str == ';' || ISSPACE(*str))) --len, str++;

	n = end - beg;
	str_copy(name, beg, n);
	s = RSTRING_PTR(name);
	for (i = 0; i < n; ++i) {
	    if (s[i] == '-') s[i] = '_';
	}
#ifndef RIPPER
	do {
	    if (STRNCASECMP(p->name, s, n) == 0) {
		n = vend - vbeg;
		if (p->length) {
		    n = (*p->length)(parser, vbeg, n);
		}
		str_copy(val, vbeg, n);
		(*p->func)(parser, s, RSTRING_PTR(val));
		break;
	    }
	} while (++p < magic_comments + numberof(magic_comments));
#else
	str_copy(val, vbeg, vend - vbeg);
	dispatch2(magic_comment, name, val);
#endif
    }

    return TRUE;
}

static void
set_file_encoding(struct parser_params *parser, const char *str, const char *send)
{
    int sep = 0;
    const char *beg = str;
    VALUE s;

    for (;;) {
	if (send - str <= 6) return;
	switch (str[6]) {
	  case 'C': case 'c': str += 6; continue;
	  case 'O': case 'o': str += 5; continue;
	  case 'D': case 'd': str += 4; continue;
	  case 'I': case 'i': str += 3; continue;
	  case 'N': case 'n': str += 2; continue;
	  case 'G': case 'g': str += 1; continue;
	  case '=': case ':':
	    sep = 1;
	    str += 6;
	    break;
	  default:
	    str += 6;
	    if (ISSPACE(*str)) break;
	    continue;
	}
	if (STRNCASECMP(str-6, "coding", 6) == 0) break;
    }
    for (;;) {
	do {
	    if (++str >= send) return;
	} while (ISSPACE(*str));
	if (sep) break;
	if (*str != '=' && *str != ':') return;
	sep = 1;
	str++;
    }
    beg = str;
    while ((*str == '-' || *str == '_' || ISALNUM(*str)) && ++str < send);
    s = rb_str_new(beg, parser_encode_length(parser, beg, str - beg));
    parser_set_encode(parser, RSTRING_PTR(s));
    rb_str_resize(s, 0);
}

static void
parser_prepare(struct parser_params *parser)
{
    int c = nextc();
    switch (c) {
      case '#':
	if (peek('!')) parser->has_shebang = 1;
	break;
      case 0xef:		/* UTF-8 BOM marker */
	if (lex_pend - lex_p >= 2 &&
	    (unsigned char)lex_p[0] == 0xbb &&
	    (unsigned char)lex_p[1] == 0xbf) {
	    parser->enc = rb_utf8_encoding();
	    lex_p += 2;
	    lex_pbeg = lex_p;
	    return;
	}
	break;
      case EOF:
	return;
    }
    pushback(c);
    parser->enc = rb_enc_get(lex_lastline);
}

#define IS_ARG() IS_lex_state(EXPR_ARG_ANY)
#define IS_END() IS_lex_state(EXPR_END_ANY)
#define IS_BEG() IS_lex_state(EXPR_BEG_ANY)
#define IS_SPCARG(c) (IS_ARG() && space_seen && !ISSPACE(c))
#define IS_LABEL_POSSIBLE() ((IS_lex_state(EXPR_BEG | EXPR_ENDFN) && !cmd_state) || IS_ARG())
#define IS_LABEL_SUFFIX(n) (peek_n(':',(n)) && !peek_n(':', (n)+1))
#define IS_AFTER_OPERATOR() IS_lex_state(EXPR_FNAME | EXPR_DOT)

#ifndef RIPPER
#define ambiguous_operator(op, syn) ( \
    rb_warning0("`"op"' after local variable or literal is interpreted as binary operator"), \
    rb_warning0("even though it seems like "syn""))
#else
#define ambiguous_operator(op, syn) dispatch2(operator_ambiguous, ripper_intern(op), rb_str_new_cstr(syn))
#endif
#define warn_balanced(op, syn) ((void) \
    (!IS_lex_state_for(last_state, EXPR_CLASS|EXPR_DOT|EXPR_FNAME|EXPR_ENDFN|EXPR_ENDARG) && \
     space_seen && !ISSPACE(c) && \
     (ambiguous_operator(op, syn), 0)))

static VALUE
parse_rational(struct parser_params *parser, char *str, int len, int seen_point)
{
    VALUE v;
    char *point = &str[seen_point];
    size_t fraclen = len-seen_point-1;
    memmove(point, point+1, fraclen+1);
    v = rb_cstr_to_inum(str, 10, FALSE);
    return rb_rational_new(v, rb_int_positive_pow(10, fraclen));
}

static int
parse_numeric(struct parser_params *parser, int c)
{
    int is_float, seen_point, seen_e, nondigit;
    int suffix;

    is_float = seen_point = seen_e = nondigit = 0;
    lex_state = EXPR_END;
    newtok();
    if (c == '-' || c == '+') {
	tokadd(c);
	c = nextc();
    }
    if (c == '0') {
#define no_digits() do {yyerror("numeric literal without digits"); return 0;} while (0)
	int start = toklen();
	c = nextc();
	if (c == 'x' || c == 'X') {
	    /* hexadecimal */
	    c = nextc();
	    if (c != -1 && ISXDIGIT(c)) {
		do {
		    if (c == '_') {
			if (nondigit) break;
			nondigit = c;
			continue;
		    }
		    if (!ISXDIGIT(c)) break;
		    nondigit = 0;
		    tokadd(c);
		} while ((c = nextc()) != -1);
	    }
	    pushback(c);
	    tokfix();
	    if (toklen() == start) {
		no_digits();
	    }
	    else if (nondigit) goto trailing_uc;
	    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
	    return set_integer_literal(rb_cstr_to_inum(tok(), 16, FALSE), suffix);
	}
	if (c == 'b' || c == 'B') {
	    /* binary */
	    c = nextc();
	    if (c == '0' || c == '1') {
		do {
		    if (c == '_') {
			if (nondigit) break;
			nondigit = c;
			continue;
		    }
		    if (c != '0' && c != '1') break;
		    nondigit = 0;
		    tokadd(c);
		} while ((c = nextc()) != -1);
	    }
	    pushback(c);
	    tokfix();
	    if (toklen() == start) {
		no_digits();
	    }
	    else if (nondigit) goto trailing_uc;
	    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
	    return set_integer_literal(rb_cstr_to_inum(tok(), 2, FALSE), suffix);
	}
	if (c == 'd' || c == 'D') {
	    /* decimal */
	    c = nextc();
	    if (c != -1 && ISDIGIT(c)) {
		do {
		    if (c == '_') {
			if (nondigit) break;
			nondigit = c;
			continue;
		    }
		    if (!ISDIGIT(c)) break;
		    nondigit = 0;
		    tokadd(c);
		} while ((c = nextc()) != -1);
	    }
	    pushback(c);
	    tokfix();
	    if (toklen() == start) {
		no_digits();
	    }
	    else if (nondigit) goto trailing_uc;
	    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
	    return set_integer_literal(rb_cstr_to_inum(tok(), 10, FALSE), suffix);
	}
	if (c == '_') {
	    /* 0_0 */
	    goto octal_number;
	}
	if (c == 'o' || c == 'O') {
	    /* prefixed octal */
	    c = nextc();
	    if (c == -1 || c == '_' || !ISDIGIT(c)) {
		no_digits();
	    }
	}
	if (c >= '0' && c <= '7') {
	    /* octal */
	  octal_number:
	    do {
		if (c == '_') {
		    if (nondigit) break;
		    nondigit = c;
		    continue;
		}
		if (c < '0' || c > '9') break;
		if (c > '7') goto invalid_octal;
		nondigit = 0;
		tokadd(c);
	    } while ((c = nextc()) != -1);
	    if (toklen() > start) {
		pushback(c);
		tokfix();
		if (nondigit) goto trailing_uc;
		suffix = number_literal_suffix(NUM_SUFFIX_ALL);
		return set_integer_literal(rb_cstr_to_inum(tok(), 8, FALSE), suffix);
	    }
	    if (nondigit) {
		pushback(c);
		goto trailing_uc;
	    }
	}
	if (c > '7' && c <= '9') {
	  invalid_octal:
	    yyerror("Invalid octal digit");
	}
	else if (c == '.' || c == 'e' || c == 'E') {
	    tokadd('0');
	}
	else {
	    pushback(c);
	    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
	    return set_integer_literal(INT2FIX(0), suffix);
	}
    }

    for (;;) {
	switch (c) {
	  case '0': case '1': case '2': case '3': case '4':
	  case '5': case '6': case '7': case '8': case '9':
	    nondigit = 0;
	    tokadd(c);
	    break;

	  case '.':
	    if (nondigit) goto trailing_uc;
	    if (seen_point || seen_e) {
		goto decode_num;
	    }
	    else {
		int c0 = nextc();
		if (c0 == -1 || !ISDIGIT(c0)) {
		    pushback(c0);
		    goto decode_num;
		}
		c = c0;
	    }
	    seen_point = toklen();
	    tokadd('.');
	    tokadd(c);
	    is_float++;
	    nondigit = 0;
	    break;

	  case 'e':
	  case 'E':
	    if (nondigit) {
		pushback(c);
		c = nondigit;
		goto decode_num;
	    }
	    if (seen_e) {
		goto decode_num;
	    }
	    nondigit = c;
	    c = nextc();
	    if (c != '-' && c != '+' && !ISDIGIT(c)) {
		pushback(c);
		nondigit = 0;
		goto decode_num;
	    }
	    tokadd(nondigit);
	    seen_e++;
	    is_float++;
	    tokadd(c);
	    nondigit = (c == '-' || c == '+') ? c : 0;
	    break;

	  case '_':	/* `_' in number just ignored */
	    if (nondigit) goto decode_num;
	    nondigit = c;
	    break;

	  default:
	    goto decode_num;
	}
	c = nextc();
    }

  decode_num:
    pushback(c);
    if (nondigit) {
	char tmp[30];
      trailing_uc:
	snprintf(tmp, sizeof(tmp), "trailing `%c' in number", nondigit);
	yyerror(tmp);
    }
    tokfix();
    if (is_float) {
	int type = tFLOAT;
	VALUE v;

	suffix = number_literal_suffix(seen_e ? NUM_SUFFIX_I : NUM_SUFFIX_ALL);
	if (suffix & NUM_SUFFIX_R) {
	    type = tRATIONAL;
	    v = parse_rational(parser, tok(), toklen(), seen_point);
	}
	else {
	    double d = strtod(tok(), 0);
	    if (errno == ERANGE) {
		rb_warningS("Float %s out of range", tok());
		errno = 0;
	    }
	    v = DBL2NUM(d);
	}
	return set_number_literal(v, type, suffix);
    }
    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
    return set_integer_literal(rb_cstr_to_inum(tok(), 10, FALSE), suffix);
}

static int
parse_qmark(struct parser_params *parser)
{
    rb_encoding *enc;
    register int c;

    if (IS_END()) {
	lex_state = EXPR_VALUE;
	return '?';
    }
    c = nextc();
    if (c == -1) {
	compile_error(PARSER_ARG "incomplete character syntax");
	return 0;
    }
    if (rb_enc_isspace(c, current_enc)) {
	if (!IS_ARG()) {
	    int c2 = 0;
	    switch (c) {
	      case ' ':
		c2 = 's';
		break;
	      case '\n':
		c2 = 'n';
		break;
	      case '\t':
		c2 = 't';
		break;
	      case '\v':
		c2 = 'v';
		break;
	      case '\r':
		c2 = 'r';
		break;
	      case '\f':
		c2 = 'f';
		break;
	    }
	    if (c2) {
		rb_warnI("invalid character syntax; use ?\\%c", c2);
	    }
	}
      ternary:
	pushback(c);
	lex_state = EXPR_VALUE;
	return '?';
    }
    newtok();
    enc = current_enc;
    if (!parser_isascii()) {
	if (tokadd_mbchar(c) == -1) return 0;
    }
    else if ((rb_enc_isalnum(c, current_enc) || c == '_') &&
	     lex_p < lex_pend && is_identchar(lex_p, lex_pend, current_enc)) {
	goto ternary;
    }
    else if (c == '\\') {
	if (peek('u')) {
	    nextc();
	    c = parser_tokadd_utf8(parser, &enc, 0, 0, 0);
	    if (0x80 <= c) {
		tokaddmbc(c, enc);
	    }
	    else {
		tokadd(c);
	    }
	}
	else if (!lex_eol_p() && !(c = *lex_p, ISASCII(c))) {
	    nextc();
	    if (tokadd_mbchar(c) == -1) return 0;
	}
	else {
	    c = read_escape(0, &enc);
	    tokadd(c);
	}
    }
    else {
	tokadd(c);
    }
    tokfix();
    set_yylval_str(STR_NEW3(tok(), toklen(), enc, 0));
    lex_state = EXPR_END;
    return tCHAR;
}

static int
parse_percent(struct parser_params *parser, const int space_seen, const enum lex_state_e last_state)
{
    register int c;

    if (IS_lex_state(EXPR_BEG_ANY)) {
	int term;
	int paren;

	c = nextc();
      quotation:
	if (c == -1 || !ISALNUM(c)) {
	    term = c;
	    c = 'Q';
	}
	else {
	    term = nextc();
	    if (rb_enc_isalnum(term, current_enc) || !parser_isascii()) {
		yyerror("unknown type of %string");
		return 0;
	    }
	}
	if (c == -1 || term == -1) {
	    compile_error(PARSER_ARG "unterminated quoted string meets end of file");
	    return 0;
	}
	paren = term;
	if (term == '(') term = ')';
	else if (term == '[') term = ']';
	else if (term == '{') term = '}';
	else if (term == '<') term = '>';
	else paren = 0;

	switch (c) {
	  case 'Q':
	    lex_strterm = NEW_STRTERM(str_dquote, term, paren);
	    return tSTRING_BEG;

	  case 'q':
	    lex_strterm = NEW_STRTERM(str_squote, term, paren);
	    return tSTRING_BEG;

	  case 'W':
	    lex_strterm = NEW_STRTERM(str_dword, term, paren);
	    do {c = nextc();} while (ISSPACE(c));
	    pushback(c);
	    return tWORDS_BEG;

	  case 'w':
	    lex_strterm = NEW_STRTERM(str_sword, term, paren);
	    do {c = nextc();} while (ISSPACE(c));
	    pushback(c);
	    return tQWORDS_BEG;

	  case 'I':
	    lex_strterm = NEW_STRTERM(str_dword, term, paren);
	    do {c = nextc();} while (ISSPACE(c));
	    pushback(c);
	    return tSYMBOLS_BEG;

	  case 'i':
	    lex_strterm = NEW_STRTERM(str_sword, term, paren);
	    do {c = nextc();} while (ISSPACE(c));
	    pushback(c);
	    return tQSYMBOLS_BEG;

	  case 'x':
	    lex_strterm = NEW_STRTERM(str_xquote, term, paren);
	    return tXSTRING_BEG;

	  case 'r':
	    lex_strterm = NEW_STRTERM(str_regexp, term, paren);
	    return tREGEXP_BEG;

	  case 's':
	    lex_strterm = NEW_STRTERM(str_ssym, term, paren);
	    lex_state = EXPR_FNAME;
	    return tSYMBEG;

	  default:
	    yyerror("unknown type of %string");
	    return 0;
	}
    }
    if ((c = nextc()) == '=') {
	set_yylval_id('%');
	lex_state = EXPR_BEG;
	return tOP_ASGN;
    }
    if (IS_SPCARG(c)) {
	goto quotation;
    }
    lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
    pushback(c);
    warn_balanced("%%", "string literal");
    return '%';
}

static int
tokadd_ident(struct parser_params *parser, int c)
{
    do {
	if (tokadd_mbchar(c) == -1) return -1;
	c = nextc();
    } while (parser_is_identchar());
    pushback(c);
    return 0;
}

static void
tokenize_ident(struct parser_params *parser, const enum lex_state_e last_state)
{
    ID ident = TOK_INTERN();

    set_yylval_name(ident);
    if (!IS_lex_state_for(last_state, EXPR_DOT|EXPR_FNAME) &&
	is_local_id(ident) && lvar_defined(ident)) {
	lex_state = EXPR_END;
    }
}

static int
parse_gvar(struct parser_params *parser, const enum lex_state_e last_state)
{
    register int c;

    lex_state = EXPR_END;
    newtok();
    c = nextc();
    switch (c) {
      case '_':		/* $_: last read line string */
	c = nextc();
	if (parser_is_identchar()) {
	    tokadd('$');
	    tokadd('_');
	    break;
	}
	pushback(c);
	c = '_';
	/* fall through */
      case '~':		/* $~: match-data */
      case '*':		/* $*: argv */
      case '$':		/* $$: pid */
      case '?':		/* $?: last status */
      case '!':		/* $!: error string */
      case '@':		/* $@: error position */
      case '/':		/* $/: input record separator */
      case '\\':		/* $\: output record separator */
      case ';':		/* $;: field separator */
      case ',':		/* $,: output field separator */
      case '.':		/* $.: last read line number */
      case '=':		/* $=: ignorecase */
      case ':':		/* $:: load path */
      case '<':		/* $<: reading filename */
      case '>':		/* $>: default output handle */
      case '\"':		/* $": already loaded files */
	tokadd('$');
	tokadd(c);
	goto gvar;

      case '-':
	tokadd('$');
	tokadd(c);
	c = nextc();
	if (parser_is_identchar()) {
	    if (tokadd_mbchar(c) == -1) return 0;
	}
	else {
	    pushback(c);
	    pushback('-');
	    return '$';
	}
      gvar:
	set_yylval_name(intern_cstr(tok(), tokidx, current_enc));
	return tGVAR;

      case '&':		/* $&: last match */
      case '`':		/* $`: string before last match */
      case '\'':		/* $': string after last match */
      case '+':		/* $+: string matches last paren. */
	if (IS_lex_state_for(last_state, EXPR_FNAME)) {
	    tokadd('$');
	    tokadd(c);
	    goto gvar;
	}
	set_yylval_node(NEW_BACK_REF(c));
	return tBACK_REF;

      case '1': case '2': case '3':
      case '4': case '5': case '6':
      case '7': case '8': case '9':
	tokadd('$');
	do {
	    tokadd(c);
	    c = nextc();
	} while (c != -1 && ISDIGIT(c));
	pushback(c);
	if (IS_lex_state_for(last_state, EXPR_FNAME)) goto gvar;
	tokfix();
	set_yylval_node(NEW_NTH_REF(atoi(tok()+1)));
	return tNTH_REF;

      default:
	if (!parser_is_identchar()) {
	    pushback(c);
	    compile_error(PARSER_ARG "`$%c' is not allowed as a global variable name", c);
	    return 0;
	}
      case '0':
	tokadd('$');
    }

    if (tokadd_ident(parser, c)) return 0;
    lex_state = EXPR_END;
    tokenize_ident(parser, last_state);
    return tGVAR;
}

static int
parse_atmark(struct parser_params *parser, const enum lex_state_e last_state)
{
    int result = tIVAR;
    register int c = nextc();

    newtok();
    tokadd('@');
    if (c == '@') {
	result = tCVAR;
	tokadd('@');
	c = nextc();
    }
    if (c != -1 && (ISDIGIT(c) || !parser_is_identchar())) {
	pushback(c);
	if (tokidx == 1) {
	    compile_error(PARSER_ARG "`@%c' is not allowed as an instance variable name", c);
	}
	else {
	    compile_error(PARSER_ARG "`@@%c' is not allowed as a class variable name", c);
	}
	return 0;
    }

    if (tokadd_ident(parser, c)) return 0;
    lex_state = EXPR_END;
    tokenize_ident(parser, last_state);
    return result;
}

static int
parse_ident(struct parser_params *parser, int c, int cmd_state)
{
    int result = 0;
    int mb = ENC_CODERANGE_7BIT;
    const enum lex_state_e last_state = lex_state;

    do {
	if (!ISASCII(c)) mb = ENC_CODERANGE_UNKNOWN;
	if (tokadd_mbchar(c) == -1) return 0;
	c = nextc();
    } while (parser_is_identchar());
    if ((c == '!' || c == '?') && !peek('=')) {
	tokadd(c);
    }
    else {
	pushback(c);
    }
    tokfix();

    if (toklast() == '!' || toklast() == '?') {
	result = tFID;
    }
    else {
	if (IS_lex_state(EXPR_FNAME)) {
	    register int c = nextc();
	    if (c == '=' && !peek('~') && !peek('>') &&
		(!peek('=') || (peek_n('>', 1)))) {
		result = tIDENTIFIER;
		tokadd(c);
		tokfix();
	    }
	    else {
		pushback(c);
	    }
	}
	if (result == 0 && ISUPPER(tok()[0])) {
	    result = tCONSTANT;
	}
	else {
	    result = tIDENTIFIER;
	}
    }

    if (IS_LABEL_POSSIBLE()) {
	if (IS_LABEL_SUFFIX(0)) {
	    lex_state = EXPR_LABELARG;
	    nextc();
	    set_yylval_name(TOK_INTERN());
	    return tLABEL;
	}
    }
    if (mb == ENC_CODERANGE_7BIT && !IS_lex_state(EXPR_DOT)) {
	const struct kwtable *kw;

	/* See if it is a reserved word.  */
	kw = rb_reserved_word(tok(), toklen());
	if (kw) {
	    enum lex_state_e state = lex_state;
	    lex_state = kw->state;
	    if (IS_lex_state_for(state, EXPR_FNAME)) {
		set_yylval_name(rb_intern(kw->name));
		return kw->id[0];
	    }
	    if (IS_lex_state(EXPR_BEG)) {
		command_start = TRUE;
	    }
	    if (kw->id[0] == keyword_do) {
		if (lpar_beg && lpar_beg == paren_nest) {
		    lpar_beg = 0;
		    --paren_nest;
		    return keyword_do_LAMBDA;
		}
		if (COND_P()) return keyword_do_cond;
		if (CMDARG_P() && !IS_lex_state_for(state, EXPR_CMDARG))
		    return keyword_do_block;
		if (IS_lex_state_for(state, (EXPR_BEG | EXPR_ENDARG)))
		    return keyword_do_block;
		return keyword_do;
	    }
	    if (IS_lex_state_for(state, (EXPR_BEG | EXPR_VALUE)))
		return kw->id[0];
	    else {
		if (kw->id[0] != kw->id[1])
		    lex_state = EXPR_BEG;
		return kw->id[1];
	    }
	}
    }

    if (IS_lex_state(EXPR_BEG_ANY | EXPR_ARG_ANY | EXPR_DOT)) {
	if (cmd_state) {
	    lex_state = EXPR_CMDARG;
	}
	else {
	    lex_state = EXPR_ARG;
	}
    }
    else if (lex_state == EXPR_FNAME) {
	lex_state = EXPR_ENDFN;
    }
    else {
	lex_state = EXPR_END;
    }

    tokenize_ident(parser, last_state);
    return result;
}

static int
parser_yylex(struct parser_params *parser)
{
    register int c;
    int space_seen = 0;
    int cmd_state;
    enum lex_state_e last_state;
#ifdef RIPPER
    int fallthru = FALSE;
#endif

    if (lex_strterm) {
	int token;
	if (nd_type(lex_strterm) == NODE_HEREDOC) {
	    token = here_document(lex_strterm);
	    if (token == tSTRING_END) {
		lex_strterm = 0;
		lex_state = EXPR_END;
	    }
	}
	else {
	    token = parse_string(lex_strterm);
	    if (token == tSTRING_END || token == tREGEXP_END) {
		rb_gc_force_recycle((VALUE)lex_strterm);
		lex_strterm = 0;
		lex_state = EXPR_END;
	    }
	}
	return token;
    }
    cmd_state = command_start;
    command_start = FALSE;
  retry:
    last_state = lex_state;
    switch (c = nextc()) {
      case '\0':		/* NUL */
      case '\004':		/* ^D */
      case '\032':		/* ^Z */
      case -1:			/* end of script. */
	return 0;

	/* white spaces */
      case ' ': case '\t': case '\f': case '\r':
      case '\13': /* '\v' */
	space_seen = 1;
#ifdef RIPPER
	while ((c = nextc())) {
	    switch (c) {
	      case ' ': case '\t': case '\f': case '\r':
	      case '\13': /* '\v' */
		break;
	      default:
		goto outofloop;
	    }
	}
      outofloop:
	pushback(c);
	ripper_dispatch_scan_event(parser, tSP);
#endif
	goto retry;

      case '#':		/* it's a comment */
	/* no magic_comment in shebang line */
	if (!parser_magic_comment(parser, lex_p, lex_pend - lex_p)) {
	    if (comment_at_top(parser)) {
		set_file_encoding(parser, lex_p, lex_pend);
	    }
	}
	lex_p = lex_pend;
#ifdef RIPPER
        ripper_dispatch_scan_event(parser, tCOMMENT);
        fallthru = TRUE;
#endif
	/* fall through */
      case '\n':
	if (IS_lex_state(EXPR_BEG | EXPR_VALUE | EXPR_CLASS | EXPR_FNAME | EXPR_DOT | EXPR_LABELARG)) {
#ifdef RIPPER
            if (!fallthru) {
                ripper_dispatch_scan_event(parser, tIGNORED_NL);
            }
            fallthru = FALSE;
#endif
	    if (IS_lex_state(EXPR_LABELARG) && parser->parser_in_kwarg) {
		goto normal_newline;
	    }
	    goto retry;
	}
	while ((c = nextc())) {
	    switch (c) {
	      case ' ': case '\t': case '\f': case '\r':
	      case '\13': /* '\v' */
		space_seen = 1;
		break;
	      case '.': {
		  if ((c = nextc()) != '.') {
		      pushback(c);
		      pushback('.');
		      goto retry;
		  }
	      }
	      default:
		--ruby_sourceline;
		lex_nextline = lex_lastline;
	      case -1:		/* EOF no decrement*/
		lex_goto_eol(parser);
#ifdef RIPPER
		if (c != -1) {
		    parser->tokp = lex_p;
		}
#endif
		goto normal_newline;
	    }
	}
      normal_newline:
	command_start = TRUE;
	lex_state = EXPR_BEG;
	return '\n';

      case '*':
	if ((c = nextc()) == '*') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tPOW);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    if (IS_SPCARG(c)) {
		rb_warning0("`**' interpreted as argument prefix");
		c = tDSTAR;
	    }
	    else if (IS_BEG()) {
		c = tDSTAR;
	    }
	    else {
		warn_balanced("**", "argument prefix");
		c = tPOW;
	    }
	}
	else {
	    if (c == '=') {
                set_yylval_id('*');
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    if (IS_SPCARG(c)) {
		rb_warning0("`*' interpreted as argument prefix");
		c = tSTAR;
	    }
	    else if (IS_BEG()) {
		c = tSTAR;
	    }
	    else {
		warn_balanced("*", "argument prefix");
		c = '*';
	    }
	}
	lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
	return c;

      case '!':
	c = nextc();
	if (IS_AFTER_OPERATOR()) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return '!';
	    }
	}
	else {
	    lex_state = EXPR_BEG;
	}
	if (c == '=') {
	    return tNEQ;
	}
	if (c == '~') {
	    return tNMATCH;
	}
	pushback(c);
	return '!';

      case '=':
	if (was_bol()) {
	    /* skip embedded rd document */
	    if (strncmp(lex_p, "begin", 5) == 0 && ISSPACE(lex_p[5])) {
#ifdef RIPPER
                int first_p = TRUE;

                lex_goto_eol(parser);
                ripper_dispatch_scan_event(parser, tEMBDOC_BEG);
#endif
		for (;;) {
		    lex_goto_eol(parser);
#ifdef RIPPER
                    if (!first_p) {
                        ripper_dispatch_scan_event(parser, tEMBDOC);
                    }
                    first_p = FALSE;
#endif
		    c = nextc();
		    if (c == -1) {
			compile_error(PARSER_ARG "embedded document meets end of file");
			return 0;
		    }
		    if (c != '=') continue;
		    if (strncmp(lex_p, "end", 3) == 0 &&
			(lex_p + 3 == lex_pend || ISSPACE(lex_p[3]))) {
			break;
		    }
		}
		lex_goto_eol(parser);
#ifdef RIPPER
                ripper_dispatch_scan_event(parser, tEMBDOC_END);
#endif
		goto retry;
	    }
	}

	lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
	if ((c = nextc()) == '=') {
	    if ((c = nextc()) == '=') {
		return tEQQ;
	    }
	    pushback(c);
	    return tEQ;
	}
	if (c == '~') {
	    return tMATCH;
	}
	else if (c == '>') {
	    return tASSOC;
	}
	pushback(c);
	return '=';

      case '<':
	last_state = lex_state;
	c = nextc();
	if (c == '<' &&
	    !IS_lex_state(EXPR_DOT | EXPR_CLASS) &&
	    !IS_END() &&
	    (!IS_ARG() || space_seen)) {
	    int token = heredoc_identifier();
	    if (token) return token;
	}
	if (IS_AFTER_OPERATOR()) {
	    lex_state = EXPR_ARG;
	}
	else {
	    if (IS_lex_state(EXPR_CLASS))
		command_start = TRUE;
	    lex_state = EXPR_BEG;
	}
	if (c == '=') {
	    if ((c = nextc()) == '>') {
		return tCMP;
	    }
	    pushback(c);
	    return tLEQ;
	}
	if (c == '<') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tLSHFT);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    warn_balanced("<<", "here document");
	    return tLSHFT;
	}
	pushback(c);
	return '<';

      case '>':
	lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
	if ((c = nextc()) == '=') {
	    return tGEQ;
	}
	if (c == '>') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tRSHFT);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tRSHFT;
	}
	pushback(c);
	return '>';

      case '"':
	lex_strterm = NEW_STRTERM(str_dquote, '"', 0);
	return tSTRING_BEG;

      case '`':
	if (IS_lex_state(EXPR_FNAME)) {
	    lex_state = EXPR_ENDFN;
	    return c;
	}
	if (IS_lex_state(EXPR_DOT)) {
	    if (cmd_state)
		lex_state = EXPR_CMDARG;
	    else
		lex_state = EXPR_ARG;
	    return c;
	}
	lex_strterm = NEW_STRTERM(str_xquote, '`', 0);
	return tXSTRING_BEG;

      case '\'':
	lex_strterm = NEW_STRTERM(str_squote, '\'', 0);
	return tSTRING_BEG;

      case '?':
	return parse_qmark(parser);

      case '&':
	if ((c = nextc()) == '&') {
	    lex_state = EXPR_BEG;
	    if ((c = nextc()) == '=') {
                set_yylval_id(tANDOP);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tANDOP;
	}
	else if (c == '=') {
            set_yylval_id('&');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_SPCARG(c)) {
	    rb_warning0("`&' interpreted as argument prefix");
	    c = tAMPER;
	}
	else if (IS_BEG()) {
	    c = tAMPER;
	}
	else {
	    warn_balanced("&", "argument prefix");
	    c = '&';
	}
	lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
	return c;

      case '|':
	if ((c = nextc()) == '|') {
	    lex_state = EXPR_BEG;
	    if ((c = nextc()) == '=') {
                set_yylval_id(tOROP);
		lex_state = EXPR_BEG;
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tOROP;
	}
	if (c == '=') {
            set_yylval_id('|');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
	pushback(c);
	return '|';

      case '+':
	c = nextc();
	if (IS_AFTER_OPERATOR()) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return tUPLUS;
	    }
	    pushback(c);
	    return '+';
	}
	if (c == '=') {
            set_yylval_id('+');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous('+'))) {
	    lex_state = EXPR_BEG;
	    pushback(c);
	    if (c != -1 && ISDIGIT(c)) {
		return parse_numeric(parser, '+');
	    }
	    return tUPLUS;
	}
	lex_state = EXPR_BEG;
	pushback(c);
	warn_balanced("+", "unary operator");
	return '+';

      case '-':
	c = nextc();
	if (IS_AFTER_OPERATOR()) {
	    lex_state = EXPR_ARG;
	    if (c == '@') {
		return tUMINUS;
	    }
	    pushback(c);
	    return '-';
	}
	if (c == '=') {
            set_yylval_id('-');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	if (c == '>') {
	    lex_state = EXPR_ENDFN;
	    return tLAMBDA;
	}
	if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous('-'))) {
	    lex_state = EXPR_BEG;
	    pushback(c);
	    if (c != -1 && ISDIGIT(c)) {
		return tUMINUS_NUM;
	    }
	    return tUMINUS;
	}
	lex_state = EXPR_BEG;
	pushback(c);
	warn_balanced("-", "unary operator");
	return '-';

      case '.':
	lex_state = EXPR_BEG;
	if ((c = nextc()) == '.') {
	    if ((c = nextc()) == '.') {
		return tDOT3;
	    }
	    pushback(c);
	    return tDOT2;
	}
	pushback(c);
	if (c != -1 && ISDIGIT(c)) {
	    yyerror("no .<digit> floating literal anymore; put 0 before dot");
	}
	lex_state = EXPR_DOT;
	return '.';

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
	return parse_numeric(parser, c);

      case ')':
      case ']':
	paren_nest--;
      case '}':
	COND_LEXPOP();
	CMDARG_LEXPOP();
	if (c == ')')
	    lex_state = EXPR_ENDFN;
	else
	    lex_state = EXPR_ENDARG;
	if (c == '}') {
	    if (!brace_nest--) c = tSTRING_DEND;
	}
	return c;

      case ':':
	c = nextc();
	if (c == ':') {
	    if (IS_BEG() || IS_lex_state(EXPR_CLASS) || IS_SPCARG(-1)) {
		lex_state = EXPR_BEG;
		return tCOLON3;
	    }
	    lex_state = EXPR_DOT;
	    return tCOLON2;
	}
	if (IS_END() || ISSPACE(c)) {
	    pushback(c);
	    warn_balanced(":", "symbol literal");
	    lex_state = EXPR_BEG;
	    return ':';
	}
	switch (c) {
	  case '\'':
	    lex_strterm = NEW_STRTERM(str_ssym, c, 0);
	    break;
	  case '"':
	    lex_strterm = NEW_STRTERM(str_dsym, c, 0);
	    break;
	  default:
	    pushback(c);
	    break;
	}
	lex_state = EXPR_FNAME;
	return tSYMBEG;

      case '/':
	if (IS_lex_state(EXPR_BEG_ANY)) {
	    lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
	    return tREGEXP_BEG;
	}
	if ((c = nextc()) == '=') {
            set_yylval_id('/');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_SPCARG(c)) {
	    (void)arg_ambiguous('/');
	    lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
	    return tREGEXP_BEG;
	}
	lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
	warn_balanced("/", "regexp literal");
	return '/';

      case '^':
	if ((c = nextc()) == '=') {
            set_yylval_id('^');
	    lex_state = EXPR_BEG;
	    return tOP_ASGN;
	}
	lex_state = IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG;
	pushback(c);
	return '^';

      case ';':
	lex_state = EXPR_BEG;
	command_start = TRUE;
	return ';';

      case ',':
	lex_state = EXPR_BEG;
	return ',';

      case '~':
	if (IS_AFTER_OPERATOR()) {
	    if ((c = nextc()) != '@') {
		pushback(c);
	    }
	    lex_state = EXPR_ARG;
	}
	else {
	    lex_state = EXPR_BEG;
	}
	return '~';

      case '(':
	if (IS_BEG()) {
	    c = tLPAREN;
	}
	else if (IS_SPCARG(-1)) {
	    c = tLPAREN_ARG;
	}
	paren_nest++;
	COND_PUSH(0);
	CMDARG_PUSH(0);
	lex_state = EXPR_BEG;
	return c;

      case '[':
	paren_nest++;
	if (IS_AFTER_OPERATOR()) {
	    lex_state = EXPR_ARG;
	    if ((c = nextc()) == ']') {
		if ((c = nextc()) == '=') {
		    return tASET;
		}
		pushback(c);
		return tAREF;
	    }
	    pushback(c);
	    return '[';
	}
	else if (IS_BEG()) {
	    c = tLBRACK;
	}
	else if (IS_ARG() && space_seen) {
	    c = tLBRACK;
	}
	lex_state = EXPR_BEG;
	COND_PUSH(0);
	CMDARG_PUSH(0);
	return c;

      case '{':
	++brace_nest;
	if (lpar_beg && lpar_beg == paren_nest) {
	    lex_state = EXPR_BEG;
	    lpar_beg = 0;
	    --paren_nest;
	    COND_PUSH(0);
	    CMDARG_PUSH(0);
	    return tLAMBEG;
	}
	if (IS_ARG() || IS_lex_state(EXPR_END | EXPR_ENDFN))
	    c = '{';          /* block (primary) */
	else if (IS_lex_state(EXPR_ENDARG))
	    c = tLBRACE_ARG;  /* block (expr) */
	else
	    c = tLBRACE;      /* hash */
	COND_PUSH(0);
	CMDARG_PUSH(0);
	lex_state = EXPR_BEG;
	if (c != tLBRACE) command_start = TRUE;
	return c;

      case '\\':
	c = nextc();
	if (c == '\n') {
	    space_seen = 1;
#ifdef RIPPER
	    ripper_dispatch_scan_event(parser, tSP);
#endif
	    goto retry; /* skip \\n */
	}
	pushback(c);
	return '\\';

      case '%':
	return parse_percent(parser, space_seen, last_state);

      case '$':
	return parse_gvar(parser, last_state);

      case '@':
	return parse_atmark(parser, last_state);

      case '_':
	if (was_bol() && whole_match_p("__END__", 7, 0)) {
	    ruby__end__seen = 1;
	    parser->eofp = Qtrue;
#ifndef RIPPER
	    return -1;
#else
            lex_goto_eol(parser);
            ripper_dispatch_scan_event(parser, k__END__);
            return 0;
#endif
	}
	newtok();
	break;

      default:
	if (!parser_is_identchar()) {
	    compile_error(PARSER_ARG  "Invalid char `\\x%02X' in expression", c);
	    goto retry;
	}

	newtok();
	break;
    }

    return parse_ident(parser, c, cmd_state);
}

#if YYPURE
static int
yylex(void *lval, void *p)
#else
yylex(void *p)
#endif
{
    struct parser_params *parser = (struct parser_params*)p;
    int t;

#if YYPURE
    parser->parser_yylval = lval;
    parser->parser_yylval->val = Qundef;
#endif
    t = parser_yylex(parser);
#ifdef RIPPER
    if (!NIL_P(parser->delayed)) {
	ripper_dispatch_delayed_token(parser, t);
	return t;
    }
    if (t != 0)
	ripper_dispatch_scan_event(parser, t);
#endif

    return t;
}

#ifndef RIPPER
static NODE*
node_newnode(struct parser_params *parser, enum node_type type, VALUE a0, VALUE a1, VALUE a2)
{
    NODE *n = (rb_node_newnode)(type, a0, a1, a2);
    nd_set_line(n, ruby_sourceline);
    return n;
}

static enum node_type
nodetype(NODE *node)			/* for debug */
{
    return (enum node_type)nd_type(node);
}

static int
nodeline(NODE *node)
{
    return nd_line(node);
}

static NODE*
newline_node(NODE *node)
{
    if (node) {
	node = remove_begin(node);
	node->flags |= NODE_FL_NEWLINE;
    }
    return node;
}

static void
fixpos(NODE *node, NODE *orig)
{
    if (!node) return;
    if (!orig) return;
    if (orig == (NODE*)1) return;
    nd_set_line(node, nd_line(orig));
}

static void
parser_warning(struct parser_params *parser, NODE *node, const char *mesg)
{
    rb_compile_warning(ruby_sourcefile, nd_line(node), "%s", mesg);
}
#define parser_warning(node, mesg) parser_warning(parser, (node), (mesg))

static void
parser_warn(struct parser_params *parser, NODE *node, const char *mesg)
{
    rb_compile_warn(ruby_sourcefile, nd_line(node), "%s", mesg);
}
#define parser_warn(node, mesg) parser_warn(parser, (node), (mesg))

static NODE*
block_append_gen(struct parser_params *parser, NODE *head, NODE *tail)
{
    NODE *end, *h = head, *nd;

    if (tail == 0) return head;

    if (h == 0) return tail;
    switch (nd_type(h)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_SELF:
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_NIL:
	parser_warning(h, "unused literal ignored");
	return tail;
      default:
	h = end = NEW_BLOCK(head);
	end->nd_end = end;
	fixpos(end, head);
	head = end;
	break;
      case NODE_BLOCK:
	end = h->nd_end;
	break;
    }

    nd = end->nd_head;
    switch (nd_type(nd)) {
      case NODE_RETURN:
      case NODE_BREAK:
      case NODE_NEXT:
      case NODE_REDO:
      case NODE_RETRY:
	if (RTEST(ruby_verbose)) {
	    parser_warning(tail, "statement not reached");
	}
	break;

      default:
	break;
    }

    if (nd_type(tail) != NODE_BLOCK) {
	tail = NEW_BLOCK(tail);
	tail->nd_end = tail;
    }
    end->nd_next = tail;
    h->nd_end = tail->nd_end;
    return head;
}

/* append item to the list */
static NODE*
list_append_gen(struct parser_params *parser, NODE *list, NODE *item)
{
    NODE *last;

    if (list == 0) return NEW_LIST(item);
    if (list->nd_next) {
	last = list->nd_next->nd_end;
    }
    else {
	last = list;
    }

    list->nd_alen += 1;
    last->nd_next = NEW_LIST(item);
    list->nd_next->nd_end = last->nd_next;
    return list;
}

/* concat two lists */
static NODE*
list_concat_gen(struct parser_params *parser, NODE *head, NODE *tail)
{
    NODE *last;

    if (head->nd_next) {
	last = head->nd_next->nd_end;
    }
    else {
	last = head;
    }

    head->nd_alen += tail->nd_alen;
    last->nd_next = tail;
    if (tail->nd_next) {
	head->nd_next->nd_end = tail->nd_next->nd_end;
    }
    else {
	head->nd_next->nd_end = tail;
    }

    return head;
}

static int
literal_concat0(struct parser_params *parser, VALUE head, VALUE tail)
{
    if (NIL_P(tail)) return 1;
    if (!rb_enc_compatible(head, tail)) {
	compile_error(PARSER_ARG "string literal encodings differ (%s / %s)",
		      rb_enc_name(rb_enc_get(head)),
		      rb_enc_name(rb_enc_get(tail)));
	rb_str_resize(head, 0);
	rb_str_resize(tail, 0);
	return 0;
    }
    rb_str_buf_append(head, tail);
    return 1;
}

/* concat two string literals */
static NODE *
literal_concat_gen(struct parser_params *parser, NODE *head, NODE *tail)
{
    enum node_type htype;
    NODE *headlast;
    VALUE lit;

    if (!head) return tail;
    if (!tail) return head;

    htype = nd_type(head);
    if (htype == NODE_EVSTR) {
	NODE *node = NEW_DSTR(Qnil);
	head = list_append(node, head);
	htype = NODE_DSTR;
    }
    switch (nd_type(tail)) {
      case NODE_STR:
	if (htype == NODE_DSTR && (headlast = head->nd_next->nd_end->nd_head) &&
	    nd_type(headlast) == NODE_STR) {
	    htype = NODE_STR;
	    lit = headlast->nd_lit;
	}
	else {
	    lit = head->nd_lit;
	}
	if (htype == NODE_STR) {
	    if (!literal_concat0(parser, lit, tail->nd_lit)) {
	      error:
		rb_gc_force_recycle((VALUE)head);
		rb_gc_force_recycle((VALUE)tail);
		return 0;
	    }
	    rb_gc_force_recycle((VALUE)tail);
	}
	else {
	    list_append(head, tail);
	}
	break;

      case NODE_DSTR:
	if (htype == NODE_STR) {
	    if (!literal_concat0(parser, head->nd_lit, tail->nd_lit))
		goto error;
	    tail->nd_lit = head->nd_lit;
	    rb_gc_force_recycle((VALUE)head);
	    head = tail;
	}
	else if (NIL_P(tail->nd_lit)) {
	  append:
	    head->nd_alen += tail->nd_alen - 1;
	    head->nd_next->nd_end->nd_next = tail->nd_next;
	    head->nd_next->nd_end = tail->nd_next->nd_end;
	    rb_gc_force_recycle((VALUE)tail);
	}
	else if (htype == NODE_DSTR && (headlast = head->nd_next->nd_end->nd_head) &&
		 nd_type(headlast) == NODE_STR) {
	    lit = headlast->nd_lit;
	    if (!literal_concat0(parser, lit, tail->nd_lit))
		goto error;
	    tail->nd_lit = Qnil;
	    goto append;
	}
	else {
	    nd_set_type(tail, NODE_ARRAY);
	    tail->nd_head = NEW_STR(tail->nd_lit);
	    list_concat(head, tail);
	}
	break;

      case NODE_EVSTR:
	if (htype == NODE_STR) {
	    nd_set_type(head, NODE_DSTR);
	    head->nd_alen = 1;
	}
	list_append(head, tail);
	break;
    }
    return head;
}

static NODE *
evstr2dstr_gen(struct parser_params *parser, NODE *node)
{
    if (nd_type(node) == NODE_EVSTR) {
	node = list_append(NEW_DSTR(Qnil), node);
    }
    return node;
}

static NODE *
new_evstr_gen(struct parser_params *parser, NODE *node)
{
    NODE *head = node;

    if (node) {
	switch (nd_type(node)) {
	  case NODE_STR: case NODE_DSTR: case NODE_EVSTR:
	    return node;
	}
    }
    return NEW_EVSTR(head);
}

static NODE *
call_bin_op_gen(struct parser_params *parser, NODE *recv, ID id, NODE *arg1)
{
    value_expr(recv);
    value_expr(arg1);
    return NEW_CALL(recv, id, NEW_LIST(arg1));
}

static NODE *
call_uni_op_gen(struct parser_params *parser, NODE *recv, ID id)
{
    value_expr(recv);
    return NEW_CALL(recv, id, 0);
}

static NODE*
match_op_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    value_expr(node1);
    value_expr(node2);
    if (node1) {
	switch (nd_type(node1)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH2(node1, node2);

	  case NODE_LIT:
	    if (RB_TYPE_P(node1->nd_lit, T_REGEXP)) {
		return NEW_MATCH2(node1, node2);
	    }
	}
    }

    if (node2) {
	switch (nd_type(node2)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH3(node2, node1);

	  case NODE_LIT:
	    if (RB_TYPE_P(node2->nd_lit, T_REGEXP)) {
		return NEW_MATCH3(node2, node1);
	    }
	}
    }

    return NEW_CALL(node1, tMATCH, NEW_LIST(node2));
}

static NODE*
gettable_gen(struct parser_params *parser, ID id)
{
    switch (id) {
      case keyword_self:
	return NEW_SELF();
      case keyword_nil:
	return NEW_NIL();
      case keyword_true:
	return NEW_TRUE();
      case keyword_false:
	return NEW_FALSE();
      case keyword__FILE__:
	return NEW_STR(rb_str_dup(ruby_sourcefile_string));
      case keyword__LINE__:
	return NEW_LIT(INT2FIX(tokline));
      case keyword__ENCODING__:
	return NEW_LIT(rb_enc_from_encoding(current_enc));
    }
    switch (id_type(id)) {
      case ID_LOCAL:
	if (dyna_in_block() && dvar_defined(id)) return NEW_DVAR(id);
	if (local_id(id)) return NEW_LVAR(id);
	/* method call without arguments */
	return NEW_VCALL(id);
      case ID_GLOBAL:
	return NEW_GVAR(id);
      case ID_INSTANCE:
	return NEW_IVAR(id);
      case ID_CONST:
	return NEW_CONST(id);
      case ID_CLASS:
	return NEW_CVAR(id);
    }
    compile_error(PARSER_ARG "identifier %"PRIsVALUE" is not valid to get", rb_id2str(id));
    return 0;
}
#else  /* !RIPPER */
static int
id_is_var_gen(struct parser_params *parser, ID id)
{
    if (is_notop_id(id)) {
	switch (id & ID_SCOPE_MASK) {
	  case ID_GLOBAL: case ID_INSTANCE: case ID_CONST: case ID_CLASS:
	    return 1;
	  case ID_LOCAL:
	    if (dyna_in_block() && dvar_defined(id)) return 1;
	    if (local_id(id)) return 1;
	    /* method call without arguments */
	    return 0;
	}
    }
    compile_error(PARSER_ARG "identifier %s is not valid to get", rb_id2str(id));
    return 0;
}
#endif /* !RIPPER */

#if PARSER_DEBUG
static const char *
lex_state_name(enum lex_state_e state)
{
    static const char names[][12] = {
	"EXPR_BEG",    "EXPR_END",    "EXPR_ENDARG", "EXPR_ENDFN",  "EXPR_ARG",
	"EXPR_CMDARG", "EXPR_MID",    "EXPR_FNAME",  "EXPR_DOT",    "EXPR_CLASS",
	"EXPR_VALUE",
    };

    if ((unsigned)state & ~(~0u << EXPR_MAX_STATE))
	return names[ffs(state)];
    return NULL;
}
#endif

#ifdef RIPPER
static VALUE
assignable_gen(struct parser_params *parser, VALUE lhs)
#else
static NODE*
assignable_gen(struct parser_params *parser, ID id, NODE *val)
#endif
{
#ifdef RIPPER
    ID id = get_id(lhs);
# define assignable_result(x) get_value(lhs)
# define parser_yyerror(parser, x) dispatch1(assign_error, lhs)
#else
# define assignable_result(x) (x)
#endif
    if (!id) return assignable_result(0);
    switch (id) {
      case keyword_self:
	yyerror("Can't change the value of self");
	goto error;
      case keyword_nil:
	yyerror("Can't assign to nil");
	goto error;
      case keyword_true:
	yyerror("Can't assign to true");
	goto error;
      case keyword_false:
	yyerror("Can't assign to false");
	goto error;
      case keyword__FILE__:
	yyerror("Can't assign to __FILE__");
	goto error;
      case keyword__LINE__:
	yyerror("Can't assign to __LINE__");
	goto error;
      case keyword__ENCODING__:
	yyerror("Can't assign to __ENCODING__");
	goto error;
    }
    switch (id_type(id)) {
      case ID_LOCAL:
	if (dyna_in_block()) {
	    if (dvar_curr(id)) {
		return assignable_result(NEW_DASGN_CURR(id, val));
	    }
	    else if (dvar_defined(id)) {
		return assignable_result(NEW_DASGN(id, val));
	    }
	    else if (local_id(id)) {
		return assignable_result(NEW_LASGN(id, val));
	    }
	    else {
		dyna_var(id);
		return assignable_result(NEW_DASGN_CURR(id, val));
	    }
	}
	else {
	    if (!local_id(id)) {
		local_var(id);
	    }
	    return assignable_result(NEW_LASGN(id, val));
	}
	break;
      case ID_GLOBAL:
	return assignable_result(NEW_GASGN(id, val));
      case ID_INSTANCE:
	return assignable_result(NEW_IASGN(id, val));
      case ID_CONST:
	if (!in_def && !in_single)
	    return assignable_result(NEW_CDECL(id, val, 0));
	yyerror("dynamic constant assignment");
	break;
      case ID_CLASS:
	return assignable_result(NEW_CVASGN(id, val));
      default:
	compile_error(PARSER_ARG "identifier %"PRIsVALUE" is not valid to set", rb_id2str(id));
    }
  error:
    return assignable_result(0);
#undef assignable_result
#undef parser_yyerror
}

static int
is_private_local_id(ID name)
{
    VALUE s;
    if (name == idUScore) return 1;
    if (!is_local_id(name)) return 0;
    s = rb_id2str(name);
    if (!s) return 0;
    return RSTRING_PTR(s)[0] == '_';
}

#define LVAR_USED ((ID)1 << (sizeof(ID) * CHAR_BIT - 1))

static int
shadowing_lvar_0(struct parser_params *parser, ID name)
{
    if (is_private_local_id(name)) return 1;
    if (dyna_in_block()) {
	if (dvar_curr(name)) {
	    yyerror("duplicated argument name");
	}
	else if (dvar_defined_get(name) || local_id(name)) {
	    rb_warningV("shadowing outer local variable - %"PRIsVALUE, rb_id2str(name));
	    vtable_add(lvtbl->vars, name);
	    if (lvtbl->used) {
		vtable_add(lvtbl->used, (ID)ruby_sourceline | LVAR_USED);
	    }
	    return 0;
	}
    }
    else {
	if (local_id(name)) {
	    yyerror("duplicated argument name");
	}
    }
    return 1;
}

static ID
shadowing_lvar_gen(struct parser_params *parser, ID name)
{
    shadowing_lvar_0(parser, name);
    return name;
}

static void
new_bv_gen(struct parser_params *parser, ID name)
{
    if (!name) return;
    if (!is_local_id(name)) {
	compile_error(PARSER_ARG "invalid local variable - %"PRIsVALUE,
		      rb_id2str(name));
	return;
    }
    if (!shadowing_lvar_0(parser, name)) return;
    dyna_var(name);
}

#ifndef RIPPER
static NODE *
aryset_gen(struct parser_params *parser, NODE *recv, NODE *idx)
{
    return NEW_ATTRASGN(recv, tASET, idx);
}

static void
block_dup_check_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (node2 && node1 && nd_type(node1) == NODE_BLOCK_PASS) {
	compile_error(PARSER_ARG "both block arg and actual block given");
    }
}

static NODE *
attrset_gen(struct parser_params *parser, NODE *recv, ID id)
{
    return NEW_ATTRASGN(recv, rb_id_attrset(id), 0);
}

static void
rb_backref_error_gen(struct parser_params *parser, NODE *node)
{
    switch (nd_type(node)) {
      case NODE_NTH_REF:
	compile_error(PARSER_ARG "Can't set variable $%ld", node->nd_nth);
	break;
      case NODE_BACK_REF:
	compile_error(PARSER_ARG "Can't set variable $%c", (int)node->nd_nth);
	break;
    }
}

static NODE *
arg_concat_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (!node2) return node1;
    switch (nd_type(node1)) {
      case NODE_BLOCK_PASS:
	if (node1->nd_head)
	    node1->nd_head = arg_concat(node1->nd_head, node2);
	else
	    node1->nd_head = NEW_LIST(node2);
	return node1;
      case NODE_ARGSPUSH:
	if (nd_type(node2) != NODE_ARRAY) break;
	node1->nd_body = list_concat(NEW_LIST(node1->nd_body), node2);
	nd_set_type(node1, NODE_ARGSCAT);
	return node1;
      case NODE_ARGSCAT:
	if (nd_type(node2) != NODE_ARRAY ||
	    nd_type(node1->nd_body) != NODE_ARRAY) break;
	node1->nd_body = list_concat(node1->nd_body, node2);
	return node1;
    }
    return NEW_ARGSCAT(node1, node2);
}

static NODE *
arg_append_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (!node1) return NEW_LIST(node2);
    switch (nd_type(node1))  {
      case NODE_ARRAY:
	return list_append(node1, node2);
      case NODE_BLOCK_PASS:
	node1->nd_head = arg_append(node1->nd_head, node2);
	return node1;
      case NODE_ARGSPUSH:
	node1->nd_body = list_append(NEW_LIST(node1->nd_body), node2);
	nd_set_type(node1, NODE_ARGSCAT);
	return node1;
    }
    return NEW_ARGSPUSH(node1, node2);
}

static NODE *
splat_array(NODE* node)
{
    if (nd_type(node) == NODE_SPLAT) node = node->nd_head;
    if (nd_type(node) == NODE_ARRAY) return node;
    return 0;
}

static NODE *
node_assign_gen(struct parser_params *parser, NODE *lhs, NODE *rhs)
{
    if (!lhs) return 0;

    switch (nd_type(lhs)) {
      case NODE_GASGN:
      case NODE_IASGN:
      case NODE_IASGN2:
      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_DASGN_CURR:
      case NODE_MASGN:
      case NODE_CDECL:
      case NODE_CVASGN:
	lhs->nd_value = rhs;
	break;

      case NODE_ATTRASGN:
      case NODE_CALL:
	lhs->nd_args = arg_append(lhs->nd_args, rhs);
	break;

      default:
	/* should not happen */
	break;
    }

    return lhs;
}

static int
value_expr_gen(struct parser_params *parser, NODE *node)
{
    int cond = 0;

    if (!node) {
	rb_warning0("empty expression");
    }
    while (node) {
	switch (nd_type(node)) {
	  case NODE_RETURN:
	  case NODE_BREAK:
	  case NODE_NEXT:
	  case NODE_REDO:
	  case NODE_RETRY:
	    if (!cond) yyerror("void value expression");
	    /* or "control never reach"? */
	    return FALSE;

	  case NODE_BLOCK:
	    while (node->nd_next) {
		node = node->nd_next;
	    }
	    node = node->nd_head;
	    break;

	  case NODE_BEGIN:
	    node = node->nd_body;
	    break;

	  case NODE_IF:
	    if (!node->nd_body) {
		node = node->nd_else;
		break;
	    }
	    else if (!node->nd_else) {
		node = node->nd_body;
		break;
	    }
	    if (!value_expr(node->nd_body)) return FALSE;
	    node = node->nd_else;
	    break;

	  case NODE_AND:
	  case NODE_OR:
	    cond = 1;
	    node = node->nd_2nd;
	    break;

	  default:
	    return TRUE;
	}
    }

    return TRUE;
}

static void
void_expr_gen(struct parser_params *parser, NODE *node)
{
    const char *useless = 0;

    if (!RTEST(ruby_verbose)) return;

    if (!node) return;
    switch (nd_type(node)) {
      case NODE_CALL:
	switch (node->nd_mid) {
	  case '+':
	  case '-':
	  case '*':
	  case '/':
	  case '%':
	  case tPOW:
	  case tUPLUS:
	  case tUMINUS:
	  case '|':
	  case '^':
	  case '&':
	  case tCMP:
	  case '>':
	  case tGEQ:
	  case '<':
	  case tLEQ:
	  case tEQ:
	  case tNEQ:
	    useless = rb_id2name(node->nd_mid);
	    break;
	}
	break;

      case NODE_LVAR:
      case NODE_DVAR:
      case NODE_GVAR:
      case NODE_IVAR:
      case NODE_CVAR:
      case NODE_NTH_REF:
      case NODE_BACK_REF:
	useless = "a variable";
	break;
      case NODE_CONST:
	useless = "a constant";
	break;
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	useless = "a literal";
	break;
      case NODE_COLON2:
      case NODE_COLON3:
	useless = "::";
	break;
      case NODE_DOT2:
	useless = "..";
	break;
      case NODE_DOT3:
	useless = "...";
	break;
      case NODE_SELF:
	useless = "self";
	break;
      case NODE_NIL:
	useless = "nil";
	break;
      case NODE_TRUE:
	useless = "true";
	break;
      case NODE_FALSE:
	useless = "false";
	break;
      case NODE_DEFINED:
	useless = "defined?";
	break;
    }

    if (useless) {
	int line = ruby_sourceline;

	ruby_sourceline = nd_line(node);
	rb_warnS("possibly useless use of %s in void context", useless);
	ruby_sourceline = line;
    }
}

static void
void_stmts_gen(struct parser_params *parser, NODE *node)
{
    if (!RTEST(ruby_verbose)) return;
    if (!node) return;
    if (nd_type(node) != NODE_BLOCK) return;

    for (;;) {
	if (!node->nd_next) return;
	void_expr0(node->nd_head);
	node = node->nd_next;
    }
}

static NODE *
remove_begin(NODE *node)
{
    NODE **n = &node, *n1 = node;
    while (n1 && nd_type(n1) == NODE_BEGIN && n1->nd_body) {
	*n = n1 = n1->nd_body;
    }
    return node;
}

static NODE *
remove_begin_all(NODE *node)
{
    NODE **n = &node, *n1 = node;
    while (n1 && nd_type(n1) == NODE_BEGIN) {
	*n = n1 = n1->nd_body;
    }
    return node;
}

static void
reduce_nodes_gen(struct parser_params *parser, NODE **body)
{
    NODE *node = *body;

    if (!node) {
	*body = NEW_NIL();
	return;
    }
#define subnodes(n1, n2) \
    ((!node->n1) ? (node->n2 ? (body = &node->n2, 1) : 0) : \
     (!node->n2) ? (body = &node->n1, 1) : \
     (reduce_nodes(&node->n1), body = &node->n2, 1))

    while (node) {
	int newline = (int)(node->flags & NODE_FL_NEWLINE);
	switch (nd_type(node)) {
	  end:
	  case NODE_NIL:
	    *body = 0;
	    return;
	  case NODE_RETURN:
	    *body = node = node->nd_stts;
	    if (newline && node) node->flags |= NODE_FL_NEWLINE;
	    continue;
	  case NODE_BEGIN:
	    *body = node = node->nd_body;
	    if (newline && node) node->flags |= NODE_FL_NEWLINE;
	    continue;
	  case NODE_BLOCK:
	    body = &node->nd_end->nd_head;
	    break;
	  case NODE_IF:
	    if (subnodes(nd_body, nd_else)) break;
	    return;
	  case NODE_CASE:
	    body = &node->nd_body;
	    break;
	  case NODE_WHEN:
	    if (!subnodes(nd_body, nd_next)) goto end;
	    break;
	  case NODE_ENSURE:
	    if (!subnodes(nd_head, nd_resq)) goto end;
	    break;
	  case NODE_RESCUE:
	    if (node->nd_else) {
		body = &node->nd_resq;
		break;
	    }
	    if (!subnodes(nd_head, nd_resq)) goto end;
	    break;
	  default:
	    return;
	}
	node = *body;
	if (newline && node) node->flags |= NODE_FL_NEWLINE;
    }

#undef subnodes
}

static int
is_static_content(NODE *node)
{
    if (!node) return 1;
    switch (nd_type(node)) {
      case NODE_HASH:
	if (!(node = node->nd_head)) break;
      case NODE_ARRAY:
	do {
	    if (!is_static_content(node->nd_head)) return 0;
	} while ((node = node->nd_next) != 0);
      case NODE_LIT:
      case NODE_STR:
      case NODE_NIL:
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_ZARRAY:
	break;
      default:
	return 0;
    }
    return 1;
}

static int
assign_in_cond(struct parser_params *parser, NODE *node)
{
    switch (nd_type(node)) {
      case NODE_MASGN:
	yyerror("multiple assignment in conditional");
	return 1;

      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_DASGN_CURR:
      case NODE_GASGN:
      case NODE_IASGN:
	break;

      default:
	return 0;
    }

    if (!node->nd_value) return 1;
    if (is_static_content(node->nd_value)) {
	/* reports always */
	parser_warn(node->nd_value, "found = in conditional, should be ==");
    }
    return 1;
}

static void
warn_unless_e_option(struct parser_params *parser, NODE *node, const char *str)
{
    if (!e_option_supplied(parser)) parser_warn(node, str);
}

static void
warning_unless_e_option(struct parser_params *parser, NODE *node, const char *str)
{
    if (!e_option_supplied(parser)) parser_warning(node, str);
}

static void
fixup_nodes(NODE **rootnode)
{
    NODE *node, *next, *head;

    for (node = *rootnode; node; node = next) {
	enum node_type type;
	VALUE val;

	next = node->nd_next;
	head = node->nd_head;
	rb_gc_force_recycle((VALUE)node);
	*rootnode = next;
	switch (type = nd_type(head)) {
	  case NODE_DOT2:
	  case NODE_DOT3:
	    val = rb_range_new(head->nd_beg->nd_lit, head->nd_end->nd_lit,
			       type == NODE_DOT3);
	    rb_gc_force_recycle((VALUE)head->nd_beg);
	    rb_gc_force_recycle((VALUE)head->nd_end);
	    nd_set_type(head, NODE_LIT);
	    head->nd_lit = val;
	    break;
	  default:
	    break;
	}
    }
}

static NODE *cond0(struct parser_params*,NODE*);

static NODE*
range_op(struct parser_params *parser, NODE *node)
{
    enum node_type type;

    if (node == 0) return 0;

    type = nd_type(node);
    value_expr(node);
    if (type == NODE_LIT && FIXNUM_P(node->nd_lit)) {
	warn_unless_e_option(parser, node, "integer literal in conditional range");
	return NEW_CALL(node, tEQ, NEW_LIST(NEW_GVAR(rb_intern("$."))));
    }
    return cond0(parser, node);
}

static int
literal_node(NODE *node)
{
    if (!node) return 1;	/* same as NODE_NIL */
    switch (nd_type(node)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_EVSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
      case NODE_DSYM:
	return 2;
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_NIL:
	return 1;
    }
    return 0;
}

static NODE*
cond0(struct parser_params *parser, NODE *node)
{
    if (node == 0) return 0;
    assign_in_cond(parser, node);

    switch (nd_type(node)) {
      case NODE_DSTR:
      case NODE_EVSTR:
      case NODE_STR:
	rb_warn0("string literal in condition");
	break;

      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	warning_unless_e_option(parser, node, "regex literal in condition");
	return NEW_MATCH2(node, NEW_GVAR(rb_intern("$_")));

      case NODE_AND:
      case NODE_OR:
	node->nd_1st = cond0(parser, node->nd_1st);
	node->nd_2nd = cond0(parser, node->nd_2nd);
	break;

      case NODE_DOT2:
      case NODE_DOT3:
	node->nd_beg = range_op(parser, node->nd_beg);
	node->nd_end = range_op(parser, node->nd_end);
	if (nd_type(node) == NODE_DOT2) nd_set_type(node,NODE_FLIP2);
	else if (nd_type(node) == NODE_DOT3) nd_set_type(node, NODE_FLIP3);
	if (!e_option_supplied(parser)) {
	    int b = literal_node(node->nd_beg);
	    int e = literal_node(node->nd_end);
	    if ((b == 1 && e == 1) || (b + e >= 2 && RTEST(ruby_verbose))) {
		parser_warn(node, "range literal in condition");
	    }
	}
	break;

      case NODE_DSYM:
	parser_warning(node, "literal in condition");
	break;

      case NODE_LIT:
	if (RB_TYPE_P(node->nd_lit, T_REGEXP)) {
	    warn_unless_e_option(parser, node, "regex literal in condition");
	    nd_set_type(node, NODE_MATCH);
	}
	else {
	    parser_warning(node, "literal in condition");
	}
      default:
	break;
    }
    return node;
}

static NODE*
cond_gen(struct parser_params *parser, NODE *node)
{
    if (node == 0) return 0;
    return cond0(parser, node);
}

static NODE*
logop_gen(struct parser_params *parser, enum node_type type, NODE *left, NODE *right)
{
    value_expr(left);
    if (left && (enum node_type)nd_type(left) == type) {
	NODE *node = left, *second;
	while ((second = node->nd_2nd) != 0 && (enum node_type)nd_type(second) == type) {
	    node = second;
	}
	node->nd_2nd = NEW_NODE(type, second, right, 0);
	return left;
    }
    return NEW_NODE(type, left, right, 0);
}

static void
no_blockarg(struct parser_params *parser, NODE *node)
{
    if (node && nd_type(node) == NODE_BLOCK_PASS) {
	compile_error(PARSER_ARG "block argument should not be given");
    }
}

static NODE *
ret_args_gen(struct parser_params *parser, NODE *node)
{
    if (node) {
	no_blockarg(parser, node);
	if (nd_type(node) == NODE_ARRAY) {
	    if (node->nd_next == 0) {
		node = node->nd_head;
	    }
	    else {
		nd_set_type(node, NODE_VALUES);
	    }
	}
    }
    return node;
}

static NODE *
new_yield_gen(struct parser_params *parser, NODE *node)
{
    if (node) no_blockarg(parser, node);

    return NEW_YIELD(node);
}

static VALUE
negate_lit(VALUE lit)
{
    int type = TYPE(lit);
    switch (type) {
      case T_FIXNUM:
	lit = LONG2FIX(-FIX2LONG(lit));
	break;
      case T_BIGNUM:
      case T_RATIONAL:
      case T_COMPLEX:
	lit = rb_funcall(lit,tUMINUS,0,0);
	break;
      case T_FLOAT:
#if USE_FLONUM
	if (FLONUM_P(lit)) {
	    lit = DBL2NUM(-RFLOAT_VALUE(lit));
	    break;
	}
#endif
	RFLOAT(lit)->float_value = -RFLOAT_VALUE(lit);
	break;
      default:
	rb_bug("unknown literal type (%d) passed to negate_lit", type);
	break;
    }
    return lit;
}

static NODE *
arg_blk_pass(NODE *node1, NODE *node2)
{
    if (node2) {
	node2->nd_head = node1;
	return node2;
    }
    return node1;
}


static NODE*
new_args_gen(struct parser_params *parser, NODE *m, NODE *o, ID r, NODE *p, NODE *tail)
{
    int saved_line = ruby_sourceline;
    struct rb_args_info *args = tail->nd_ainfo;

    args->pre_args_num   = m ? rb_long2int(m->nd_plen) : 0;
    args->pre_init       = m ? m->nd_next : 0;

    args->post_args_num  = p ? rb_long2int(p->nd_plen) : 0;
    args->post_init      = p ? p->nd_next : 0;
    args->first_post_arg = p ? p->nd_pid : 0;

    args->rest_arg       = r;

    args->opt_args       = o;

    ruby_sourceline = saved_line;

    return tail;
}

static NODE*
new_args_tail_gen(struct parser_params *parser, NODE *k, ID kr, ID b)
{
    int saved_line = ruby_sourceline;
    struct rb_args_info *args;
    NODE *kw_rest_arg = 0;
    NODE *node;
    int check = 0;

    args = ZALLOC(struct rb_args_info);
    node = NEW_NODE(NODE_ARGS, 0, 0, args);

    args->block_arg      = b;
    args->kw_args        = k;
    if (k && !kr) {
	check = 1;
	kr = internal_id();
    }
    if (kr) {
	arg_var(kr);
	kw_rest_arg  = NEW_DVAR(kr);
	kw_rest_arg->nd_cflag = check;
    }
    args->kw_rest_arg    = kw_rest_arg;

    ruby_sourceline = saved_line;
    return node;
}

static NODE*
dsym_node_gen(struct parser_params *parser, NODE *node)
{
    VALUE lit;

    if (!node) {
	return NEW_LIT(ID2SYM(idNULL));
    }

    switch (nd_type(node)) {
      case NODE_DSTR:
	nd_set_type(node, NODE_DSYM);
	break;
      case NODE_STR:
	lit = node->nd_lit;
	node->nd_lit = ID2SYM(rb_intern_str(lit));
	nd_set_type(node, NODE_LIT);
	break;
      default:
	node = NEW_NODE(NODE_DSYM, Qnil, 1, NEW_LIST(node));
	break;
    }
    return node;
}
#endif /* !RIPPER */

#ifndef RIPPER
static NODE *
new_op_assign_gen(struct parser_params *parser, NODE *lhs, ID op, NODE *rhs)
{
    NODE *asgn;

    if (lhs) {
	ID vid = lhs->nd_vid;
	if (op == tOROP) {
	    lhs->nd_value = rhs;
	    asgn = NEW_OP_ASGN_OR(gettable(vid), lhs);
	    if (is_notop_id(vid)) {
		switch (id_type(vid)) {
		  case ID_GLOBAL:
		  case ID_INSTANCE:
		  case ID_CLASS:
		    asgn->nd_aid = vid;
		}
	    }
	}
	else if (op == tANDOP) {
	    lhs->nd_value = rhs;
	    asgn = NEW_OP_ASGN_AND(gettable(vid), lhs);
	}
	else {
	    asgn = lhs;
	    asgn->nd_value = NEW_CALL(gettable(vid), op, NEW_LIST(rhs));
	}
    }
    else {
	asgn = NEW_BEGIN(0);
    }
    return asgn;
}

static NODE *
new_attr_op_assign_gen(struct parser_params *parser, NODE *lhs, ID attr, ID op, NODE *rhs)
{
    NODE *asgn;

    if (op == tOROP) {
	op = 0;
    }
    else if (op == tANDOP) {
	op = 1;
    }
    asgn = NEW_OP_ASGN2(lhs, attr, op, rhs);
    fixpos(asgn, lhs);
    return asgn;
}

static NODE *
new_const_op_assign_gen(struct parser_params *parser, NODE *lhs, ID op, NODE *rhs)
{
    NODE *asgn;

    if (op == tOROP) {
	op = 0;
    }
    else if (op == tANDOP) {
	op = 1;
    }
    if (lhs) {
	asgn = NEW_OP_CDECL(lhs, op, rhs);
    }
    else {
	asgn = NEW_BEGIN(0);
    }
    fixpos(asgn, lhs);
    return asgn;
}
#else
static VALUE
new_op_assign_gen(struct parser_params *parser, VALUE lhs, VALUE op, VALUE rhs)
{
    return dispatch3(opassign, lhs, op, rhs);
}

static VALUE
new_attr_op_assign_gen(struct parser_params *parser, VALUE lhs, VALUE type, VALUE attr, VALUE op, VALUE rhs)
{
    VALUE recv = dispatch3(field, lhs, type, attr);
    return dispatch3(opassign, recv, op, rhs);
}
#endif

static void
warn_unused_var(struct parser_params *parser, struct local_vars *local)
{
    int i, cnt;
    ID *v, *u;

    if (!local->used) return;
    v = local->vars->tbl;
    u = local->used->tbl;
    cnt = local->used->pos;
    if (cnt != local->vars->pos) {
	rb_bug("local->used->pos != local->vars->pos");
    }
    for (i = 0; i < cnt; ++i) {
	if (!v[i] || (u[i] & LVAR_USED)) continue;
	if (is_private_local_id(v[i])) continue;
	rb_warn4V(ruby_sourcefile, (int)u[i], "assigned but unused variable - %"PRIsVALUE, rb_id2str(v[i]));
    }
}

static void
local_push_gen(struct parser_params *parser, int inherit_dvars)
{
    struct local_vars *local;

    local = ALLOC(struct local_vars);
    local->prev = lvtbl;
    local->args = vtable_alloc(0);
    local->vars = vtable_alloc(inherit_dvars ? DVARS_INHERIT : DVARS_TOPSCOPE);
    local->used = !(inherit_dvars &&
		    (ifndef_ripper(compile_for_eval || e_option_supplied(parser))+0)) &&
	RTEST(ruby_verbose) ? vtable_alloc(0) : 0;
    local->cmdargs = cmdarg_stack;
    cmdarg_stack = 0;
    lvtbl = local;
}

static void
local_pop_gen(struct parser_params *parser)
{
    struct local_vars *local = lvtbl->prev;
    if (lvtbl->used) {
	warn_unused_var(parser, lvtbl);
	vtable_free(lvtbl->used);
    }
    vtable_free(lvtbl->args);
    vtable_free(lvtbl->vars);
    cmdarg_stack = lvtbl->cmdargs;
    xfree(lvtbl);
    lvtbl = local;
}

#ifndef RIPPER
static ID*
local_tbl_gen(struct parser_params *parser)
{
    int cnt_args = vtable_size(lvtbl->args);
    int cnt_vars = vtable_size(lvtbl->vars);
    int cnt = cnt_args + cnt_vars;
    int i, j;
    ID *buf;

    if (cnt <= 0) return 0;
    buf = ALLOC_N(ID, cnt + 1);
    MEMCPY(buf+1, lvtbl->args->tbl, ID, cnt_args);
    /* remove IDs duplicated to warn shadowing */
    for (i = 0, j = cnt_args+1; i < cnt_vars; ++i) {
	ID id = lvtbl->vars->tbl[i];
	if (!vtable_included(lvtbl->args, id)) {
	    buf[j++] = id;
	}
    }
    if (--j < cnt) REALLOC_N(buf, ID, (cnt = j) + 1);
    buf[0] = cnt;
    return buf;
}
#endif

static void
arg_var_gen(struct parser_params *parser, ID id)
{
    vtable_add(lvtbl->args, id);
}

static void
local_var_gen(struct parser_params *parser, ID id)
{
    vtable_add(lvtbl->vars, id);
    if (lvtbl->used) {
	vtable_add(lvtbl->used, (ID)ruby_sourceline);
    }
}

static int
local_id_gen(struct parser_params *parser, ID id)
{
    struct vtable *vars, *args, *used;

    vars = lvtbl->vars;
    args = lvtbl->args;
    used = lvtbl->used;

    while (vars && POINTER_P(vars->prev)) {
	vars = vars->prev;
	args = args->prev;
	if (used) used = used->prev;
    }

    if (vars && vars->prev == DVARS_INHERIT) {
	return rb_local_defined(id);
    }
    else if (vtable_included(args, id)) {
	return 1;
    }
    else {
	int i = vtable_included(vars, id);
	if (i && used) used->tbl[i-1] |= LVAR_USED;
	return i != 0;
    }
}

static const struct vtable *
dyna_push_gen(struct parser_params *parser)
{
    lvtbl->args = vtable_alloc(lvtbl->args);
    lvtbl->vars = vtable_alloc(lvtbl->vars);
    if (lvtbl->used) {
	lvtbl->used = vtable_alloc(lvtbl->used);
    }
    return lvtbl->args;
}

static void
dyna_pop_1(struct parser_params *parser)
{
    struct vtable *tmp;

    if ((tmp = lvtbl->used) != 0) {
	warn_unused_var(parser, lvtbl);
	lvtbl->used = lvtbl->used->prev;
	vtable_free(tmp);
    }
    tmp = lvtbl->args;
    lvtbl->args = lvtbl->args->prev;
    vtable_free(tmp);
    tmp = lvtbl->vars;
    lvtbl->vars = lvtbl->vars->prev;
    vtable_free(tmp);
}

static void
dyna_pop_gen(struct parser_params *parser, const struct vtable *lvargs)
{
    while (lvtbl->args != lvargs) {
	dyna_pop_1(parser);
	if (!lvtbl->args) {
	    struct local_vars *local = lvtbl->prev;
	    xfree(lvtbl);
	    lvtbl = local;
	}
    }
    dyna_pop_1(parser);
}

static int
dyna_in_block_gen(struct parser_params *parser)
{
    return POINTER_P(lvtbl->vars) && lvtbl->vars->prev != DVARS_TOPSCOPE;
}

static int
dvar_defined_gen(struct parser_params *parser, ID id, int get)
{
    struct vtable *vars, *args, *used;
    int i;

    args = lvtbl->args;
    vars = lvtbl->vars;
    used = lvtbl->used;

    while (POINTER_P(vars)) {
	if (vtable_included(args, id)) {
	    return 1;
	}
	if ((i = vtable_included(vars, id)) != 0) {
	    if (used) used->tbl[i-1] |= LVAR_USED;
	    return 1;
	}
	args = args->prev;
	vars = vars->prev;
	if (get) used = 0;
	if (used) used = used->prev;
    }

    if (vars == DVARS_INHERIT) {
        return rb_dvar_defined(id);
    }

    return 0;
}

static int
dvar_curr_gen(struct parser_params *parser, ID id)
{
    return (vtable_included(lvtbl->args, id) ||
	    vtable_included(lvtbl->vars, id));
}

#ifndef RIPPER
static void
reg_fragment_setenc_gen(struct parser_params* parser, VALUE str, int options)
{
    int c = RE_OPTION_ENCODING_IDX(options);

    if (c) {
	int opt, idx;
	rb_char_to_option_kcode(c, &opt, &idx);
	if (idx != ENCODING_GET(str) &&
	    rb_enc_str_coderange(str) != ENC_CODERANGE_7BIT) {
            goto error;
	}
	ENCODING_SET(str, idx);
    }
    else if (RE_OPTION_ENCODING_NONE(options)) {
        if (!ENCODING_IS_ASCII8BIT(str) &&
            rb_enc_str_coderange(str) != ENC_CODERANGE_7BIT) {
            c = 'n';
            goto error;
        }
	rb_enc_associate(str, rb_ascii8bit_encoding());
    }
    else if (current_enc == rb_usascii_encoding()) {
	if (rb_enc_str_coderange(str) != ENC_CODERANGE_7BIT) {
	    /* raise in re.c */
	    rb_enc_associate(str, rb_usascii_encoding());
	}
	else {
	    rb_enc_associate(str, rb_ascii8bit_encoding());
	}
    }
    return;

  error:
    compile_error(PARSER_ARG
        "regexp encoding option '%c' differs from source encoding '%s'",
        c, rb_enc_name(rb_enc_get(str)));
}

static int
reg_fragment_check_gen(struct parser_params* parser, VALUE str, int options)
{
    VALUE err;
    reg_fragment_setenc(str, options);
    err = rb_reg_check_preprocess(str);
    if (err != Qnil) {
        err = rb_obj_as_string(err);
        compile_error(PARSER_ARG "%"PRIsVALUE, err);
	return 0;
    }
    return 1;
}

typedef struct {
    struct parser_params* parser;
    rb_encoding *enc;
    NODE *succ_block;
    NODE *fail_block;
    int num;
} reg_named_capture_assign_t;

static int
reg_named_capture_assign_iter(const OnigUChar *name, const OnigUChar *name_end,
          int back_num, int *back_refs, OnigRegex regex, void *arg0)
{
    reg_named_capture_assign_t *arg = (reg_named_capture_assign_t*)arg0;
    struct parser_params* parser = arg->parser;
    rb_encoding *enc = arg->enc;
    long len = name_end - name;
    const char *s = (const char *)name;
    ID var;

    arg->num++;

    if (arg->succ_block == 0) {
        arg->succ_block = NEW_BEGIN(0);
        arg->fail_block = NEW_BEGIN(0);
    }

    if (!len || (*name != '_' && ISASCII(*name) && !rb_enc_islower(*name, enc)) ||
	(len < MAX_WORD_LENGTH && rb_reserved_word(s, (int)len)) ||
	!rb_enc_symname2_p(s, len, enc)) {
        return ST_CONTINUE;
    }
    var = intern_cstr(s, len, enc);
    if (dvar_defined(var) || local_id(var)) {
        rb_warningV("named capture conflicts a local variable - %"PRIsVALUE,
                    rb_id2str(var));
    }
    arg->succ_block = block_append(arg->succ_block,
        newline_node(node_assign(assignable(var,0),
            NEW_CALL(
              gettable(rb_intern("$~")),
              idAREF,
              NEW_LIST(NEW_LIT(ID2SYM(var))))
            )));
    arg->fail_block = block_append(arg->fail_block,
        newline_node(node_assign(assignable(var,0), NEW_LIT(Qnil))));
    return ST_CONTINUE;
}

static NODE *
reg_named_capture_assign_gen(struct parser_params* parser, VALUE regexp, NODE *match)
{
    reg_named_capture_assign_t arg;

    arg.parser = parser;
    arg.enc = rb_enc_get(regexp);
    arg.succ_block = 0;
    arg.fail_block = 0;
    arg.num = 0;
    onig_foreach_name(RREGEXP(regexp)->ptr, reg_named_capture_assign_iter, &arg);

    if (arg.num == 0)
        return match;

    return
        block_append(
            newline_node(match),
            NEW_IF(gettable(rb_intern("$~")),
                block_append(
                    newline_node(arg.succ_block),
                    newline_node(
                        NEW_CALL(
                          gettable(rb_intern("$~")),
                          rb_intern("begin"),
                          NEW_LIST(NEW_LIT(INT2FIX(0)))))),
                block_append(
                    newline_node(arg.fail_block),
                    newline_node(
                        NEW_LIT(Qnil)))));
}

static VALUE
reg_compile_gen(struct parser_params* parser, VALUE str, int options)
{
    VALUE re;
    VALUE err;

    reg_fragment_setenc(str, options);
    err = rb_errinfo();
    re = rb_reg_compile(str, options & RE_OPTION_MASK, ruby_sourcefile, ruby_sourceline);
    if (NIL_P(re)) {
	ID mesg = rb_intern("mesg");
	VALUE m = rb_attr_get(rb_errinfo(), mesg);
	rb_set_errinfo(err);
	if (!NIL_P(err)) {
	    rb_str_append(rb_str_cat(rb_attr_get(err, mesg), "\n", 1), m);
	}
	else {
	    compile_error(PARSER_ARG "%"PRIsVALUE, m);
	}
	return Qnil;
    }
    return re;
}

NODE*
rb_parser_append_print(VALUE vparser, NODE *node)
{
    NODE *prelude = 0;
    NODE *scope = node;
    struct parser_params *parser;

    if (!node) return node;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);

    node = node->nd_body;

    if (nd_type(node) == NODE_PRELUDE) {
	prelude = node;
	node = node->nd_body;
    }

    node = block_append(node,
			NEW_FCALL(rb_intern("print"),
				  NEW_ARRAY(NEW_GVAR(rb_intern("$_")))));
    if (prelude) {
	prelude->nd_body = node;
	scope->nd_body = prelude;
    }
    else {
	scope->nd_body = node;
    }

    return scope;
}

NODE *
rb_parser_while_loop(VALUE vparser, NODE *node, int chop, int split)
{
    NODE *prelude = 0;
    NODE *scope = node;
    struct parser_params *parser;

    if (!node) return node;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);

    node = node->nd_body;

    if (nd_type(node) == NODE_PRELUDE) {
	prelude = node;
	node = node->nd_body;
    }
    if (split) {
	node = block_append(NEW_GASGN(rb_intern("$F"),
				      NEW_CALL(NEW_GVAR(rb_intern("$_")),
					       rb_intern("split"), 0)),
			    node);
    }
    if (chop) {
	node = block_append(NEW_CALL(NEW_GVAR(rb_intern("$_")),
				     rb_intern("chop!"), 0), node);
    }

    node = NEW_OPT_N(node);

    if (prelude) {
	prelude->nd_body = node;
	scope->nd_body = prelude;
    }
    else {
	scope->nd_body = node;
    }

    return scope;
}

void
rb_init_parse(void)
{
    /* just to suppress unused-function warnings */
    (void)nodetype;
    (void)nodeline;
#if PARSER_DEBUG
    (void)lex_state_name(-1);
#endif
}
#endif /* !RIPPER */

static ID
internal_id_gen(struct parser_params *parser)
{
    ID id = (ID)vtable_size(lvtbl->args) + (ID)vtable_size(lvtbl->vars);
    id += ((tLAST_TOKEN - ID_INTERNAL) >> ID_SCOPE_SHIFT) + 1;
    return ID_STATIC_SYM | ID_INTERNAL | (id << ID_SCOPE_SHIFT);
}

static void
parser_initialize(struct parser_params *parser)
{
    parser->eofp = Qfalse;

    parser->parser_lex_strterm = 0;
    parser->parser_cond_stack = 0;
    parser->parser_cmdarg_stack = 0;
    parser->parser_class_nest = 0;
    parser->parser_paren_nest = 0;
    parser->parser_lpar_beg = 0;
    parser->parser_brace_nest = 0;
    parser->parser_in_single = 0;
    parser->parser_in_def = 0;
    parser->parser_in_defined = 0;
    parser->parser_in_kwarg = 0;
    parser->parser_compile_for_eval = 0;
    parser->parser_cur_mid = 0;
    parser->parser_tokenbuf = NULL;
    parser->parser_tokidx = 0;
    parser->parser_toksiz = 0;
    parser->parser_heredoc_end = 0;
    parser->parser_command_start = TRUE;
    parser->parser_deferred_nodes = 0;
    parser->parser_lex_pbeg = 0;
    parser->parser_lex_p = 0;
    parser->parser_lex_pend = 0;
    parser->parser_lvtbl = 0;
    parser->parser_ruby__end__seen = 0;
    parser->parser_ruby_sourcefile = 0;
    parser->parser_ruby_sourcefile_string = Qnil;
#ifndef RIPPER
    parser->is_ripper = 0;
    parser->parser_eval_tree_begin = 0;
    parser->parser_eval_tree = 0;
#else
    parser->is_ripper = 1;
    parser->delayed = Qnil;

    parser->result = Qnil;
    parser->parsing_thread = Qnil;
    parser->toplevel_p = TRUE;
#endif
#ifdef YYMALLOC
    parser->heap = NULL;
#endif
    parser->enc = rb_utf8_encoding();
}

#ifdef RIPPER
#define parser_mark ripper_parser_mark
#define parser_free ripper_parser_free
#endif

static void
parser_mark(void *ptr)
{
    struct parser_params *p = (struct parser_params*)ptr;

    rb_gc_mark((VALUE)p->parser_lex_strterm);
    rb_gc_mark((VALUE)p->parser_deferred_nodes);
    rb_gc_mark(p->parser_lex_input);
    rb_gc_mark(p->parser_lex_lastline);
    rb_gc_mark(p->parser_lex_nextline);
    rb_gc_mark(p->parser_ruby_sourcefile_string);
#ifndef RIPPER
    rb_gc_mark((VALUE)p->parser_eval_tree_begin) ;
    rb_gc_mark((VALUE)p->parser_eval_tree) ;
    rb_gc_mark(p->debug_lines);
#else
    rb_gc_mark(p->delayed);
    rb_gc_mark(p->value);
    rb_gc_mark(p->result);
    rb_gc_mark(p->parsing_thread);
#endif
#ifdef YYMALLOC
    rb_gc_mark((VALUE)p->heap);
#endif
}

static void
parser_free(void *ptr)
{
    struct parser_params *p = (struct parser_params*)ptr;
    struct local_vars *local, *prev;

    if (p->parser_tokenbuf) {
        xfree(p->parser_tokenbuf);
    }
    for (local = p->parser_lvtbl; local; local = prev) {
	if (local->vars) xfree(local->vars);
	prev = local->prev;
	xfree(local);
    }
    xfree(p);
}

static size_t
parser_memsize(const void *ptr)
{
    struct parser_params *p = (struct parser_params*)ptr;
    struct local_vars *local;
    size_t size = sizeof(*p);

    if (!ptr) return 0;
    size += p->parser_toksiz;
    for (local = p->parser_lvtbl; local; local = local->prev) {
	size += sizeof(*local);
	if (local->vars) size += local->vars->capa * sizeof(ID);
    }
    return size;
}

static
#ifndef RIPPER
const
#endif
rb_data_type_t parser_data_type = {
    "parser",
    {
	parser_mark,
	parser_free,
	parser_memsize,
    },
    NULL, NULL, RUBY_TYPED_FREE_IMMEDIATELY
};

#ifndef RIPPER
#undef rb_reserved_word

const struct kwtable *
rb_reserved_word(const char *str, unsigned int len)
{
    return reserved_word(str, len);
}

static struct parser_params *
parser_new(void)
{
    struct parser_params *p;

    p = ZALLOC(struct parser_params);
    parser_initialize(p);
    return p;
}

VALUE
rb_parser_new(void)
{
    struct parser_params *p = parser_new();

    return TypedData_Wrap_Struct(0, &parser_data_type, p);
}

/*
 *  call-seq:
 *    ripper#end_seen?   -> Boolean
 *
 *  Return true if parsed source ended by +\_\_END\_\_+.
 */
VALUE
rb_parser_end_seen_p(VALUE vparser)
{
    struct parser_params *parser;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    return ruby__end__seen ? Qtrue : Qfalse;
}

/*
 *  call-seq:
 *    ripper#encoding   -> encoding
 *
 *  Return encoding of the source.
 */
VALUE
rb_parser_encoding(VALUE vparser)
{
    struct parser_params *parser;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    return rb_enc_from_encoding(current_enc);
}

/*
 *  call-seq:
 *    ripper.yydebug   -> true or false
 *
 *  Get yydebug.
 */
VALUE
rb_parser_get_yydebug(VALUE self)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    return yydebug ? Qtrue : Qfalse;
}

/*
 *  call-seq:
 *    ripper.yydebug = flag
 *
 *  Set yydebug.
 */
VALUE
rb_parser_set_yydebug(VALUE self, VALUE flag)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    yydebug = RTEST(flag);
    return flag;
}

#ifdef YYMALLOC
#define HEAPCNT(n, size) ((n) * (size) / sizeof(YYSTYPE))
#define NEWHEAP() rb_node_newnode(NODE_ALLOCA, 0, (VALUE)parser->heap, 0)
#define ADD2HEAP(n, c, p) ((parser->heap = (n))->u1.node = (p), \
			   (n)->u3.cnt = (c), (p))

void *
rb_parser_malloc(struct parser_params *parser, size_t size)
{
    size_t cnt = HEAPCNT(1, size);
    NODE *n = NEWHEAP();
    void *ptr = xmalloc(size);

    return ADD2HEAP(n, cnt, ptr);
}

void *
rb_parser_calloc(struct parser_params *parser, size_t nelem, size_t size)
{
    size_t cnt = HEAPCNT(nelem, size);
    NODE *n = NEWHEAP();
    void *ptr = xcalloc(nelem, size);

    return ADD2HEAP(n, cnt, ptr);
}

void *
rb_parser_realloc(struct parser_params *parser, void *ptr, size_t size)
{
    NODE *n;
    size_t cnt = HEAPCNT(1, size);

    if (ptr && (n = parser->heap) != NULL) {
	do {
	    if (n->u1.node == ptr) {
		n->u1.node = ptr = xrealloc(ptr, size);
		if (n->u3.cnt) n->u3.cnt = cnt;
		return ptr;
	    }
	} while ((n = n->u2.node) != NULL);
    }
    n = NEWHEAP();
    ptr = xrealloc(ptr, size);
    return ADD2HEAP(n, cnt, ptr);
}

void
rb_parser_free(struct parser_params *parser, void *ptr)
{
    NODE **prev = &parser->heap, *n;

    while ((n = *prev) != NULL) {
	if (n->u1.node == ptr) {
	    *prev = n->u2.node;
	    rb_gc_force_recycle((VALUE)n);
	    break;
	}
	prev = &n->u2.node;
    }
    xfree(ptr);
}
#endif
#endif

#ifdef RIPPER
#ifdef RIPPER_DEBUG
extern int rb_is_pointer_to_heap(VALUE);

/* :nodoc: */
static VALUE
ripper_validate_object(VALUE self, VALUE x)
{
    if (x == Qfalse) return x;
    if (x == Qtrue) return x;
    if (x == Qnil) return x;
    if (x == Qundef)
        rb_raise(rb_eArgError, "Qundef given");
    if (FIXNUM_P(x)) return x;
    if (SYMBOL_P(x)) return x;
    if (!rb_is_pointer_to_heap(x))
        rb_raise(rb_eArgError, "invalid pointer: %p", x);
    switch (BUILTIN_TYPE(x)) {
      case T_STRING:
      case T_OBJECT:
      case T_ARRAY:
      case T_BIGNUM:
      case T_FLOAT:
      case T_COMPLEX:
      case T_RATIONAL:
        return x;
      case T_NODE:
	if (nd_type(x) != NODE_LASGN) {
	    rb_raise(rb_eArgError, "NODE given: %p", x);
	}
	return ((NODE *)x)->nd_rval;
      default:
        rb_raise(rb_eArgError, "wrong type of ruby object: %p (%s)",
                 x, rb_obj_classname(x));
    }
    return x;
}
#endif

#define validate(x) ((x) = get_value(x))

static VALUE
ripper_dispatch0(struct parser_params *parser, ID mid)
{
    return rb_funcall(parser->value, mid, 0);
}

static VALUE
ripper_dispatch1(struct parser_params *parser, ID mid, VALUE a)
{
    validate(a);
    return rb_funcall(parser->value, mid, 1, a);
}

static VALUE
ripper_dispatch2(struct parser_params *parser, ID mid, VALUE a, VALUE b)
{
    validate(a);
    validate(b);
    return rb_funcall(parser->value, mid, 2, a, b);
}

static VALUE
ripper_dispatch3(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c)
{
    validate(a);
    validate(b);
    validate(c);
    return rb_funcall(parser->value, mid, 3, a, b, c);
}

static VALUE
ripper_dispatch4(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c, VALUE d)
{
    validate(a);
    validate(b);
    validate(c);
    validate(d);
    return rb_funcall(parser->value, mid, 4, a, b, c, d);
}

static VALUE
ripper_dispatch5(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c, VALUE d, VALUE e)
{
    validate(a);
    validate(b);
    validate(c);
    validate(d);
    validate(e);
    return rb_funcall(parser->value, mid, 5, a, b, c, d, e);
}

static VALUE
ripper_dispatch7(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c, VALUE d, VALUE e, VALUE f, VALUE g)
{
    validate(a);
    validate(b);
    validate(c);
    validate(d);
    validate(e);
    validate(f);
    validate(g);
    return rb_funcall(parser->value, mid, 7, a, b, c, d, e, f, g);
}

static const struct kw_assoc {
    ID id;
    const char *name;
} keyword_to_name[] = {
    {keyword_class,	"class"},
    {keyword_module,	"module"},
    {keyword_def,	"def"},
    {keyword_undef,	"undef"},
    {keyword_begin,	"begin"},
    {keyword_rescue,	"rescue"},
    {keyword_ensure,	"ensure"},
    {keyword_end,	"end"},
    {keyword_if,	"if"},
    {keyword_unless,	"unless"},
    {keyword_then,	"then"},
    {keyword_elsif,	"elsif"},
    {keyword_else,	"else"},
    {keyword_case,	"case"},
    {keyword_when,	"when"},
    {keyword_while,	"while"},
    {keyword_until,	"until"},
    {keyword_for,	"for"},
    {keyword_break,	"break"},
    {keyword_next,	"next"},
    {keyword_redo,	"redo"},
    {keyword_retry,	"retry"},
    {keyword_in,	"in"},
    {keyword_do,	"do"},
    {keyword_do_cond,	"do"},
    {keyword_do_block,	"do"},
    {keyword_return,	"return"},
    {keyword_yield,	"yield"},
    {keyword_super,	"super"},
    {keyword_self,	"self"},
    {keyword_nil,	"nil"},
    {keyword_true,	"true"},
    {keyword_false,	"false"},
    {keyword_and,	"and"},
    {keyword_or,	"or"},
    {keyword_not,	"not"},
    {modifier_if,	"if"},
    {modifier_unless,	"unless"},
    {modifier_while,	"while"},
    {modifier_until,	"until"},
    {modifier_rescue,	"rescue"},
    {keyword_alias,	"alias"},
    {keyword_defined,	"defined?"},
    {keyword_BEGIN,	"BEGIN"},
    {keyword_END,	"END"},
    {keyword__LINE__,	"__LINE__"},
    {keyword__FILE__,	"__FILE__"},
    {keyword__ENCODING__, "__ENCODING__"},
    {0, NULL}
};

static const char*
keyword_id_to_str(ID id)
{
    const struct kw_assoc *a;

    for (a = keyword_to_name; a->id; a++) {
        if (a->id == id)
            return a->name;
    }
    return NULL;
}

#undef ripper_id2sym
static VALUE
ripper_id2sym(ID id)
{
    const char *name;
    char buf[8];

    if (id <= 256) {
        buf[0] = (char)id;
        buf[1] = '\0';
        return ID2SYM(rb_intern2(buf, 1));
    }
    if ((name = keyword_id_to_str(id))) {
        return ID2SYM(rb_intern(name));
    }
    switch (id) {
      case tOROP:
        name = "||";
        break;
      case tANDOP:
        name = "&&";
        break;
      default:
        if (!rb_id2str(id)) {
            rb_bug("cannot convert ID to string: %ld", (unsigned long)id);
        }
        return ID2SYM(id);
    }
    return ID2SYM(rb_intern(name));
}

static ID
ripper_get_id(VALUE v)
{
    NODE *nd;
    if (!RB_TYPE_P(v, T_NODE)) return 0;
    nd = (NODE *)v;
    if (nd_type(nd) != NODE_LASGN) return 0;
    return nd->nd_vid;
}

static VALUE
ripper_get_value(VALUE v)
{
    NODE *nd;
    if (v == Qundef) return Qnil;
    if (!RB_TYPE_P(v, T_NODE)) return v;
    nd = (NODE *)v;
    if (nd_type(nd) != NODE_LASGN) return Qnil;
    return nd->nd_rval;
}

static void
ripper_compile_error(struct parser_params *parser, const char *fmt, ...)
{
    VALUE str;
    va_list args;

    va_start(args, fmt);
    str = rb_vsprintf(fmt, args);
    va_end(args);
    rb_funcall(parser->value, rb_intern("compile_error"), 1, str);
}

static void
ripper_warn0(struct parser_params *parser, const char *fmt)
{
    rb_funcall(parser->value, rb_intern("warn"), 1, STR_NEW2(fmt));
}

static void
ripper_warnI(struct parser_params *parser, const char *fmt, int a)
{
    rb_funcall(parser->value, rb_intern("warn"), 2,
               STR_NEW2(fmt), INT2NUM(a));
}

#if 0				/* not in use right now */
static void
ripper_warnS(struct parser_params *parser, const char *fmt, const char *str)
{
    rb_funcall(parser->value, rb_intern("warn"), 2,
               STR_NEW2(fmt), STR_NEW2(str));
}
#endif

static void
ripper_warnV(struct parser_params *parser, const char *fmt, VALUE v)
{
    rb_funcall(parser->value, rb_intern("warn"), 2,
               STR_NEW2(fmt), v);
}

static void
ripper_warning0(struct parser_params *parser, const char *fmt)
{
    rb_funcall(parser->value, rb_intern("warning"), 1, STR_NEW2(fmt));
}

static void
ripper_warningS(struct parser_params *parser, const char *fmt, const char *str)
{
    rb_funcall(parser->value, rb_intern("warning"), 2,
               STR_NEW2(fmt), STR_NEW2(str));
}

static void
ripper_warningV(struct parser_params *parser, const char *fmt, VALUE v)
{
    rb_funcall(parser->value, rb_intern("warning"), 2,
               STR_NEW2(fmt), v);
}

static VALUE
ripper_lex_get_generic(struct parser_params *parser, VALUE src)
{
    return rb_io_gets(src);
}

static VALUE
ripper_s_allocate(VALUE klass)
{
    struct parser_params *p;
    VALUE self;

    p = ZALLOC(struct parser_params);
    self = TypedData_Wrap_Struct(klass, &parser_data_type, p);
    p->value = self;
    return self;
}

#define ripper_initialized_p(r) ((r)->parser_lex_input != 0)

/*
 *  call-seq:
 *    Ripper.new(src, filename="(ripper)", lineno=1) -> ripper
 *
 *  Create a new Ripper object.
 *  _src_ must be a String, an IO, or an Object which has #gets method.
 *
 *  This method does not starts parsing.
 *  See also Ripper#parse and Ripper.parse.
 */
static VALUE
ripper_initialize(int argc, VALUE *argv, VALUE self)
{
    struct parser_params *parser;
    VALUE src, fname, lineno;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    rb_scan_args(argc, argv, "12", &src, &fname, &lineno);
    if (RB_TYPE_P(src, T_FILE)) {
        parser->parser_lex_gets = ripper_lex_get_generic;
    }
    else {
        StringValue(src);
        parser->parser_lex_gets = lex_get_str;
    }
    parser->parser_lex_input = src;
    parser->eofp = Qfalse;
    if (NIL_P(fname)) {
        fname = STR_NEW2("(ripper)");
	OBJ_FREEZE(fname);
    }
    else {
        StringValue(fname);
	fname = rb_str_new_frozen(fname);
    }
    parser_initialize(parser);

    parser->parser_ruby_sourcefile_string = fname;
    parser->parser_ruby_sourcefile = RSTRING_PTR(fname);
    parser->parser_ruby_sourceline = NIL_P(lineno) ? 0 : NUM2INT(lineno) - 1;

    return Qnil;
}

struct ripper_args {
    struct parser_params *parser;
    int argc;
    VALUE *argv;
};

static VALUE
ripper_parse0(VALUE parser_v)
{
    struct parser_params *parser;

    TypedData_Get_Struct(parser_v, struct parser_params, &parser_data_type, parser);
    parser_prepare(parser);
    ripper_yyparse((void*)parser);
    return parser->result;
}

static VALUE
ripper_ensure(VALUE parser_v)
{
    struct parser_params *parser;

    TypedData_Get_Struct(parser_v, struct parser_params, &parser_data_type, parser);
    parser->parsing_thread = Qnil;
    return Qnil;
}

/*
 *  call-seq:
 *    ripper#parse
 *
 *  Start parsing and returns the value of the root action.
 */
static VALUE
ripper_parse(VALUE self)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (!NIL_P(parser->parsing_thread)) {
        if (parser->parsing_thread == rb_thread_current())
            rb_raise(rb_eArgError, "Ripper#parse is not reentrant");
        else
            rb_raise(rb_eArgError, "Ripper#parse is not multithread-safe");
    }
    parser->parsing_thread = rb_thread_current();
    rb_ensure(ripper_parse0, self, ripper_ensure, self);

    return parser->result;
}

/*
 *  call-seq:
 *    ripper#column   -> Integer
 *
 *  Return column number of current parsing line.
 *  This number starts from 0.
 */
static VALUE
ripper_column(VALUE self)
{
    struct parser_params *parser;
    long col;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (NIL_P(parser->parsing_thread)) return Qnil;
    col = parser->tokp - parser->parser_lex_pbeg;
    return LONG2NUM(col);
}

/*
 *  call-seq:
 *    ripper#filename   -> String
 *
 *  Return current parsing filename.
 */
static VALUE
ripper_filename(VALUE self)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    return parser->parser_ruby_sourcefile_string;
}

/*
 *  call-seq:
 *    ripper#lineno   -> Integer
 *
 *  Return line number of current parsing line.
 *  This number starts from 1.
 */
static VALUE
ripper_lineno(VALUE self)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (NIL_P(parser->parsing_thread)) return Qnil;
    return INT2NUM(parser->parser_ruby_sourceline);
}

#ifdef RIPPER_DEBUG
/* :nodoc: */
static VALUE
ripper_assert_Qundef(VALUE self, VALUE obj, VALUE msg)
{
    StringValue(msg);
    if (obj == Qundef) {
        rb_raise(rb_eArgError, "%"PRIsVALUE, msg);
    }
    return Qnil;
}

/* :nodoc: */
static VALUE
ripper_value(VALUE self, VALUE obj)
{
    return ULONG2NUM(obj);
}
#endif


void
Init_ripper(void)
{
    parser_data_type.parent = RTYPEDDATA_TYPE(rb_parser_new());

    ripper_init_eventids1();
    ripper_init_eventids2();
    /* ensure existing in symbol table */
    (void)rb_intern("||");
    (void)rb_intern("&&");

    InitVM(ripper);
}

void
InitVM_ripper(void)
{
    VALUE Ripper;

    Ripper = rb_define_class("Ripper", rb_cObject);
    /* version of Ripper */
    rb_define_const(Ripper, "Version", rb_usascii_str_new2(RIPPER_VERSION));
    rb_define_alloc_func(Ripper, ripper_s_allocate);
    rb_define_method(Ripper, "initialize", ripper_initialize, -1);
    rb_define_method(Ripper, "parse", ripper_parse, 0);
    rb_define_method(Ripper, "column", ripper_column, 0);
    rb_define_method(Ripper, "filename", ripper_filename, 0);
    rb_define_method(Ripper, "lineno", ripper_lineno, 0);
    rb_define_method(Ripper, "end_seen?", rb_parser_end_seen_p, 0);
    rb_define_method(Ripper, "encoding", rb_parser_encoding, 0);
    rb_define_method(Ripper, "yydebug", rb_parser_get_yydebug, 0);
    rb_define_method(Ripper, "yydebug=", rb_parser_set_yydebug, 1);
#ifdef RIPPER_DEBUG
    rb_define_method(rb_mKernel, "assert_Qundef", ripper_assert_Qundef, 2);
    rb_define_method(rb_mKernel, "rawVALUE", ripper_value, 1);
    rb_define_method(rb_mKernel, "validate_object", ripper_validate_object, 1);
#endif

    ripper_init_eventids1_table(Ripper);
    ripper_init_eventids2_table(Ripper);

# if 0
    /* Hack to let RDoc document SCRIPT_LINES__ */

    /*
     * When a Hash is assigned to +SCRIPT_LINES__+ the contents of files loaded
     * after the assignment will be added as an Array of lines with the file
     * name as the key.
     */
    rb_define_global_const("SCRIPT_LINES__", Qnil);
#endif

}
#endif /* RIPPER */
