# -*- Makefile -*-
# $Id$

# Copyright (C) 2002-2010 Alexander Chernov <cher@ejudge.ru> */

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

USERLIST_CLNT_CFILES=\
 userlist_clnt/admin_process.c\
 userlist_clnt/bytes_available.c\
 userlist_clnt/change_registration.c\
 userlist_clnt/close.c\
 userlist_clnt/cnts_passwd_op.c\
 userlist_clnt/control.c\
 userlist_clnt/copy_user_info.c\
 userlist_clnt/create_member.c\
 userlist_clnt/create_user.c\
 userlist_clnt/delete_cookie.c\
 userlist_clnt/delete_field.c\
 userlist_clnt/delete_info.c\
 userlist_clnt/do_pass_fd.c\
 userlist_clnt/dump_database.c\
 userlist_clnt/edit_field.c\
 userlist_clnt/edit_field_seq.c\
 userlist_clnt/generate_team_passwd.c\
 userlist_clnt/get_contests.c\
 userlist_clnt/get_cookie.c\
 userlist_clnt/get_database.c\
 userlist_clnt/get_fd.c\
 userlist_clnt/get_info.c\
 userlist_clnt/get_param.c\
 userlist_clnt/get_uid_by_pid.c\
 userlist_clnt/get_uid_by_pid_2.c\
 userlist_clnt/get_xml_by_text.c\
 userlist_clnt/import_csv_users.c\
 userlist_clnt/list_all_users.c\
 userlist_clnt/list_users.c\
 userlist_clnt/login.c\
 userlist_clnt/logout.c\
 userlist_clnt/lookup_cookie.c\
 userlist_clnt/lookup_user.c\
 userlist_clnt/lookup_user_id.c\
 userlist_clnt/map_contest.c\
 userlist_clnt/move_member.c\
 userlist_clnt/notify.c\
 userlist_clnt/open.c\
 userlist_clnt/pass_fd.c\
 userlist_clnt/priv_cookie.c\
 userlist_clnt/priv_cookie_login.c\
 userlist_clnt/priv_login.c\
 userlist_clnt/read_and_notify.c\
 userlist_clnt/read_notification.c\
 userlist_clnt/recover_passwd_2.c\
 userlist_clnt/recv_packet.c\
 userlist_clnt/register_contest.c\
 userlist_clnt/register_new.c\
 userlist_clnt/register_new_2.c\
 userlist_clnt/send_packet.c\
 userlist_clnt/set_cookie.c\
 userlist_clnt/set_info.c\
 userlist_clnt/set_notification_callback.c\
 userlist_clnt/set_passwd.c\
 userlist_clnt/team_cookie.c

SUPER_CLNT_CFILES=\
 super_clnt/control.c\
 super_clnt/create_contest.c\
 super_clnt/do_pass_fd.c\
 super_clnt/http_request.c\
 super_clnt/main_page.c\
 super_clnt/open.c\
 super_clnt/pass_fd.c\
 super_clnt/recv_packet.c\
 super_clnt/send_packet.c\
 super_clnt/set_param.c\
 super_clnt/simple_cmd.c

NEW_SERVER_CLNT_CFILES=\
 new_server_clnt/close.c\
 new_server_clnt/control.c\
 new_server_clnt/http_request.c\
 new_server_clnt/open.c\
 new_server_clnt/pass_fd.c\
 new_server_clnt/recv_packet.c\
 new_server_clnt/send_packet.c

