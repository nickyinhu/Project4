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
    enum clnt_stat retval;

    printf("%s\n", "1");

    printf("Input file size is: %d\n", var.arg.arg_len);

    output result;
    result.output_u.res.res_val = malloc(sizeof(src_len));
    result.output_u.res.res_len = malloc(sizeof(u_int));

    printf("%s\n", "2");

    retval = minify_proc_1(var, &result, cl);
    if (retval != RPC_SUCCESS) {
        clnt_perror (cl, "call failed");
    }

    printf("%s\n", "3");

    void *result_val = (void*)result.output_u.res.res_val;
    *dst_len = (int)result.output_u.res.res_len;

    printf("Output file size is: %d\n", (int)result.output_u.res.res_len);
    printf("Actual output file size is: %d\n", *dst_len);

    return result.output_u.res.res_val;
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