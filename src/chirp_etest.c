// ===================
// Testing basic chirp
// ===================
//
// Basic test against the libchirp.so, all other tests compile against
// libchirp.a.
//

// Project includes
// ================
//
// .. code-block:: cpp
//
#include "libchirp.h"

static
void
start(ch_chirp_t* chirp)
{
    ch_chirp_close_ts(chirp);
}

// .. c:function::
int
main()
//    :noindex:
//
//    Run chirp
//
// .. code-block:: cpp
//
{
    ch_chirp_t chirp;
    uv_loop_t loop;
    ch_config_t config;
    ch_chirp_config_init(&config);
    config.CERT_CHAIN_PEM = "./cert.pem";
    config.DH_PARAMS_PEM = "./dh.pem";
    ch_libchirp_init();
    ch_loop_init(&loop);
    if(ch_chirp_init(
            &chirp,
            &config,
            &loop,
            start,
            NULL,
            NULL
    ) != CH_SUCCESS) {
        printf("ch_chirp_init error\n");
        return 1;
    }
    ch_chirp_set_auto_stop_loop(&chirp);
    ch_run(&loop);
    int tmp_err = ch_loop_close(&loop);
    ch_libchirp_cleanup();
    return tmp_err;
}
