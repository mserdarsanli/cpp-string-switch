// (C) Copyright 2018 Mustafa Serdar Sanli <mserdarsanli@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <string>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "search.hpp"

TEST_CASE( "ada" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "else", "exit", "terminate", "type", "raise", "range", "reverse",
        "declare", "end", "record", "exception", "not", "then", "return",
        "separate", "select", "digits", "renames", "subtype", "elsif",
        "function", "for", "package", "procedure", "private", "while", "when",
        "new", "entry", "delay", "case", "constant", "at", "abort", "accept",
        "and", "delta", "access", "abs", "pragma", "array", "use", "out", "do",
        "others", "of", "or", "all", "limited", "loop", "null", "task", "in",
        "is", "if", "rem", "mod", "begin", "body", "xor", "goto", "generic",
        "with",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 94 == hash.word_map.rbegin()->first );
}

TEST_CASE( "adadefs" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "boolean", "character", "constraint_error", "false", "float", "integer",
        "natural", "numeric_error", "positive", "program_error", "storage_error",
        "string", "tasking_error", "true", "address", "aft", "base", "callable",
        "constrained", "count", "delta", "digits", "emax", "epsilon", "first",
        "firstbit", "fore", "image", "large", "last", "lastbit", "length",
        "machine_emax", "machine_emin", "machine_mantissa", "machine_overflows",
        "machine_radix", "machine_rounds", "mantissa", "pos", "position", "pred",
        "range", "safe_emax", "safe_large", "safe_small", "size", "small",
        "storage_size", "succ", "terminated", "val", "value", "width",
    } );

    CHECK( 4 == hash.word_map.begin()->first );
    CHECK( 83 == hash.word_map.rbegin()->first );
}

TEST_CASE( "c++" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "asm", "auto", "break", "case", "catch", "char", "class", "const", "continue",
        "default", "delete", "do", "double", "else", "enum", "extern", "float", "for",
        "friend", "goto", "if", "inline", "int", "long", "new", "operator", "overload",
        "private", "protected", "public", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "template", "this", "typedef", "union",
        "unsigned", "virtual", "void", "volatile", "while",
    } );

    CHECK( 2 == hash.word_map.begin()->first );
    CHECK( 51 == hash.word_map.rbegin()->first );
}

TEST_CASE( "c-parse" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "@class", "@compatibility_alias", "@defs", "@encode", "@end", "@implementation",
        "@interface", "@private", "@protected", "@protocol", "@public", "@selector",
        "__alignof", "__alignof__", "__asm", "__asm__", "__attribute", "__attribute__",
        "__complex", "__complex__", "__const", "__const__", "__extension__", "__imag",
        "__imag__", "__inline", "__inline__", "__iterator", "__iterator__", "__label__",
        "__real", "__real__", "__restrict", "__restrict__", "__signed", "__signed__",
        "__typeof", "__typeof__", "__volatile", "__volatile__", "asm", "auto", "break",
        "bycopy", "byref", "case", "char", "const", "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for", "goto", "id", "if", "in", "inout",
        "inline", "int", "long", "oneway", "out", "register", "restrict", "return",
        "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "typeof",
        "union", "unsigned", "void", "volatile", "while",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 100 == hash.word_map.rbegin()->first );
}

TEST_CASE( "c" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "if", "do", "int", "for", "case", "char", "auto", "goto", "else", "long", "void",
        "enum", "float", "short", "union", "break", "while", "const", "double", "static",
        "extern", "struct", "return", "sizeof", "switch", "signed", "typedef", "default",
        "unsigned", "continue", "register", "volatile",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 34 == hash.word_map.rbegin()->first );
}

