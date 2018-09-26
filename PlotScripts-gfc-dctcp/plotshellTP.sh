#Usage startTime
printf "Flow Throughput\n\n" | tee -a overallTP.txt


python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50000 N-63-0.pcap plotmeTP/TP-S10.plotme plotmeTPP/TP-S10.plotme S1-0 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50001 N-63-0.pcap plotmeTP/TP-S11.plotme plotmeTPP/TP-S11.plotme S1-1 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50002 N-63-0.pcap plotmeTP/TP-S12.plotme plotmeTPP/TP-S12.plotme S1-2 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50003 N-63-0.pcap plotmeTP/TP-S13.plotme plotmeTPP/TP-S13.plotme S1-3 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50004 N-63-0.pcap plotmeTP/TP-S14.plotme plotmeTPP/TP-S14.plotme S1-4 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50005 N-63-0.pcap plotmeTP/TP-S15.plotme plotmeTPP/TP-S15.plotme S1-5 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50006 N-63-0.pcap plotmeTP/TP-S16.plotme plotmeTPP/TP-S16.plotme S1-6 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50007 N-63-0.pcap plotmeTP/TP-S17.plotme plotmeTPP/TP-S17.plotme S1-7 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50008 N-63-0.pcap plotmeTP/TP-S18.plotme plotmeTPP/TP-S18.plotme S1-8 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50009 N-63-0.pcap plotmeTP/TP-S19.plotme plotmeTPP/TP-S19.plotme S1-9 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50010 N-63-0.pcap plotmeTP/TP-S30.plotme plotmeTPP/TP-S30.plotme S3-0 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50011 N-63-0.pcap plotmeTP/TP-S31.plotme plotmeTPP/TP-S31.plotme S3-1 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50012 N-63-0.pcap plotmeTP/TP-S32.plotme plotmeTPP/TP-S32.plotme S3-2 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50013 N-63-0.pcap plotmeTP/TP-S33.plotme plotmeTPP/TP-S33.plotme S3-3 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50014 N-63-0.pcap plotmeTP/TP-S34.plotme plotmeTPP/TP-S34.plotme S3-4 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50015 N-63-0.pcap plotmeTP/TP-S35.plotme plotmeTPP/TP-S35.plotme S3-5 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50016 N-63-0.pcap plotmeTP/TP-S36.plotme plotmeTPP/TP-S36.plotme S3-6 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50017 N-63-0.pcap plotmeTP/TP-S37.plotme plotmeTPP/TP-S37.plotme S3-7 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50018 N-63-0.pcap plotmeTP/TP-S38.plotme plotmeTPP/TP-S38.plotme S3-8 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.4.0.1 --destPort 50019 N-63-0.pcap plotmeTP/TP-S39.plotme plotmeTPP/TP-S39.plotme S3-9 | tee -a overallTP.txt

python tp-new.py --startTime=3 --destIp 10.5.1.1 N-43-0.pcap plotmeTP/TP-S20.plotme plotmeTPP/TP-S20.plotme S2-0 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.2.1 N-44-0.pcap plotmeTP/TP-S21.plotme plotmeTPP/TP-S21.plotme S2-1 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.3.1 N-45-0.pcap plotmeTP/TP-S22.plotme plotmeTPP/TP-S22.plotme S2-2 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.4.1 N-46-0.pcap plotmeTP/TP-S23.plotme plotmeTPP/TP-S23.plotme S2-3 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.5.1 N-47-0.pcap plotmeTP/TP-S24.plotme plotmeTPP/TP-S24.plotme S2-4 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.6.1 N-48-0.pcap plotmeTP/TP-S25.plotme plotmeTPP/TP-S25.plotme S2-5 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.7.1 N-49-0.pcap plotmeTP/TP-S26.plotme plotmeTPP/TP-S26.plotme S2-6 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.8.1 N-50-0.pcap plotmeTP/TP-S27.plotme plotmeTPP/TP-S27.plotme S2-7 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.9.1 N-51-0.pcap plotmeTP/TP-S28.plotme plotmeTPP/TP-S28.plotme S2-8 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.10.1 N-52-0.pcap plotmeTP/TP-S29.plotme plotmeTPP/TP-S29.plotme S2-9 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.11.1 N-53-0.pcap plotmeTP/TP-S210.plotme plotmeTPP/TP-S210.plotme S2-10 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.12.1 N-54-0.pcap plotmeTP/TP-S211.plotme plotmeTPP/TP-S211.plotme S2-11 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.13.1 N-55-0.pcap plotmeTP/TP-S212.plotme plotmeTPP/TP-S212.plotme S2-12 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.14.1 N-56-0.pcap plotmeTP/TP-S213.plotme plotmeTPP/TP-S213.plotme S2-13 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.15.1 N-57-0.pcap plotmeTP/TP-S214.plotme plotmeTPP/TP-S214.plotme S2-14 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.16.1 N-58-0.pcap plotmeTP/TP-S215.plotme plotmeTPP/TP-S215.plotme S2-15 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.17.1 N-59-0.pcap plotmeTP/TP-S216.plotme plotmeTPP/TP-S216.plotme S2-16 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.18.1 N-60-0.pcap plotmeTP/TP-S217.plotme plotmeTPP/TP-S217.plotme S2-17 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.19.1 N-61-0.pcap plotmeTP/TP-S218.plotme plotmeTPP/TP-S218.plotme S2-18 | tee -a overallTP.txt
python tp-new.py --startTime=3 --destIp 10.5.20.1 N-62-0.pcap plotmeTP/TP-S219.plotme plotmeTPP/TP-S219.plotme S2-19 | tee -a overallTP.txt