COMMON_CFILES=\
 allowed_list.c\
 archive_paths.c\
 base64.c\
 cgi.c\
 charsets.c\
 clarlog.c\
 cldb_plugin_file.c\
 clntutil.c\
 common_plugin.c\
 compile_packet_1.c\
 compile_packet_2.c\
 compile_packet_3.c\
 compile_packet_4.c\
 compile_packet_5.c\
 compile_packet_6.c\
 contests.c\
 contests_2.c\
 contest_tmpl.c\
 copyright.c\
 csv.c\
 diff.c\
 digest_1.c\
 digest_2.c\
 digest_3.c\
 digest_4.c\
 digest_5.c\
 dos2unix_str.c\
 ejudge_cfg.c\
 errlog.c\
 expat_iface.c\
 filehash.c\
 filter_eval.c\
 filter_tree.c\
 html.c\
 html_checkbox.c\
 html_date_select.c\
 html_input_password.c\
 html_input_text.c\
 html_hidden.c\
 html_hyperref.c\
 html_start_form.c\
 l10n.c\
 lang_config.c\
 lang_config_vis.c\
 master_html.c\
 meta_generic.c\
 mime_type.c\
 misctext.c\
 ncheck_packet.c\
 new_server_html.c\
 new_server_html_2.c\
 new_server_html_3.c\
 new_server_html_4.c\
 new_server_html_5.c\
 new_server_proto.c\
 new_server_tables.c\
 ncurses_utils.c\
 nsdb_plugin_files.c\
 nwrun_packet.c\
 opcaps.c\
 opcaps_2.c\
 parsecfg.c\
 parsecfg_2.c\
 pathutl.c\
 plugin.c\
 prepare.c\
 prepare_out.c\
 prepare_serve.c\
 printing.c\
 problem_common.c\
 problem_xml.c\
 protocol.c\
 random.c\
 reports.c\
 rldb_plugin_file.c\
 run_inverse.c\
 runlog.c\
 runlog_import.c\
 runlog_static.c\
 runlog_xml.c\
 run_packet_1.c\
 run_packet_2.c\
 run_packet_3.c\
 run_packet_4.c\
 run_packet_5.c\
 run_packet_6.c\
 run_packet_7.c\
 send_job_packet.c\
 server_framework.c\
 serve_2.c\
 serve_state.c\
 sformat.c\
 shellcfg_parse.c\
 stringset.c\
 super_html.c\
 super_html_2.c\
 super_html_3.c\
 super_html_4.c\
 super_html_5.c\
 super_proto.c\
 sha.c\
 t3m_dir_listener.c\
 t3m_zip_packet_class.c\
 t3_packets.c\
 teamdb.c\
 teamdb_2.c\
 team_extra.c\
 team_extra_xml.c\
 testinfo.c\
 testing_report_xml.c\
 tex_dom.c\
 tex_dom_parse.c\
 tex_dom_doc.c\
 tex_dom_render.c\
 tsc.c\
 uldb_plugin_xml.c\
 userlist.c\
 userlist_check.c\
 userlist_proto.c\
 userlist_xml.c\
 varsubst.c\
 vcs.c\
 watched_file.c\
 xml_utils/attr_bool.c\
 xml_utils/attr_bool_byte.c\
 xml_utils/attr_date.c\
 xml_utils/attr_int.c\
 xml_utils/elem_ip_mask.c\
 xml_utils/empty_text.c\
 xml_utils/err_attrs.c\
 xml_utils/err_attr_invalid.c\
 xml_utils/err_attr_not_allowed.c\
 xml_utils/err_attr_undefined.c\
 xml_utils/err_attr_undefined_s.c\
 xml_utils/err_elem_empty.c\
 xml_utils/err_elem_invalid.c\
 xml_utils/err_elem_not_allowed.c\
 xml_utils/err_elem_redefined.c\
 xml_utils/err_elem_undefined.c\
 xml_utils/err_elem_undefined_s.c\
 xml_utils/err_get_attr_name.c\
 xml_utils/err_get_elem_name.c\
 xml_utils/err_nested_elems.c\
 xml_utils/err_top_level.c\
 xml_utils/err_top_level_s.c\
 xml_utils/err_variables.c\
 xml_utils/leaf_elem.c\
 xml_utils/parse_bool.c\
 xml_utils/parse_date.c\
 xml_utils/parse_int.c\
 xml_utils/parse_ip.c\
 xml_utils/parse_ip_mask.c\
 xml_utils/unparse_bool.c\
 xml_utils/unparse_date.c\
 xml_utils/unparse_ip.c\
 xml_utils/unparse_ip_mask.c\
 xml_utils/unparse_run_status.c\
 xml_utils/unparse_text.c\
 xml_utils/xml_err.c\
 xml_utils/xml_err_a.c