TEST_CASE( "charsets" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "437", "850", "851", "852", "855", "857", "860", "861", "862", "863", "865", "866",
        "869", "904", "adobe-standard-encoding", "adobe-symbol-encoding", "ansi_x3.110-1983",
        "ansi_x3.4-1968", "ansi_x3.4-1986", "arabic", "arabic7", "ascii", "asmo-708",
        "asmo_449", "big5", "big5-hkscs", "bs_4730", "bs_viewdata", "ca", "ccsid00858",
        "ccsid00924", "ccsid01140", "ccsid01141", "ccsid01142", "ccsid01143", "ccsid01144",
        "ccsid01145", "ccsid01146", "ccsid01147", "ccsid01148", "ccsid01149", "cesu-8",
        "chinese", "cn", "cp-ar", "cp-gr", "cp-is", "cp00858", "cp00924", "cp01140",
        "cp01141", "cp01142", "cp01143", "cp01144", "cp01145", "cp01146", "cp01147",
        "cp01148", "cp01149", "cp037", "cp038", "cp1026", "cp273", "cp274", "cp275", "cp278",
        "cp280", "cp281", "cp284", "cp285", "cp290", "cp297", "cp367", "cp420", "cp423",
        "cp424", "cp437", "cp500", "cp775", "cp819", "cp850", "cp851", "cp852", "cp855",
        "cp857", "cp860", "cp861", "cp862", "cp863", "cp864", "cp865", "cp866", "cp868",
        "cp869", "cp870", "cp871", "cp880", "cp891", "cp903", "cp904", "cp905", "cp918",
        "cp936", "csa7-1", "csa7-2", "csa_t500-1983", "csa_z243.4-1985-1", "csa_z243.4-1985-2",
        "csa_z243.4-1985-gr", "csadobestandardencoding", "csascii", "csbig5", "cscesu-8",
        "csdecmcs", "csdkus", "csebcdicatdea", "csebcdiccafr", "csebcdicdkno", "csebcdicdknoa",
        "csebcdices", "csebcdicesa", "csebcdicess", "csebcdicfise", "csebcdicfisea", "csebcdicfr",
        "csebcdicit", "csebcdicpt", "csebcdicuk", "csebcdicus", "cseucfixwidjapanese", "cseuckr",
        "cseucpkdfmtjapanese", "csgb2312", "cshalfwidthkatakana", "cshpdesktop", "cshplegal",
        "cshpmath8", "cshppifont", "cshppsmath", "cshproman8", "csibbm904", "csibm037",
        "csibm038", "csibm1026", "csibm273", "csibm274", "csibm275", "csibm277", "csibm278",
        "csibm280", "csibm281", "csibm284", "csibm285", "csibm290", "csibm297", "csibm420",
        "csibm423", "csibm424", "csibm500", "csibm851", "csibm855", "csibm857", "csibm860",
        "csibm861", "csibm863", "csibm864", "csibm865", "csibm866", "csibm868", "csibm869",
        "csibm870", "csibm871", "csibm880", "csibm891", "csibm903", "csibm905", "csibm918",
        "csibmebcdicatde", "csibmsymbols", "csibmthai", "csinvariant", "csiso102t617bit",
        "csiso10367box", "csiso103t618bit", "csiso10646utf1", "csiso10swedish",
        "csiso111ecmacyrillic", "csiso11swedishfornames", "csiso121canadian1",
        "csiso122canadian2", "csiso123csaz24341985gr", "csiso128t101g2",
        "csiso139csn369103", "csiso13jisc6220jp", "csiso141jusib1002", "csiso143iecp271",
        "csiso146serbian", "csiso147macedonian", "csiso14jisc6220ro", "csiso150",
        "csiso150greekccitt", "csiso151cuba", "csiso153gost1976874", "csiso158lap",
        "csiso159jisx02121990", "csiso15italian", "csiso16portuguese", "csiso17spanish",
        "csiso18greek7old", "csiso19latingreek", "csiso2022jp", "csiso2022jp2",
        "csiso2022kr", "csiso2033", "csiso21german", "csiso25french", "csiso27latingreek1",
        "csiso2intlrefversion", "csiso42jisc62261978", "csiso47bsviewdata",
        "csiso49inis", "csiso4unitedkingdom", "csiso50inis8", "csiso51iniscyrillic",
        "csiso5427cyrillic", "csiso5428greek", "csiso57gb1988", "csiso58gb231280",
        "csiso60danishnorwegian", "csiso60norwegian1", "csiso61norwegian2",
        "csiso646basic1983", "csiso646danish", "csiso6937add", "csiso69french",
        "csiso70videotexsupp1", "csiso84portuguese2", "csiso85spanish2",
        "csiso86hungarian", "csiso87jisx0208", "csiso88596e", "csiso88596i",
        "csiso88598e", "csiso88598i", "csiso8859supp", "csiso88greek7", "csiso89asmo449",
        "csiso90", "csiso91jisc62291984a", "csiso92jisc62991984b", "csiso93jis62291984badd",
        "csiso94jis62291984hand", "csiso95jis62291984handadd", "csiso96jisc62291984kana",
        "csiso99naplps", "csisolatin1", "csisolatin2", "csisolatin3", "csisolatin4",
        "csisolatin5", "csisolatin6", "csisolatinarabic", "csisolatincyrillic",
        "csisolatingreek", "csisolatinhebrew", "csisotextcomm", "csjisencoding",
        "cskoi8r", "csksc56011987", "csksc5636", "csmacintosh", "csmicrosoftpublishing",
        "csmnem", "csmnemonic", "csn_369103", "csnatsdano", "csnatsdanoadd",
        "csnatssefi", "csnatssefiadd", "cspc775baltic", "cspc850multilingual",
        "cspc862latinhebrew", "cspc8codepage437", "cspc8danishnorwegian",
        "cspc8turkish", "cspcp852", "csshiftjis", "csucs4", "csunicode",
        "csunicode11", "csunicode11utf7", "csunicodeascii", "csunicodeibm1261",
        "csunicodeibm1264", "csunicodeibm1265", "csunicodeibm1268", "csunicodeibm1276",
        "csunicodelatin1", "csunknown8bit", "csusdk", "csventurainternational",
        "csventuramath", "csventuraus", "csviqr", "csviscii", "cswindows30latin1",
        "cswindows31j", "cswindows31latin1", "cswindows31latin2", "cswindows31latin5",
        "cuba", "cyrillic", "de", "dec", "dec-mcs", "din_66003", "dk", "dk-us",
        "ds2089", "ds_2089", "e13b", "ebcdic-at-de", "ebcdic-at-de-a", "ebcdic-be",
        "ebcdic-br", "ebcdic-ca-fr", "ebcdic-cp-ar1", "ebcdic-cp-ar2", "ebcdic-cp-be",
        "ebcdic-cp-ca", "ebcdic-cp-ch", "ebcdic-cp-dk", "ebcdic-cp-es", "ebcdic-cp-fi",
        "ebcdic-cp-fr", "ebcdic-cp-gb", "ebcdic-cp-gr", "ebcdic-cp-he", "ebcdic-cp-is",
        "ebcdic-cp-it", "ebcdic-cp-nl", "ebcdic-cp-no", "ebcdic-cp-roece",
        "ebcdic-cp-se", "ebcdic-cp-tr", "ebcdic-cp-us", "ebcdic-cp-wt", "ebcdic-cp-yu",
        "ebcdic-cyrillic", "ebcdic-de-273+euro", "ebcdic-dk-277+euro", "ebcdic-dk-no",
        "ebcdic-dk-no-a", "ebcdic-es", "ebcdic-es-284+euro", "ebcdic-es-a",
        "ebcdic-es-s", "ebcdic-fi-278+euro", "ebcdic-fi-se", "ebcdic-fi-se-a",
        "ebcdic-fr", "ebcdic-fr-297+euro", "ebcdic-gb-285+euro", "ebcdic-int",
        "ebcdic-international-500+euro", "ebcdic-is-871+euro", "ebcdic-it",
        "ebcdic-it-280+euro", "ebcdic-jp-e", "ebcdic-jp-kana", "ebcdic-latin9--euro",
        "ebcdic-no-277+euro", "ebcdic-pt", "ebcdic-se-278+euro", "ebcdic-uk",
        "ebcdic-us", "ebcdic-us-37+euro", "ecma-114", "ecma-118", "ecma-cyrillic",
        "elot_928", "es", "es2", "euc-jp", "euc-kr", "extended_unix_code_fixed_width_for_japanese",
        "extended_unix_code_packed_format_for_japanese", "fi", "fr", "gb",
        "gb18030", "gb2312", "gb_1988-80", "gb_2312-80", "gbk", "gost_19768-74",
        "greek", "greek-ccitt", "greek7", "greek7-old", "greek8", "hebrew",
        "hp-desktop", "hp-legal", "hp-math8", "hp-pi-font", "hp-roman8",
        "hu", "hz-gb-2312", "ibm-symbols", "ibm-thai", "ibm00858", "ibm00924",
        "ibm01140", "ibm01141", "ibm01142", "ibm01143", "ibm01144", "ibm01145",
        "ibm01146", "ibm01147", "ibm01148", "ibm01149", "ibm037", "ibm038",
        "ibm1026", "ibm273", "ibm274", "ibm275", "ibm277", "ibm278", "ibm280",
        "ibm281", "ibm284", "ibm285", "ibm290", "ibm297", "ibm367", "ibm420",
        "ibm423", "ibm424", "ibm437", "ibm500", "ibm775", "ibm819", "ibm850",
        "ibm851", "ibm852", "ibm855", "ibm857", "ibm860", "ibm861", "ibm862",
        "ibm863", "ibm864", "ibm865", "ibm866", "ibm868", "ibm869", "ibm870",
        "ibm871", "ibm880", "ibm891", "ibm903", "ibm904", "ibm905", "ibm918",
        "iec_p27-1", "inis", "inis-8", "inis-cyrillic", "invariant", "irv",
        "iso-10646", "iso-10646-j-1", "iso-10646-ucs-2", "iso-10646-ucs-4",
        "iso-10646-ucs-basic", "iso-10646-unicode-latin1", "iso-10646-utf-1",
        "iso-2022-cn", "iso-2022-cn-ext", "iso-2022-jp", "iso-2022-jp-2",
        "iso-2022-kr", "iso-8859-1", "iso-8859-1-windows-3.0-latin-1", "iso-8859-1-windows-3.1-latin-1",
        "iso-8859-10", "iso-8859-13", "iso-8859-14", "iso-8859-15", "iso-8859-16",
        "iso-8859-2", "iso-8859-2-windows-latin-2", "iso-8859-3", "iso-8859-4",
        "iso-8859-5", "iso-8859-6", "iso-8859-6-e", "iso-8859-6-i", "iso-8859-7",
        "iso-8859-8", "iso-8859-8-e", "iso-8859-8-i", "iso-8859-9", "iso-8859-9-windows-latin-5",
        "iso-celtic", "iso-ir-10", "iso-ir-100", "iso-ir-101", "iso-ir-102",
        "iso-ir-103", "iso-ir-109", "iso-ir-11", "iso-ir-110", "iso-ir-111",
        "iso-ir-121", "iso-ir-122", "iso-ir-123", "iso-ir-126", "iso-ir-127",
        "iso-ir-128", "iso-ir-13", "iso-ir-138", "iso-ir-139", "iso-ir-14",
        "iso-ir-141", "iso-ir-142", "iso-ir-143", "iso-ir-144", "iso-ir-146",
        "iso-ir-147", "iso-ir-148", "iso-ir-149", "iso-ir-15", "iso-ir-150",
        "iso-ir-151", "iso-ir-152", "iso-ir-153", "iso-ir-154", "iso-ir-155",
        "iso-ir-157", "iso-ir-158", "iso-ir-159", "iso-ir-16", "iso-ir-17",
        "iso-ir-18", "iso-ir-19", "iso-ir-199", "iso-ir-2", "iso-ir-21",
        "iso-ir-25", "iso-ir-27", "iso-ir-37", "iso-ir-4", "iso-ir-42", "iso-ir-47",
        "iso-ir-49", "iso-ir-50", "iso-ir-51", "iso-ir-54", "iso-ir-55",
        "iso-ir-57", "iso-ir-58", "iso-ir-6", "iso-ir-60", "iso-ir-61", "iso-ir-69",
        "iso-ir-70", "iso-ir-8-1", "iso-ir-8-2", "iso-ir-84", "iso-ir-85",
        "iso-ir-86", "iso-ir-87", "iso-ir-88", "iso-ir-89", "iso-ir-9-1",
        "iso-ir-9-2", "iso-ir-90", "iso-ir-91", "iso-ir-92", "iso-ir-93",
        "iso-ir-94", "iso-ir-95", "iso-ir-96", "iso-ir-98", "iso-ir-99",
        "iso-unicode-ibm-1261", "iso-unicode-ibm-1264", "iso-unicode-ibm-1265",
        "iso-unicode-ibm-1268", "iso-unicode-ibm-1276", "iso5427cyrillic1981",
        "iso646-ca", "iso646-ca2", "iso646-cn", "iso646-cu", "iso646-de",
        "iso646-dk", "iso646-es", "iso646-es2", "iso646-fi", "iso646-fr",
        "iso646-fr1", "iso646-gb", "iso646-hu", "iso646-it", "iso646-jp",
        "iso646-jp-ocr-b", "iso646-kr", "iso646-no", "iso646-no2", "iso646-pt",
        "iso646-pt2", "iso646-se", "iso646-se2", "iso646-us", "iso646-yu",
        "iso_10367-box", "iso_2033-1983", "iso_5427", "iso_5427:1981", "iso_5428:1980",
        "iso_646.basic:1983", "iso_646.irv:1983", "iso_646.irv:1991", "iso_6937-2-25",
        "iso_6937-2-add", "iso_8859-1", "iso_8859-10:1992", "iso_8859-14",
        "iso_8859-14:1998", "iso_8859-15", "iso_8859-1:1987", "iso_8859-2",
        "iso_8859-2:1987", "iso_8859-3", "iso_8859-3:1988", "iso_8859-4",
        "iso_8859-4:1988", "iso_8859-5", "iso_8859-5:1988", "iso_8859-6",
        "iso_8859-6-e", "iso_8859-6-i", "iso_8859-6:1987", "iso_8859-7",
        "iso_8859-7:1987", "iso_8859-8", "iso_8859-8-e", "iso_8859-8-i",
        "iso_8859-8:1988", "iso_8859-9", "iso_8859-9:1989", "iso_8859-supp",
        "iso_9036", "it", "jis_c6220-1969", "jis_c6220-1969-jp", "jis_c6220-1969-ro",
        "jis_c6226-1978", "jis_c6226-1983", "jis_c6229-1984-a", "jis_c6229-1984-b",
        "jis_c6229-1984-b-add", "jis_c6229-1984-hand", "jis_c6229-1984-hand-add",
        "jis_c6229-1984-kana", "jis_encoding", "jis_x0201", "jis_x0208-1983",
        "jis_x0212-1990", "jp", "jp-ocr-a", "jp-ocr-b", "jp-ocr-b-add", "jp-ocr-hand",
        "jp-ocr-hand-add", "js", "jus_i.b1.002", "jus_i.b1.003-mac", "jus_i.b1.003-serb",
        "katakana", "koi8-r", "koi8-u", "korean", "ks_c_5601-1987", "ks_c_5601-1989",
        "ksc5636", "ksc_5601", "l1", "l2", "l3", "l4", "l5", "l6", "l8",
        "lap", "latin-greek", "latin-greek-1", "latin-lap", "latin1", "latin1-2-5",
        "latin2", "latin3", "latin4", "latin5", "latin6", "latin8", "mac",
        "macedonian", "macintosh", "microsoft-publishing", "mnem", "mnemonic",
        "ms936", "ms_kanji", "msz_7795.3", "naplps", "nats-dano", "nats-dano-add",
        "nats-sefi", "nats-sefi-add", "nc_nc00-10:81", "nf_z_62-010", "nf_z_62-010_(1973)",
        "no", "no2", "ns_4551-1", "ns_4551-2", "pc-multilingual-850+euro",
        "pc8-danish-norwegian", "pc8-turkish", "pt", "pt2", "r8", "ref",
        "roman8", "scsu", "se", "se2", "sen_850200_b", "sen_850200_c", "serbian",
        "shift_jis", "st_sev_358-88", "t.101-g2", "t.61", "t.61-7bit", "t.61-8bit",
        "tis-620", "uk", "unicode-1-1", "unicode-1-1-utf-7", "unknown-8bit",
        "us", "us-ascii", "us-dk", "utf-16", "utf-16be", "utf-16le", "utf-32",
        "utf-32be", "utf-32le", "utf-7", "utf-8", "ventura-international",
        "ventura-math", "ventura-us", "videotex-suppl", "viqr", "viscii",
        "windows-1250", "windows-1251", "windows-1252", "windows-1253", "windows-1254",
        "windows-1255", "windows-1256", "windows-1257", "windows-1258", "windows-31j",
        "windows-936", "x0201", "x0201-7", "x0208", "x0212", "yu",
    } );

    CHECK( 30 == hash.word_map.begin()->first );
    CHECK( 4603 == hash.word_map.rbegin()->first );
}