cp gnuplotscript plotmeTP
cp perflowgnuplot plotmeTP
cd plotmeTP
gnuplot gnuplotscript
gnuplot perflowgnuplot
cd ..

cp gnuplotscriptPackets plotmeTPP
cd plotmeTPP
gnuplot gnuplotscriptPackets
cd ..

printf "\nRouter Throughput\n\n" | tee -a overallTP.txt

python tp-new.py --startTime=3 N-0-0.pcap plotmeRouterTP/TP-T1.plotme plotmeRouterTPP/TP-T1.plotme T1 | tee -a overallTP.txt
python tp-new.py --startTime=3 N-2-1.pcap plotmeRouterTP/TP-Scorp.plotme plotmeRouterTPP/TP-Scorp.plotme Scorp | tee -a overallTP.txt
python tp-new.py --startTime=3 N-1-1.pcap plotmeRouterTP/TP-T2.plotme plotmeRouterTPP/TP-T2.plotme T2 | tee -a overallTP.txt

cp gnuplotscriptRouters plotmeRouterTP
cd plotmeRouterTP
gnuplot gnuplotscriptRouters
cd ..

cp gnuplotscriptRoutersPackets plotmeRouterTPP
cd plotmeRouterTPP
gnuplot gnuplotscriptRoutersPackets
cd ..


mkdir -p ../Graphs
cp plotmeRouterTP/*.png ../Graphs/
cp plotmeRouterTPP/*.png ../Graphs/
cp plotmeTP/*.png ../Graphs/
cp plotmeTPP/*.png ../Graphs/
cp overallTP.txt ../Graphs/

#Cwnd plot
cp gnuplotscriptQ ../
cp gnuplotscriptCwnd ../cwndTraces/
cp gnuplotscriptProb ../ProbTraces/

cd ../queueTraces/
echo "Queue 0" > QueueStatsAfteS2sec.txt
drops=`awk '{if ($1 >= 2) print $0}' drop-0.plotme | wc -l`
marks=`awk '{if ($1 >= 2) print $0}' mark-0.plotme | wc -l`
echo -e  "$drops Drops, $marks Marks\n" >> QueueStatsAfteS2sec.txt

echo "Queue 1" >> QueueStatsAfteS2sec.txt
drops=`awk '{if ($1 >= 2) print $0}' drop-1.plotme | wc -l`
marks=`awk '{if ($1 >= 2) print $0}' mark-1.plotme | wc -l`
echo -e  "$drops Drops, $marks Marks\n" >> QueueStatsAfteS2sec.txt

echo "Queue 2" >> QueueStatsAfteS2sec.txt
drops=`awk '{if ($1 >= 2) print $0}' drop-2.plotme | wc -l`
marks=`awk '{if ($1 >= 2) print $0}' mark-2.plotme | wc -l`
echo -e  "$drops Drops, $marks Marks\n" >> QueueStatsAfteS2sec.txt


cp QueueStatsAfteS2sec.txt ../Graphs/

cd ..
gnuplot gnuplotscriptQ
cp queue-*.png Graphs/
cp queueStats.txt Graphs/

cd cwndTraces
gnuplot gnuplotscriptCwnd
cp Cwnd*.png ../Graphs/

cd ..
cd ProbTraces
gnuplot gnuplotscriptProb
cp *.png ../Graphs/
