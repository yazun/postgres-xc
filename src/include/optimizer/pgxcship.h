/*-------------------------------------------------------------------------
 *
 * pgxcship.h
 *		Functionalities for the evaluation of expression shippability
 *		to remote nodes
 *
 *
 * Portions Copyright (c) 1996-2012 PostgreSQL Global Development Group
 * Portions Copyright (c) 2010-2012 Postgres-XC Development Group
 *
 * src/include/optimizer/pgxcship.h
 *
 *-------------------------------------------------------------------------
 */

#ifndef PGXCSHIP_H
#define PGXCSHIP_H

#include "nodes/parsenodes.h"
#include "nodes/relation.h"
#include "pgxc/locator.h"


/* Determine if query is shippable */
extern ExecNodes *pgxc_is_query_shippable(Query *query, int query_level);
/* Determine if an expression is shippable */
extern bool pgxc_is_expr_shippable(Expr *node, bool *has_aggs);
/* Determine if given function is shippable */
extern bool pgxc_is_func_shippable(Oid funcid);
/* Check equijoin conditions on given relations */
extern bool pgxc_qual_has_dist_equijoin(Relids varnos_1,
	Relids varnos_2, Oid distcol_type, Node *quals, List *rtable);
/* Merge given execution nodes based on join shippability conditions */
extern ExecNodes *pgxc_merge_exec_nodes(ExecNodes *en1,
	ExecNodes *en2, bool merge_dist_equijoin, bool merge_replicated_only);
/* Check if given Query includes distribution column */
extern bool pgxc_query_has_distcolgrouping(Query *query);
/* Check the shippability of an index */
extern bool pgxc_check_index_shippability(RelationLocInfo *relLocInfo,
									   bool is_primary,
									   bool is_unique,
									   bool is_exclusion,
									   List *indexAttrs,
									   List *indexExprs);
/* Check the shippability of a parent-child constraint */
extern bool pgxc_check_fk_shippability(RelationLocInfo *parentLocInfo,
									   RelationLocInfo *childLocInfo,
									   List *parentRefs,
									   List *childRefs);

#endif