TEST_CASE( "chill" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "access", "after", "all", "all_static_off", "all_static_on", "and",
        "andif", "array", "asm", "assert", "at", "based", "begin", "bin",
        "bit", "body", "bools", "buffer", "buffer_code", "by", "call", "case",
        "cause", "ccitt_os", "chars", "context", "continue", "cycle", "dcl",
        "debug_lines", "debug_symbols", "debug_types", "delay", "do", "down",
        "dynamic", "else", "elsif", "empty_off", "empty_on", "end", "esac",
        "even", "event", "event_code", "ever", "exceptions", "exit", "extra_const_seg",
        "far", "fi", "for", "forbid", "general", "generate_all_set_names",
        "generate_set_names", "goto", "grant", "grant_file_size", "if", "in",
        "init", "inline", "inout", "large", "list", "loc", "make_publics_for_discrete_syns",
        "medium", "mod", "module", "multiple_const_segs", "multiple_data_segs",
        "newmode", "nolist", "no_overlap_check", "nonref", "nopack", "not",
        "od", "of", "on", "only_for_simulation", "only_for_target", "optimize",
        "optimize_runtime", "optimization_window", "or", "orif", "out", "pack",
        "page", "pos", "powerset", "prefixed", "print_o_code", "print_symbol_table",
        "priority", "proc", "process", "process_type", "range", "range_off",
        "range_on", "read", "receive", "recursive", "reentrant", "reentrant_all",
        "ref", "region", "rem", "remote", "result", "return", "returns",
        "row", "seize", "send", "send_buffer_default_priority", "send_signal_default_priority",
        "set", "short_pred_succ", "signal", "signal_code", "signal_max_length",
        "simple", "small", "spec", "start", "state_routine", "static", "step",
        "stop", "struct", "support_causing_address", "syn", "synmode", "text",
        "then", "this", "timeout", "to", "up", "use_seize_file", "use_seize_file_restricted",
        "varying", "while", "with", "xor", "ACCESS", "AFTER", "ALL", "ALL_STATIC_OFF",
        "ALL_STATIC_ON", "AND", "ANDIF", "ARRAY", "ASM", "ASSERT", "AT",
        "BASED", "BEGIN", "BIN", "BIT", "BODY", "BOOLS", "BUFFER", "BUFFER_CODE",
        "BY", "CALL", "CASE", "CAUSE", "CCITT_OS", "CHARS", "CONTEXT", "CONTINUE",
        "CYCLE", "DCL", "DEBUG_LINES", "DEBUG_SYMBOLS", "DEBUG_TYPES", "DELAY",
        "DO", "DOWN", "DYNAMIC", "ELSE", "ELSIF", "EMPTY_OFF", "EMPTY_ON",
        "END", "ESAC", "EVEN", "EVENT", "EVENT_CODE", "EVER", "EXCEPTIONS",
        "EXIT", "EXTRA_CONST_SEG", "FAR", "FI", "FOR", "FORBID", "GENERAL",
        "GENERATE_ALL_SET_NAMES", "GENERATE_SET_NAMES", "GOTO", "GRANT",
        "GRANT_FILE_SIZE", "IF", "IN", "INIT", "INLINE", "INOUT", "LARGE",
        "LIST", "LOC", "MAKE_PUBLICS_FOR_DISCRETE_SYNS", "MEDIUM", "MOD",
        "MODULE", "MULTIPLE_CONST_SEGS", "MULTIPLE_DATA_SEGS", "NEWMODE",
        "NOLIST", "NO_OVERLAP_CHECK", "NONREF", "NOPACK", "NOT", "OD", "OF",
        "ON", "ONLY_FOR_SIMULATION", "ONLY_FOR_TARGET", "OPTIMIZE", "OPTIMIZE_RUNTIME",
        "OPTIMIZATION_WINDOW", "OR", "ORIF", "OUT", "PACK", "PAGE", "POS",
        "POWERSET", "PREFIXED", "PRINT_O_CODE", "PRINT_SYMBOL_TABLE", "PRIORITY",
        "PROC", "PROCESS", "PROCESS_TYPE", "RANGE", "RANGE_OFF", "RANGE_ON",
        "READ", "RECEIVE", "RECURSIVE", "REENTRANT", "REENTRANT_ALL", "REF",
        "REGION", "REM", "REMOTE", "RESULT", "RETURN", "RETURNS", "ROW",
        "SEIZE", "SEND", "SEND_BUFFER_DEFAULT_PRIORITY", "SEND_SIGNAL_DEFAULT_PRIORITY",
        "SET", "SHORT_PRED_SUCC", "SIGNAL", "SIGNAL_CODE", "SIGNAL_MAX_LENGTH",
        "SIMPLE", "SMALL", "SPEC", "START", "STATE_ROUTINE", "STATIC", "STEP",
        "STOP", "STRUCT", "SUPPORT_CAUSING_ADDRESS", "SYN", "SYNMODE", "TEXT",
        "THEN", "THIS", "TIMEOUT", "TO", "UP", "USE_SEIZE_FILE", "USE_SEIZE_FILE_RESTRICTED",
        "VARYING", "WHILE", "WITH", "XOR",
    } );

    CHECK( 2 == hash.word_map.begin()->first );
    CHECK( 623 == hash.word_map.rbegin()->first );
}

