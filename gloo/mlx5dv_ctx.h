/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

//#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
extern "C"{
#include <infiniband/mlx5dv.h>
}

#include <infiniband/verbs_exp.h>


#define IB_ACCESS_FLAGS (IBV_ACCESS_LOCAL_WRITE  | \
                                                 IBV_ACCESS_REMOTE_WRITE | \
                                                 IBV_ACCESS_REMOTE_READ)


#define PCX_ERROR(exp) \
class PCX_ERR_##exp: public std::exception{				\
    const char* what() const throw() { return  #exp ; };		\
};

#define PCX_ERROR_RES(exp) 						\
class PCX_ERR_##exp: public std::exception{				\
public:									\
    PCX_ERR_##exp(int val): std::exception(), x(val){};			\
    const char* what() const throw() { 					\
	/*sprintf( str, \"%s %d\n\", #exp , x );*/			\
	return #exp ; 							\
    };									\
private:								\
	int x;								\
	char str[50];							\
};

#define PERR(exp) throw PCX_ERR_##exp();
#define RES_ERR(exp,val) throw PCX_ERR_##exp (  val  );





#ifdef DEBUG
#define PRINT(x) fprintf(stderr, "%s\n", x);
#define PRINTF(f_, ...) fprintf(stderr ,(f_), ##__VA_ARGS__)
#else
#define PRINT(x)
#define PRINTF(f_, ...) 
#endif

#define RX_SIZE 16
#define CX_SIZE 16

class verb_ctx_t{
public:


	verb_ctx_t(char *ib_devname=nullptr, int port=1);
	~verb_ctx_t();


        struct ibv_context      *context;
        struct ibv_pd           *pd;
        struct ibv_cq           *umr_cq;
        struct ibv_qp           *umr_qp;
        struct ibv_comp_channel *channel;
        struct ibv_exp_device_attr attrs;
};

