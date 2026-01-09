port = "/dev/cu.usbserial-0001";   % <-- change if yours differs
baud = 115200;

s = serialport(port, baud);
configureTerminator(s, "LF");      % Arduino println ends with \n
flush(s);

% Optional: give the ESP32 a moment after opening the port
pause(1);

% Data buffers
t0 = tic;
T = []; rawAvg=[]; dRaw=[]; filtCnt=[]; dV_uV=[]; dI_nA=[];

figure; h = plot(nan, nan); grid on;
xlabel("Time (s)"); ylabel("dI (nA)");
title("DIY Optical Power Meter (ADS1115) - Live");

disp("Logging... Press Ctrl+C to stop.");

while true
    line = readline(s);
    line = strtrim(line);

    % Skip non-data lines (headers, 'Zeroed ...', garbage)
    nums = sscanf(line, "%f");
    if numel(nums) ~= 5
        continue
    end

    T(end+1,1) = toc(t0);
    rawAvg(end+1,1) = nums(1);
    dRaw(end+1,1)   = nums(2);
    filtCnt(end+1,1)= nums(3);
    dV_uV(end+1,1)  = nums(4);
    dI_nA(end+1,1)  = nums(5);

    % Update plot
    set(h, "XData", T, "YData", dI_nA);
    drawnow limitrate
end