TEST_CASE( "cplusplus" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "__alignof", "__alignof__", "__asm", "__asm__", "__attribute", "__attribute__",
        "__complex", "__complex__", "__const", "__const__", "__extension__",
        "__imag", "__imag__", "__inline", "__inline__", "__label__", "__null",
        "__real", "__real__", "__restrict", "__restrict__", "__signature__",
        "__signed", "__signed__", "__sigof__", "__typeof", "__typeof__",
        "__volatile", "__volatile__", "__wchar_t", "asm", "and", "and_eq",
        "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char",
        "class", "compl", "const", "const_cast", "continue", "default",
        "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit",
        "export", "extern", "false", "float", "for", "friend", "goto", "if",
        "inline", "int", "long", "mutable", "namespace", "new", "not", "not_eq",
        "operator", "or", "or_eq", "private", "protected", "public", "register",
        "reinterpret_cast", "return", "short", "signature", "signed", "sigof",
        "sizeof", "static", "static_cast", "struct", "switch", "template",
        "this", "throw", "true", "try", "typedef", "typename", "typeid",
        "typeof", "union", "unsigned", "using", "virtual", "void", "volatile",
        "while", "xor", "xor_eq",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 190 == hash.word_map.rbegin()->first );
}

TEST_CASE( "gpc" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "And", "Array", "Begin", "Case", "Const", "Div", "Do", "Downto",
        "Else", "End", "File", "For", "Function", "Goto", "If", "In", "Label",
        "Mod", "Nil", "Not", "Of", "Or", "Packed", "Procedure", "Program",
        "Record", "Repeat", "Set", "Then", "To", "Type", "Until", "Var",
        "While", "With",
    } );

    CHECK( 2 == hash.word_map.begin()->first );
    CHECK( 37 == hash.word_map.rbegin()->first );
}

