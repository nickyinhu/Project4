#include "minifyjpeg_xdr.c"
#include "minifyjpeg_clnt.c"
#include <stdio.h>
#include <rpc/rpc.h>

void*
minify_via_rpc(CLIENT *cl, void* src_val, size_t src_len, size_t *dst_len){
  /*
    * Use RPC to obtain a minified version of the jpeg image
    * stored in the array src_val and having src_len bytes.
    */
    input var;
    output *result;

    printf("%s\n", (char *)src_val);

    void *result_val;
    result_val = malloc(sizeof(void*));

    memcpy(var.arg.arg_val,src_val,sizeof(void*));
    var.arg.arg_len = src_len;
    var.size = malloc(*dst_len);

    minify_proc_1(var,&result,cl);

    memcpy(result_val,result->res.res_val,sizeof(void*));

    return result_val;

}

CLIENT*
get_minify_client (char* server) {

    CLIENT *cl;

    cl = clnt_create(server, MINIFY_PROG, MINIFY_VERS, "tcp");

    if(cl == NULL) {
    	clnt_pcreateerror(server);
    	exit(1);
    }

    return cl;

}