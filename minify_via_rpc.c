#include "minifyjpeg_xdr.c"
#include "minifyjpeg_clnt.c"
#include <stdio.h>
#include <rpc/rpc.h>

void*
minify_via_rpc(CLIENT *cl, void* src_val, size_t src_len, size_t *dst_len){

    input var;
    var.arg.arg_val = src_val;
    var.arg.arg_len = (u_int) src_len;
    var.size = (int*) dst_len;

    output *result = malloc(sizeof(struct output));
    result->output_u.res.res_val = malloc(sizeof(src_len));

    result = minify_proc_1(var, cl);
    if (result == (output *)NULL)
        clnt_perror (cl, "call failed");    

    void *result_val;
    result_val = (void*)result->output_u.res.res_val;
    *dst_len = (int)result->output_u.res.res_len;

    return result_val;
}

CLIENT*
get_minify_client (char* server) {

    CLIENT *cl = clnt_create(server, MINIFY_PROG, MINIFY_VERS, "tcp");

    if(cl == (CLIENT *)NULL) {
    	clnt_pcreateerror(server);
    	exit(1);
    }
    return cl;
}