TEST_CASE( "incomplete" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "january", "february", "march", "april", "may", "june", "july",
        "august", "september", "october", "november", "december",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 14 == hash.word_map.rbegin()->first );
}

TEST_CASE( "irc" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "NICK", "MSG", "PRIVMSG", "WHO", "WHOIS", "USER", "SERVER", "LIST",
        "TOPIC", "INVITE", "CHANNEL", "VERSION", "QUIT", "SQUIT", "KILL",
        "INFO", "LINKS", "SUMMON", "STATS", "USERS", "RESTART", "WHOREPLY",
        "HELP", "ERROR", "AWAY", "DIE", "CONNECT", "PING", "PONG", "OPER",
        "PASS", "WALL", "TIME", "REHASH", "NAMES", "NAMREPLY", "ADMIN",
        "TRACE", "LINREPLY", "NOTICE", "LUSERS", "VOICE", "GRPH", "XTRA",
        "MOTD",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 53 == hash.word_map.rbegin()->first );
}

TEST_CASE( "java" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "abstract", "default", "if", "private", "throw", "boolean", "do",
        "implements", "protected", "throws", "break", "double", "import",
        "public", "transient", "byte", "else", "instanceof", "return", "try",
        "case", "extends", "int", "short", "void", "catch", "final", "interface",
        "static", "volatile", "char", "finally", "long", "super", "while",
        "class", "float", "native", "switch", "const", "for", "new", "synchronized",
        "continue", "goto", "package", "this", "true", "false", "null",
    } );

    CHECK( 2 == hash.word_map.begin()->first );
    CHECK( 58 == hash.word_map.rbegin()->first );
}

