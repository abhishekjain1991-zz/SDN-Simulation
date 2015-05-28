
from pox.core import core
import pox.openflow.libopenflow_01 as of
from pox.lib.util import dpidToStr


log=core.getLogger()


s1_dpid=0
s2_dpid=0
s3_dpid=0
s4_dpid=0
s5_dpid=0
s6_dpid=0
s7_dpid=0

def _handle_ConnectionUp(event):
    global s1_dpid, s2_dpid, s3_dpid, s4_dpid,s5_dpid, s6_dpid, s7_dpid
    print "ConnectionUp: ", dpidToStr(event.connection.dpid)

#remember the connection dpid for switch
    for m in event.connection.features.ports:
        if m.name == "s1":
            s1_dpid=event.connection.dpid
            print "s1_dpid: ", s1_dpid
        elif m.name == "s2":
            s2_dpid=event.connection.dpid
            print "s2_dpid: ", s2_dpid
        elif m.name == "s3":
            s3_dpid=event.connection.dpid
            print "s3_dpid: ", s3_dpid
        elif m.name == "s4":
            s4_dpid=event.connection.dpid
            print "s4_dpid: ", s4_dpid
        elif m.name == "s5":
            s5_dpid=event.connection.dpid
            print "s5_dpid: ", s5_dpid
        elif m.name == "s6":
            s6_dpid=event.connection.dpid
            print "s6_dpid: ", s6_dpid
        elif m.name == "s7":
            s7_dpid=event.connection.dpid
            print "s6_dpid: ", s7_dpid


def _handle_PacketIn(event):
    global s1_dpid, s2_dpid, s3_dpid, s4_dpid,s5_dpid, s6_dpid, s7_dpid
    
    if event.connection.dpid==s1_dpid:
        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
	msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.tp_dst=8000
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=2))
        event.connection.send(msg1)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=6
        msg.match.tp_src=8000
        msg.match.in_port=2
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
	msg.match.dl_type=0x0800
        msg.match.nw_proto=17
        msg.match.in_port=1
        msg.actions.append(of.ofp_action_output(port=3))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=17
        msg.match.in_port=3
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
	msg.match.dl_type=0x0800
        msg.match.nw_proto=1
        msg.match.in_port=1
        msg.actions.append(of.ofp_action_output(port=4))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=1
        msg.match.in_port=4
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.tp_dst=21
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=5))
        event.connection.send(msg1)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=6
        msg.match.in_port=5
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)


        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=6))
        event.connection.send(msg1)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=6
        msg.match.in_port=6
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)


        
       
    elif event.connection.dpid==s2_dpid:
        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
	msg1.match.nw_proto=6
        msg1.match.tp_src=8000
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=2))
        event.connection.send(msg1)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=6
        msg.match.in_port=2
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
	msg.match.dl_type=0x0800
        msg.match.nw_proto=17
        msg.match.in_port=1
        msg.actions.append(of.ofp_action_output(port=3))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=17
        msg.match.in_port=3
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
	msg.match.dl_type=0x0800
        msg.match.nw_proto=1
        msg.match.in_port=1
        msg.actions.append(of.ofp_action_output(port=4))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=1
        msg.match.in_port=4
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.tp_src=21
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=5))
        event.connection.send(msg1)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=6
        msg.match.in_port=5
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)


        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=6))
        event.connection.send(msg1)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
        msg.match.nw_proto=6
        msg.match.in_port=6
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

    elif event.connection.dpid==s3_dpid:
        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
	msg1.match.dl_type=0x0800
	msg1.match.nw_proto=6
        msg1.match.tp_dst=8000
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=2))
        event.connection.send(msg1)

        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
	msg1.match.dl_type=0x0800
	msg1.match.nw_proto=6
        msg1.match.tp_src=8000
        msg1.match.in_port=2
        msg1.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg1)


    elif event.connection.dpid==s4_dpid:
        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
	msg.match.dl_type=0x0800
        msg.match.nw_proto=17
        msg.match.in_port=1
        msg.actions.append(of.ofp_action_output(port=2))
        event.connection.send(msg)

        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
	msg.match.dl_type=0x0800
        msg.match.nw_proto=17
        msg.match.in_port=2
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

    elif event.connection.dpid==s5_dpid:
        msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
	msg.match.dl_type=0x0800
        msg.match.nw_proto=1
        msg.match.in_port=2
        msg.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg)

	msg=of.ofp_flow_mod()
        msg.priority=1
        msg.idle_timeout=0
        msg.hard_timeout=0
	msg.match.dl_type=0x0800
        msg.match.nw_proto=1
        msg.match.in_port=1
        msg.actions.append(of.ofp_action_output(port=2))
        event.connection.send(msg)

    elif event.connection.dpid==s6_dpid:
        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.tp_dst=21
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=2))
        event.connection.send(msg1)

        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.tp_src=21
        msg1.match.in_port=2
        msg1.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg1)


    elif event.connection.dpid==s7_dpid:
        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.in_port=1
        msg1.actions.append(of.ofp_action_output(port=2))
        event.connection.send(msg1)

        msg1=of.ofp_flow_mod()
        msg1.priority=1
        msg1.idle_timeout=0
        msg1.hard_timeout=0
        msg1.match.dl_type=0x0800
        msg1.match.nw_proto=6
        msg1.match.in_port=2
        msg1.actions.append(of.ofp_action_output(port=1))
        event.connection.send(msg1)

def launch():
    core.openflow.addListenerByName("ConnectionUp", _handle_ConnectionUp)
    core.openflow.addListenerByName("PacketIn", _handle_PacketIn)