CFILES=\
 clean-users.c\
 collect-emails.c\
 compile.c\
 compile-control.c\
 convert-clars.c\
 convert-runs.c\
 edit-userlist.c\
 ej-ncheck.c\
 ej-t3-mediator.c\
 ejudge-configure-compilers.c\
 ejudge-control.c\
 ejudge-setup.c\
 execute.c\
 fix-db.c\
 job-server.c\
 job-server-control.c\
 job-server-cmd.c\
 make-js-actions.c\
 new-client.c\
 new-server.c\
 new-server-cmd.c\
 new-server-control.c\
 nwrun.c\
 run.c\
 serve.c\
 serve-control.c\
 slice-userlist.c\
 struct-sizes.c\
 super-serve.c\
 super-serve-control.c\
 testinfo.c\
 userlist-server.c\
 userlist-server-control.c\
 users.c\
 unix/cpu.c\
 win32/cpu.c\
 unix/file_perms.c\
 win32/file_perms.c\
 unix/fileutl.c\
 win32/fileutl.c\
 unix/cr_serialize.c\
 win32/cr_serialize.c\
 unix/ej_process.c\
 win32/ej_process.c\
 unix/interrupt.c\
 win32/interrupt.c\
 unix/curtime.c\
 win32/curtime.c\
 unix/fmemopen.c\
 win32/fmemopen.c\
 unix/open_memstream.c\
 win32/open_memstream.c\
 unix/timestamp.c\
 win32/timestamp.c\
 unix/full_archive.c\
 win32/full_archive.c\
 unix/sock_op_enable_creds.c\
 win32/sock_op_enable_creds.c\
 unix/sock_op_get_creds.c\
 win32/sock_op_get_creds.c\
 unix/sock_op_get_fds.c\
 win32/sock_op_get_fds.c\
 unix/sock_op_put_fds.c\
 win32/sock_op_put_fds.c\
 unix/sock_op_put_creds.c\
 win32/sock_op_put_creds.c\
 unix/startstop.c\
 win32/startstop.c\
 ${COMMON_CFILES}\
 ${SUPER_CLNT_CFILES}\
 ${USERLIST_CLNT_CFILES}\
 ${NEW_SERVER_CLNT_CFILES}

HFILES=\
 archive_paths.h\
 base64.h\
 cgi.h\
 charsets.h\
 clarlog.h\
 clarlog_state.h\
 cldb_plugin.h\
 client_actions.h\
 clntutil.h\
 common_plugin.h\
 compat.h\
 compile_packet.h\
 compile_packet_priv.h\
 contests.h\
 copyright.h\
 cpu.h\
 cr_serialize.h\
 csv.h\
 curtime.h\
 diff.h\
 digest_io.h\
 ejudge_cfg.h\
 ejudge_plugin.h\
 ej_limits.h\
 ej_process.h\
 ej_types.h\
 errlog.h\
 expat_iface.h\
 filehash.h\
 file_perms.h\
 fileutl.h\
 filter_eval.h\
 filter_tree.h\
 full_archive.h\
 html.h\
 interrupt.h\
 iterators.h\
 job_packet.h\
 l10n.h\
 lang_config_vis.h\
 list_ops.h\
 meta_generic.h\
 mime_type.h\
 mischtml.h\
 misctext.h\
 ncheck_packet.h\
 ncurses_utils.h\
 new-server.h\
 nsdb_plugin.h\
 nwrun_packet.h\
 opcaps.h\
 parsecfg.h\
 pathutl.h\
 prepare.h\
 prepare_dflt.h\
 prepare_serve.h\
 printing.h\
 problem_common.h\
 problem_xml.h\
 protocol.h\
 random.h\
 rldb_plugin.h\
 run.h\
 runlog.h\
 runlog_state.h\
 run_packet.h\
 run_packet_priv.h\
 server_framework.h\
 serve_state.h\
 sformat.h\
 shellcfg_parse.h\
 sock_op.h\
 startstop.h\
 stringset.h\
 super_clnt.h\
 super_html.h\
 super_proto.h\
 super-serve.h\
 sha.h\
 t3m_dir_listener.h\
 t3m_packet_class.h\
 t3_packets.h\
 teamdb.h\
 teamdb_priv.h\
 team_extra.h\
 testinfo.h\
 testing_report_xml.h\
 tex_dom.h\
 timestamp.h\
 tsc.h\
 uldb_plugin.h\
 userlist.h\
 userlist_clnt.h\
 varsubst.h\
 vcs.h\
 version.h\
 watched_file.h\
 win32_compat.h\
 unix/unix_fileutl.h\
 userlist_clnt/private.h\
 new_server_clnt.h\
 new_server_proto.h\
 new_server_clnt/new_server_clnt_priv.h\
 xml_utils.h

OTHERFILES=\
 filter_expr.y\
 filter_scan.lex\
 plugins/mysql-userlist/uldb_mysql.c