TEST_CASE( "jscript" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "abstract", "boolean", "break", "byte", "case", "catch", "char",
        "class", "const", "continue", "default", "do", "double", "else",
        "extends", "false", "final", "finally", "float", "for", "function",
        "goto", "if", "implements", "import", "in", "instanceof", "int",
        "interface", "long", "native", "new", "null", "package", "private",
        "protected", "public", "return", "short", "static", "super", "switch",
        "synchronized", "this", "throw", "throws", "transient", "true",
        "try", "var", "void", "while", "with",
    } );

    CHECK( 4 == hash.word_map.begin()->first );
    CHECK( 68 == hash.word_map.rbegin()->first );
}

TEST_CASE( "lang-utf8" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "አማርኛ", "česky", "Dansk", "English", "Suomi", "Français", "Deutsch",
        "Ελληνικά", "Italiano", "Norsk", "Русский", "Español", "Svenska",
        "ภาษาไทย", "Türkçe", "Tiếng Việt", "日本語", "中文", "한글",
    } );

    CHECK( 5 == hash.word_map.begin()->first );
    CHECK( 23 == hash.word_map.rbegin()->first );
}

TEST_CASE( "languages" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "cel-gaulish", "uig", "ton", "rm", "pt", "mri", "ilo", "hrv", "i-navajo",
        "tg", "rn", "kom", "i-tao", "de-at-1901", "vai", "th", "ro", "mag",
        "kon", "nld", "ces", "afh", "aus", "sgn-pt", "ti", "sux", "mah",
        "hau", "ce", "mai", "gmh", "am", "sgn-be-nl", "tk", "haw", "zen",
        "tl", "oss", "mak", "kor", "ch", "mal", "lez", "kos", "ira", "zh-xiang",
        "tn", "ru", "lim", "ful", "dak", "umb", "tsi", "to", "man", "lin",
        "ar", "bos", "wln", "vi", "mao", "kua", "rw", "ipk", "as", "aym",
        "syr", "shn", "goh", "dan", "map", "i-tay", "tr", "sla", "ell",
        "afr", "bua", "ts", "pol", "mar", "ga", "co", "i-ami", "tsn", "tt",
        "mas", "ita", "her", "fur", "eng", "cmc", "tso", "pon", "lit", "sgn-co",
        "de-1901", "xh", "vo", "gd", "za", "ay", "sgn-gb", "yor", "tw",
        "mga", "el", "gon", "az", "cs", "alb", "ukr", "tuk", "raj", "bug",
        "sgn-za", "ty", "sna", "por", "en", "tum", "nno", "may", "eo", "enm",
        "cv", "ale", "ven", "iro", "gor", "slk", "snd", "kum", "ice", "hil",
        "gba", "alg", "day", "cy", "twi", "tup", "men", "id", "him", "got",
        "del", "zh", "bul", "rap", "ie", "hin", "gl", "elx", "es", "zh-yue",
        "xho", "tur", "den", "et", "vie", "tha", "slo", "rar", "mic", "gn",
        "eu", "spa", "sgn-ie", "sgn-es", "kur", "ka", "tut", "oji", "lol",
        "kha", "snk", "kut", "epo", "ang", "bur", "ik", "hit", "apa", "nah",
        "wak", "nai", "deu", "sgn-gr", "wal", "slv", "gu", "de-ch-1996",
        "gv", "mkd", "io", "guj", "cop", "ki", "zu", "srd", "kj", "khi",
        "jrb", "dzo", "dgr", "cor", "zh-min", "min", "kk", "ara", "cos",
        "mkh", "lua", "kl", "is", "hmn", "war", "nap", "lub", "km", "it",
        "hmo", "arc", "din", "was", "sad", "mg", "khm", "kn", "iu", "gwi",
        "de-de-1996", "pus", "mh", "ko", "jpn", "sgn-it", "mis", "mi", "loz",
        "kho", "i-hak", "tyv", "sag", "oc", "sah", "bla", "nau", "mk", "lug",
        "bho", "sai", "nav", "ml", "ks", "jpr", "scc", "lui", "zh-min-nan",
        "wel", "mn", "ku", "div", "tli", "srp", "sal", "mo", "kv", "no-nyn",
        "wen", "sam", "phi", "arm", "kw", "srr", "san", "fra", "arn", "mr",
        "lun", "ky", "ava", "ath", "zh-guoyu", "i-enochian", "nia", "moh",
        "ms", "luo", "ace", "arp", "om", "nep", "mt", "vol", "phn", "nic",
        "fre", "sgn-ch-de", "ota", "sas", "sa", "que", "ach", "ave", "doi",
        "no-bok", "sat", "ori", "nzi", "mol", "lus", "art", "sc", "gla",
        "sd", "sco", "roa", "or", "mon", "sga", "cus", "my", "aar", "cha",
        "os", "se", "msa", "chb", "arw", "ba", "sgn-mx", "i-klingon", "zul",
        "orm", "new", "kpe", "jav", "de-ch-1901", "sg", "gle", "eka", "scr",
        "sgn-se", "zun", "vot", "tpi", "sel", "frm", "che", "si", "sem",
        "pli", "mos", "glg", "be", "fro", "chg", "sk", "roh", "bra", "bg",
        "cym", "sl", "iku", "hun", "bh", "chi", "da", "sm", "oci", "kaa",
        "fan", "bi", "zha", "de-de-1901", "ug", "sid", "sn", "qu", "kab",
        "hup", "fao", "dua", "chk", "wa", "so", "oto", "kac", "aze", "bre",
        "rom", "chm", "de", "bnt", "i-tsu", "sgn", "ron", "egy", "sq", "chn",
        "hye", "zh-hakka", "uk", "tah", "sr", "fas", "niu", "bad", "cho",
        "bn", "sgn-de", "bo", "tai", "ss", "fa", "fat", "chp", "st", "fry",
        "nob", "su", "chr", "sv", "pra", "br", "aka", "i-default", "ypk",
        "tam", "sw", "mul", "kro", "bs", "bai", "und", "sin", "glv", "kal",
        "iba", "sgn-dk", "sgn-br", "ur", "sma", "sio", "mun", "kam", "grb",
        "bak", "chv", "paa", "kan", "ha", "grc", "dum", "mya", "bal", "fi",
        "bam", "zho", "wol", "gre", "gaa", "fj", "btk", "ban", "chy", "sgn-us",
        "wo", "sme", "kru", "yi", "tat", "sit", "kar", "he", "mus", "kas",
        "isl", "baq", "tvl", "pag", "non", "kat", "akk", "i-mingo", "en-scouse",
        "uz", "smi", "mdr", "kau", "ja", "fo", "dut", "bas", "smj", "hi",
        "bat", "kaw", "yo", "tel", "pro", "nor", "mwr", "fr", "amh", "znd",
        "tem", "rum", "pal", "grn", "fij", "dz", "yao", "urd", "sog", "run",
        "pam", "kaz", "smn", "ibo", "bej", "sgn-fr", "i-pwn", "yap", "smo",
        "pan", "myn", "tib", "la", "ho", "bel", "zh-gan", "pap", "nub",
        "lb", "fin", "bem", "art-lojban", "ter", "tgk", "ben", "tgl", "sms",
        "rus", "fy", "hr", "cre", "tet", "som", "lad", "tig", "son", "ido",
        "pau", "ssa", "hu", "ber", "cad", "nso", "na", "sqi", "de-at-1996",
        "nbl", "nde", "li", "lah", "fiu", "dyu", "nb", "nd", "mlg", "bih",
        "hy", "sgn-jp", "sot", "ne", "hz", "kik", "gay", "ng", "mnc", "ln",
        "lam", "ewe", "bik", "peo", "pa", "lo", "kin", "jv", "gem", "est",
        "crp", "nya", "yid", "lao", "sgn-be-fr", "tir", "kmb", "geo", "bin",
        "i-lux", "tkl", "per", "zh-wuu", "sgn-ni", "ndo", "kir", "nl", "ceb",
        "mni", "lt", "ger", "i-bnn", "uga", "tiv", "tmh", "swa", "nn", "lat",
        "eus", "car", "sgn-nl", "osa", "no", "lv", "efi", "bis", "ada",
        "de-1996", "pi", "lav", "nds", "fon", "asm", "cat", "suk", "mlt",
        "ile", "ewo", "cau", "sgn-no", "uzb", "swe", "nr", "hai", "awa",
        "abk", "pl", "mno", "aa", "tog", "sun", "nym", "ijo", "ab", "zap",
        "bod", "nyn", "gil", "gez", "dra", "ta", "ssw", "nyo", "nv", "inc",
        "afa", "cel", "ltz", "ind", "ae", "ast", "ine", "af", "sus", "mac",
        "heb", "ny", "cze", "te", "ps", "mad", "kok", "ca",
    } );

    CHECK( 9 == hash.word_map.begin()->first );
    CHECK( 3189 == hash.word_map.rbegin()->first );
}

