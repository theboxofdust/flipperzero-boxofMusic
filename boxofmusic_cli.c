#include <furi.h>
#include <cli/cli.h>
#include <storage/storage.h>
#include "boxofmusic_worker.h"

static void boxofmusic_cli(Cli* cli, FuriString* args, void* context) {
    UNUSED(context);
    boxofMusicWorker* boxofmusic_worker = boxofmusic_worker_alloc();
    Storage* storage = furi_record_open(RECORD_STORAGE);

    do {
        if(storage_common_stat(storage, furi_string_get_cstr(args), NULL) == FSE_OK) {
            if(!boxofmusic_worker_load(boxofmusic_worker, furi_string_get_cstr(args))) {
                printf("Failed to open file %s\r\n", furi_string_get_cstr(args));
                break;
            }
        } else {
            if(!boxofmusic_worker_load_rtttl_from_string(
                   boxofmusic_worker, furi_string_get_cstr(args))) {
                printf("Argument is not a file or RTTTL\r\n");
                break;
            }
        }

        printf("Press CTRL+C to stop\r\n");
        boxofmusic_worker_set_volume(boxofmusic_worker, 1.0f);
        boxofmusic_worker_start(boxofmusic_worker);
        while(!cli_cmd_interrupt_received(cli)) {
            furi_delay_ms(50);
        }
        boxofmusic_worker_stop(boxofmusic_worker);
    } while(0);

    furi_record_close(RECORD_STORAGE);
    boxofmusic_worker_free(boxofmusic_worker);
}

void boxofmusic_on_system_start() {
#ifdef SRV_CLI
    Cli* cli = furi_record_open(RECORD_CLI);

    cli_add_command(cli, "boxofmusic", CliCommandFlagDefault, boxofmusic_cli, NULL);

    furi_record_close(RECORD_CLI);
#else
    UNUSED(boxofmusic_cli);
#endif
}
