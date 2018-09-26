import sys
import os
import argparse

parser = argparse.ArgumentParser(description='Throughput Calculation for a application.')
parser.add_argument('inFile', type=str)
parser.add_argument('outFileBytes', type=str)
parser.add_argument('outFilePackets', type=str)
parser.add_argument('--startTime', type=float, default=0)
parser.add_argument('--packetSize', type=float, default=1500)
parser.add_argument('--destPort', type=int)
parser.add_argument('--destIp', type=str)
parser.add_argument('flowLabel', type=str)
args = parser.parse_args()

file_name      = args.inFile
outFileBytes   = args.outFileBytes
outFilePackets = args.outFilePackets
startTime      = args.startTime
packetSize     = args.packetSize
destIp         = args.destIp
flowLabel      = args.flowLabel
destPort       = args.destPort

if not os.path.exists(os.path.dirname(outFileBytes)):
    try:
        os.makedirs(os.path.dirname(outFileBytes))
    except OSError as exc: # Guard against race condition
        if exc.errno != errno.EEXIST:
            raise

if not os.path.exists(os.path.dirname(outFilePackets)):
    try:
        os.makedirs(os.path.dirname(outFilePackets))
    except OSError as exc: # Guard against race condition
        if exc.errno != errno.EEXIST:
            raise

os.system ("tshark -r " + file_name +" -T fields -e frame.time_relative -e frame.len -e ip.dst -e tcp.dstport > " + file_name[0:file_name.rindex('.')] + ".csv")
fBytes         = open (outFileBytes, 'w')
fPackets       = open (outFilePackets, 'w')
p              = startTime
old_time       = startTime
new_time       = 0
val            = 0
valPacket      = 0
totalval       = 0
totalvalPacket = 0

with open(file_name[0:file_name.rindex('.')] + '.csv') as fq:
    fp = fq.readlines()
    for line in fp:
        if (destIp == None or str(line.split('\t')[2]).strip () == destIp) and float(line.split('\t')[1]) == packetSize and float(line.split('\t')[0]) >= startTime and (destPort == None or destPort == int (line.split('\t')[3].strip ())):
            new_time = float(line.split('\t')[0])
            val += float(line.split('\t')[1])
            totalval += float(line.split('\t')[1])
            valPacket += 1
            totalvalPacket += 1
            if (new_time - old_time > 0.1):
                val = val/(new_time - old_time)
                valPacket = valPacket/(new_time - old_time)
                fBytes.write(str(p) + " " + str(val * 8.0/(1000.0 * 1000.0 * 1000.0)) + "\n")
                fPackets.write(str(p) + " " + str(valPacket) + "\n")
                p += (new_time - old_time)
                old_time = new_time
                val = 0
                valPacket = 0

    print flowLabel + ' In Gbps: ' + str(totalval * 8.0/(1000.0 * 1000.0 * 1000.0)/(new_time - startTime)) + ' In Packets: ' + str(totalvalPacket/(new_time - startTime))
fBytes.close()
fPackets.close()
os.remove(file_name[0:file_name.rindex('.')] + '.csv')