TEST_CASE( "makeinfo" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "!", "'", "*", ".", ":", "?", "@", "TeX", "`", "appendix", "appendixsec",
        "appendixsubsec", "asis", "b", "br", "bullet", "bye", "c", "center",
        "chapter", "cindex", "cite", "code", "comment", "contents", "copyright",
        "ctrl", "defcodeindex", "defindex", "dfn", "display", "dots", "emph",
        "end", "enumerate", "equiv", "error", "example", "exdent", "expansion",
        "file", "findex", "format", "group", "i", "iappendix", "iappendixsec",
        "iappendixsubsec", "ichapter", "ifinfo", "iftex", "ignore", "include",
        "inforef", "input", "isection", "isubsection", "isubsubsection",
        "item", "itemize", "itemx", "iunnumbered", "iunnumberedsec", "iunnumberedsubsec",
        "kbd", "key", "kindex", "lisp", "menu", "minus", "need", "node",
        "noindent", "page", "pindex", "point", "print", "printindex", "pxref",
        "quotation", "r", "ref", "refill", "result", "samp", "sc", "section",
        "setchapternewpage", "setfilename", "settitle", "smallexample",
        "sp", "strong", "subsection", "subsubsection", "summarycontents",
        "syncodeindex", "synindex", "t", "table", "tex", "tindex", "titlepage",
        "unnumbered", "unnumberedsec", "unnumberedsubsec", "var", "vindex",
        "w", "xref", "{", "}", "infoinclude", "footnote",
    } );

    CHECK( 1 == hash.word_map.begin()->first );
    CHECK( 190 == hash.word_map.rbegin()->first );
}

