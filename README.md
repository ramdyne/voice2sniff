# Voice2Sniff

Way back in 2000 I was doing my final internship at (what was then) Philips Business Communications in Hilversum. I was asked to write H.323 support for (what was then called) Ethereal.

In the end I produced four "works"
- A report
- Code to parse ASN.1 source files and create C++ code in a C wrapper so an Ethereal plugin (for Windows) could be built from it
- A working plugin for the ITU H.323 suite of protocols
- A new implementation of the RTP dissector to be inlcuded in Ethereal

For a while this plugin was the only freely available H.323 decoder/dissector that actually worked. Microsoft had a product at the time that was able to decode some H.323, but it never supported the full suite and wasn't able to decode newer versions of the protocol. I've never had the opportunity to see this for myself, but I have hard from developers at other VoIP related companies the decoding was even superior to most of the commercial implementations at the time.

Because of license incompatabilities (related to the choice of ASN.1 decoder generator) this plugin was never going to be able to be released by the Ethereal project. So for a while H.323 support was in a kind of limbo when I moved to a different company and I had very little time to keep this code up to date. Fortunately someone took my ideas and implemented a proper ASN.1 -> Ethereal code generator and that code is still in Wireshark.

As I mentioned before I also re-implemented RTP (and RTCP) decoding to be able to be used with what was I planning for the plugin. This code is still in Wireshark and from what I can find it my code has never been source of a Wireshark vulnerability.

This repo contains all the sourcecode for as many work products I could find. The plugin code can also be found at Sourceforge, but since I have no idea how long that site will continue to exist I am going to make this the colloquial source.