TEST_CASE( "modula3" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "AND", "ARRAY", "BEGIN", "BITS", "BY", "CASE", "CONST", "DIV", "DO",
        "ELSE", "ELSIF", "END", "EVAL", "EXCEPT", "EXCEPTION", "EXIT", "EXPORTS",
        "FINALLY", "FOR", "FROM", "IF", "IMPORT", "INTERFACE", "IN", "INLINE",
        "LOCK", "METHODS", "MOD", "MODULE", "NOT", "OBJECT", "OF", "OR",
        "PROCEDURE", "RAISES", "READONLY", "RECORD", "REF", "REPEAT", "RETURN",
        "SET", "THEN", "TO", "TRY", "TYPE", "TYPECASE", "UNSAFE", "UNTIL",
        "UNTRACED", "VALUE", "VAR", "WHILE", "WITH", "and", "array", "begin",
        "bits", "by", "case", "const", "div", "do", "else", "elsif", "end",
        "eval", "except", "exception", "exit", "exports", "finally", "for",
        "from", "if", "import", "interface", "in", "inline", "lock", "methods",
        "mod", "module", "not", "object", "of", "or", "procedure", "raises",
        "readonly", "record", "ref", "repeat", "return", "set", "then",
        "to", "try", "type", "typecase", "unsafe", "until", "untraced",
        "value", "var", "while", "with",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 113 == hash.word_map.rbegin()->first );
}

TEST_CASE( "objc" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "@defs", "@encode", "@end", "@implementation", "@interface", "@public",
        "@selector", "__alignof", "__alignof__", "__asm", "__asm__", "__attribute",
        "__attribute__", "__const", "__const__", "__extension__", "__inline",
        "__inline__", "__signed", "__signed__", "__typeof", "__typeof__",
        "__volatile", "__volatile__", "asm", "auto", "break", "case", "char",
        "const", "continue", "default", "do", "double", "else", "enum",
        "extern", "float", "for", "goto", "if", "inline", "int", "long",
        "register", "return", "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "typeof", "union", "unsigned", "void", "volatile",
        "while",
    } );

    CHECK( 2 == hash.word_map.begin()->first );
    CHECK( 61 == hash.word_map.rbegin()->first );
}

TEST_CASE( "pascal" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "with", "array", "and", "function", "case", "var", "const", "until",
        "then", "set", "record", "program", "procedure", "or", "packed",
        "not", "nil", "label", "in", "repeat", "of", "goto", "forward",
        "for", "while", "file", "else", "downto", "do", "div", "to", "type",
        "end", "mod", "begin", "if",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 40 == hash.word_map.rbegin()->first );
}

TEST_CASE( "permut2" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "xy", "yx", "xz", "zx",
    } );

    CHECK( 2 == hash.word_map.begin()->first );
    CHECK( 5 == hash.word_map.rbegin()->first );
}

TEST_CASE( "permut3" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "abc", "acb", "bca", "cab",
    } );

    CHECK( 3 == hash.word_map.begin()->first );
    CHECK( 6 == hash.word_map.rbegin()->first );
}

TEST_CASE( "permutc2" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "az", "za", "ay", "ya", "x{", "x[", "{w", "[w",
    } );

    CHECK( 2 == hash.word_map.begin()->first );
    CHECK( 9 == hash.word_map.rbegin()->first );
}

TEST_CASE( "smtp" )
{
    PerfectHash hash = GeneratePerfectHash( {
        "Accept-Language", "Action", "Alternate-Recipient", "Approved",
        "Archive", "Arrival-Date", "Autoforwarded", "Autosubmitted", "Bcc",
        "Cc", "Comments", "Complaints-To", "Content-alternative", "Content-Base",
        "Content-Description", "Content-Disposition", "Content-Duration",
        "Content-Features", "Content-ID", "Content-Language", "Content-Location",
        "Content-MD5", "Content-Transfer-Encoding", "Content-Type", "Control",
        "Conversion", "Conversion-With-Loss", "DL-Expansion-History", "DSN-Gateway",
        "Date", "Deferred-Delivery", "Delivery-Date", "Diagnostic-Code",
        "Discarded-X400-IPMS-Extensions", "Discarded-X400-MTS-Extensions",
        "Disclose-Recipients", "Disposition", "Disposition-Notification-Options",
        "Disposition-Notification-To", "Distribution", "Encrypted", "Error",
        "Expires", "Failure", "Final-Log-ID", "Final-Recipient", "Followup-To",
        "From", "Generate-Delivery-Report", "Importance", "In-Reply-To",
        "Incomplete-Copy", "Injector-Info", "Keywords", "Last-Attempt-Date",
        "Latest-Delivery-Time", "Lines", "List-Archive", "List-Help", "List-ID",
        "List-Post", "List-Owner", "List-Subscribe", "List-Unsubscribe",
        "MDN-Gateway", "Media-Accept-Features", "MIME-Version", "Mail-Copies-To",
        "Message-ID", "Message-Type", "Newsgroups", "Organization", "Original-Encoded-Information-Types",
        "Original-Envelope-ID", "Original-Message-ID", "Original-Recipient",
        "Originator-Return-Address", "Path", "Posted-And-Mailed", "Prevent-Nondelivery-Report",
        "Priority", "Received", "Received-content-MIC", "Received-From-MTA",
        "References", "Remote-MTA", "Reply-By", "Reply-To", "Reporting-MTA",
        "Reporting-UA", "Return-Path", "Sender", "Sensitivity", "Status",
        "Subject", "Summary", "Supersedes", "To", "User-Agent", "Warning",
        "Will-Retry-Until", "X400-Content-Identifier", "X400-Content-Return",
        "X400-Content-Type", "X400-MTS-Identifier", "X400-Originator", "X400-Received",
        "X400-Recipients", "Xref",
    } );

    CHECK( 8 == hash.word_map.begin()->first );
    CHECK( 161 == hash.word_map.rbegin()->first );
}
