function tDist = processArgus_OpenField(files, inDir, outDir, vidDir, varargin)
    
    markerSize = 6;
    centerPerc = 0.33;
    
    xSquares = 3;       % Number of even sized regions across X axis (NOT CURRENTLY WORKING - DEFAULT IS 3)
    ySquares = 3;       % Number of even sized regions across Y axis (NOT CURRENTLY WORKING - DEFAULT IS 3)
    tSquares = xSquares * ySquares;
    
    slidingWin = 30;    % Currently in seconds
    timePrior = 10;     % Currently in seconds
    habitTime = 30;      % Currently in minutes
    behavTime = 30;     % Currently in minutes
    
    evenHabitSegments = 1;
    evenBehavSegments = 1;
    
    timeDirection = 1;     % If +1, go FWD, is -1, go BKWD
                            % ie, if -1 and behavTime is 20, then use last
                            % 20 mins of video for behavior and rest is
                            % habituation
                            % if +1, then takes habitTime from beginning
                            % followed by behavTime afterwards
                            
    makeVideo = false;
    
    makeHeatmaps = true;
    combineHeatmaps = true;    
    
    fps = 15;
    %xpix = 261;
    %ypix = 381;
    xdist = 48.25;
    ydist = 48.25;
    units = 'Centimeters';
    
    if ~exist('files', 'var') || isempty(files)
        %files = 'H:\Behavior Videos\GBAxGKI\8-25-2022\1172500.txt';
        files = 'H:\IFNg Behavior Videos\OpenField - 08-03-2022\Argus Results\1234647.txt';
        %files = 'C:\Users\HAL2\Desktop\FOR SARAH\Open Field\6-2-22\Argus Results\1152713_OF.txt';
    end
    %'H:\RME8-PFF\OF\Captures\12-20-21\OF\Argus Output\1104485.txt';
    
    possVargin = {'habitTime', 'behavTime', 'makeVideo', 'evenHabitSegments', 'evenBehavSegments'};
    
    for i = 1:2:length(varargin)
        userArg = varargin{i};
        switch userArg
            case possVargin{1}
                habitTime = varargin{i+1};
            case possVargin{2}
                behavTime = varargin{i+1};
            case possVargin{3}
                makeVideo = varargin{i+1};
            case possVargin{4}
                evenHabitSegments = varargin{i+1};
            case possVargin{5}
                evenBehavSegments = varargin{i+1};
            otherwise
                fprintf('ERROR: Invalid input, ignored\n');
        end
    end
                
    if ~exist('inDir', 'var') || isempty(inDir)
        %inDir = 'E:\Gene Data\Rat Behavior\Results\';
        inDir = 'H:\IFNg Behavior Videos\OpenField - 08-03-2022\Argus Results\';
    end
    if ~exist('outDir', 'var') || isempty(outDir)
        %outDir = 'E:\Gene Data\Rat Results\Argus-Results\';
        outDir = 'H:\IFNg Behavior Videos\OpenField - 08-03-2022\Argus Results\';
        %outDir = 'C:\Users\HAL2\Desktop\FOR SARAH\Open Field\6-2-22\Argus Results\Processed (25 Minutes Behavior)\';
        %'H:\RME8-PFF\OF\Captures\12-20-21\OF\Argus Output\Processed (15 Minutes Behavior)\';
    end
    if ~exist('vidDir', 'var') || isempty(vidDir)
        %vidDir = 'E:\Gene Data\Rat Behavior\Videos\Converted\';
        vidDir = 'H:\Behavior Videos\PLA\Open Field\8-16-22\';
    end
    if ~strcmpi(inDir(end), filesep)
        inDir(end+1) = filesep;
    end
    if ~strcmpi(outDir(end), filesep)
        outDir(end+1) = filesep;
    end
    
    if ~exist('files', 'var') || isempty(files)
        [fileIn, fileDir] = uigetfile(fullfile(inDir, '*.txt;'));
        files = [fileDir, fileIn];
        clear fileDir fileIn;
    end
    
    [~, dataName, ~] = fileparts(files);
    vidTemp = strsplit(dataName, '_');
    %vidName = [vidTemp{1}, '_', vidTemp{2}];
    %vidDir = [vidDir, vidName, filesep, vidName, '.avi'];
    
    %WIN_20220302_13_23_58_Pro.mp4
    %   1085834 (L) and 1085833 (R)
    %WIN_20220302_13_55_28_Pro.mp4
    %   1085844 (L) and 1085843 (R)
    %WIN_20220302_15_26_01_Pro.mp4
    %   1090544 (L) and 1090543 (R)
    %WIN_20220302_15_59_07_Pro.mp4
    %   1090545 (L) and 1068655 (R)
    %WIN_20220302_16_31_40_Pro.mp4
    %   1068650 (L) and 1068644 (R)
    %WIN_20220302_17_02_32_Pro.mp4
    %   1068651 (L) and 1085829 (R)
    %WIN_20220302_17_32_17_Pro.mp4
    %   1085830 (L) and 1085832 (R)
    %WIN_20220303_12_52_19_Pro.mp4
    %   1068664 (L) and 1068663 (R)
    %WIN_20220303_13_26_24_Pro.mp4
    %   1068666 (L) and 1068667 (R)
    
    %vidDir = [vidDir, 'WIN_20220816_10_36_28_Pro.mp4'];
    clear vidTemp vidName;
    
    %outDir = [outDir, dataName, filesep];
    %'E:\Gene Data\Rat Behavior\testMatlabVersion.avi';
        
    fid = fopen(files);
    if fid < 0
        fprintf('ERROR: Could not open selected Argus output file for analysis\n');
        fprintf([files, ' failed to load\n']);
        return;
    end
    
    liner = fgetl(fid);
    fileHead = liner;
    vals = 1;
    
    xpos = 1;
    ypos = 2;
    cdis = 3;
    tdis = 4;
    cvel = 5;
    fnum = 6;
    iseq = 7;
    
    allX = [];
    allY = [];
    frme = [];
    
    while ~feof(fid)
        liner = fgetl(fid);
        if ~isempty(liner) && ~strcmpi(liner(1), '#')
            if strcmpi(liner(1), 'ï')
                liner(1:3) = '';
            end
            lineSpl = strsplit(liner, ', ');
            if length(lineSpl) < 7
                allX(vals) = str2double(lineSpl{xpos});
                allY(vals) = str2double(lineSpl{ypos});
                ttf(vals) = str2double(lineSpl{fnum});
                vals = vals + 1;
            elseif str2double(lineSpl{iseq}) == 0
                allX(vals) = str2double(lineSpl{xpos});
                allY(vals) = str2double(lineSpl{ypos});
                ttf(vals) = str2double(lineSpl{fnum});
                eqFlag(vals) = str2double(lineSpl{iseq});
                vals = vals + 1;
            end
        elseif length(liner) > 10 && strcmpi(liner(1:10), '#X-Pixels:')
            xpix = str2double(liner(11:end));
        elseif length(liner) > 10 && strcmpi(liner(1:10), '#Y-Pixels:')
            ypix = str2double(liner(11:end));
        end
    end
    vals = vals - 1;
    fclose(fid);
    
    xTemp = nan([1, max(ttf)-min(ttf)+1]);
    yTemp = nan([1, max(ttf)-min(ttf)+1]);
    frme = [min(ttf):max(ttf)];
    for i = 1:length(ttf)
        xTemp(frme == ttf(i)) = allX(i);
        yTemp(frme == ttf(i)) = allY(i);
    end
    %xTemp(frme) = allX;
    %yTemp(frme(ttf)) = allY;
    xPts = fillmissing(xTemp, 'linear');
    yPts = fillmissing(yTemp, 'linear');
    %frme = [min(ttf):max(ttf)];
    vals = length(xPts);
    
    middLX = sqrt(centerPerc)*xpix;
    middLY = sqrt(centerPerc)*ypix;
    
    xZoneDiv = round(xpix / xSquares);
    yZoneDiv = round(ypix / ySquares);
    
    middX = [round((xpix - middLX)/2), round(((xpix - middLX)/2)+middLX)];
    middY = [round((ypix - middLY)/2), round(((ypix - middLY)/2)+middLY)];
        
    cmPerPixX = xdist / xpix;
    cmPerPixY = ydist / ypix;
    pixPerCmX = xpix / xdist;
    pixPerCmY = ypix / ydist;
    
    minX = 0;
    maxX = ceil(xpix/10) * 10;
    difX = round((maxX - xpix)/2);
    minY = 0;
    maxY = ceil(ypix/10) * 10;
    difY = round((maxY - ypix)/2);
    
    positionHab = zeros([maxX, maxY])';
    positionBeh = zeros([maxX, maxY])';
    %posData = zeros([1, vals]);
    tDist = zeros([1, vals]);
    velData = zeros([1, vals-1]);
    isMiddl = zeros([1, vals]);
    xZoner = zeros([1, vals]);
    yZoner = zeros([1, vals]);
    t1Shift = zeros([1, vals]);
    t2Shift = zeros([1, vals]);
    t3Shift = zeros([1, vals]);
    [x, y] = meshgrid(1:maxX, 1:maxY);
    
    if timeDirection == 1
        frameStr = min(frme);
        habitFrames = [frameStr, frameStr + habitTime*60*fps - 1];
        behavFrames = [max(habitFrames+1), max(habitFrames+1) + behavTime*60*fps - 1];
        frameEnd = max(frme);
        idxStart = 1;
        idxEnd = find(frme==frameEnd);
    elseif timeDirection == -1
        frameEnd = max(frme);
        behavFrames = [frameEnd - behavTime*60*fps, frameEnd];
        habitFrames = [min(behavFrames-1) - habitTime*60*fps, min(behavFrames-1)];
        frameStr = min(habitFrames);
        idxStart = find(frme==frameStr);
        idxEnd = length(frme);
    else
        fprintf('ERROR: timeDirection mode not set properly\n\n');
        return;
    end
    
    if evenHabitSegments > 1
        tempH = habitFrames;
        clear habitFrames;
        
        hLength = tempH(2) - tempH(1) + 1;
        hSegs = floor(hLength / evenHabitSegments);
        for i = 1:evenHabitSegments
            habitFrames(i, 1) = tempH(1) + (hSegs*(i-1));
            habitFrames(i, 2) = tempH(1) + (hSegs*i);
        end
    end
    
    if evenBehavSegments > 1
        tempB = behavFrames;
        clear behavFrames;
        
        bLength = tempB(2) - tempB(1) + 1;
        bSegs = floor(bLength / evenBehavSegments);
        for i = 1:evenBehavSegments            
            behavFrames(i, 1) = tempB(1) + (bSegs*(i-1));
            behavFrames(i, 2) = tempB(1) + (bSegs*i);
        end
    end
    
    for i = 1:vals %idxStart:idxEnd
        isinside = (floor(x-xPts(i)).^2 + floor(y-yPts(i)).^2) <= markerSize^2;
        
        if frme(i) >= habitFrames(1, 1) && frme(i) <= habitFrames(end, 2)
            positionHab = positionHab + isinside;
        elseif frme(i) >= behavFrames(1, 1) && frme(i) <= behavFrames(end, 2)
            positionBeh = positionBeh + isinside;
        end
        
        if xPts(i) < max(middX) && xPts(i) > min(middX) && ...
                yPts(i) < max(middY) && yPts(i) > min(middY)
            isMiddl(i) = 1;
        end
        
        xZoner(i) = floor(xPts(i) / xZoneDiv) + 1;
        yZoner(i) = floor(yPts(i) / yZoneDiv) + 1;
        if xZoner(i) < 1 || xZoner(i) > xSquares
            fprintf('ERROR: X-Zone detected invalid\n\n');
        end
        if yZoner(i) < 1 || yZoner(i) > ySquares
            fprintf('ERROR: Y-Zone detected invalid\n\n');
        end
        
        if i > idxStart
            distXPix = abs(xPts(i) - xPts(i-1)); % Currently in pixels
            distYPix = abs(yPts(i) - yPts(i-1)); % Currently in pixels
            
            distCM_X = distXPix * cmPerPixX;
            distCM_Y = distYPix * cmPerPixY;
            
            totDist = sqrt((distCM_X^2) + (distCM_Y^2));
            
            tVel(i) = totDist * fps; % This will be in "units" per second
            tDist(i) = tDist(i-1) + totDist;
            
            if xZoner(i) ~= xZoner(i-1) || yZoner(i) ~= yZoner(i-1)
                if (xZoner(i) == 1 || xZoner(i) == 3)
                    if (yZoner(i) == 1 || yZoner(i) == 3)
                        t1Shift(i) = 1;
                    elseif (yZoner(i) == 2)
                        t2Shift(i) = 1;
                    end
                elseif xZoner(i) == 2
                    if yZoner(i) == 2
                        t3Shift(i) = 1;
                    elseif (yZoner(i) == 1 || yZoner(i) == 3)
                        t2Shift(i) = 1;
                    end
                end
            end
        elseif i == idxStart
            tDist(i) = 0;
            tVel(i) = 0;
        end
    end
    startDist = tDist(frme == behavFrames(1, 1));
    
    cDist = tDist - startDist;
    
    modeD = {};
    timeD = [];
    for i = 1:evenHabitSegments
        habitIdx(i, 1) = find(frme == habitFrames(i, 1));
        habitIdx(i, 2) = find(frme == habitFrames(i, 2));
        
        totalDistH(i) = tDist(habitIdx(i, 2)) - tDist(habitIdx(i, 1));
        totalT1ChangesH(i) = sum(t1Shift(habitIdx(i, 1):habitIdx(i, 2)));
        totalT2ChangesH(i) = sum(t2Shift(habitIdx(i, 1):habitIdx(i, 2)));
        totalT3ChangesH(i) = sum(t3Shift(habitIdx(i, 1):habitIdx(i, 2)));
        
        aveVelH(i) = mean(tVel(habitIdx(i, 1):habitIdx(i, 2)));
        aveCenH(i) = mean(isMiddl(habitIdx(i, 1):habitIdx(i, 2)));
        
        modeD{i, 1} = {['Habituiation', sprintf('%02d', i)]};
        timeD = [timeD; habitTime / evenHabitSegments];
    end
        
    for i = 1:evenBehavSegments
        behavIdx(i, 1) = find(frme == behavFrames(i, 1));
        behavIdx(i, 2) = find(frme == behavFrames(i, 2));
        
        totalDistB(i) = tDist(behavIdx(i, 2)) - tDist(behavIdx(i, 1));
        totalT1ChangesB(i) = sum(t1Shift(behavIdx(i, 1):behavIdx(i, 2)));
        totalT2ChangesB(i) = sum(t2Shift(behavIdx(i, 1):behavIdx(i, 2)));
        totalT3ChangesB(i) = sum(t3Shift(behavIdx(i, 1):behavIdx(i, 2)));
        
        aveVelB(i) = mean(tVel(behavIdx(i, 1):behavIdx(i, 2)));
        aveCenB(i) = mean(isMiddl(behavIdx(i, 1):behavIdx(i, 2)));
        
        modeD{i + evenHabitSegments, 1} = {['Behavior', sprintf('%02d', i)]};
        timeD = [timeD; behavTime / evenBehavSegments];
    end
        
    totalDist = [totalDistH'; totalDistB'];
    aveVel = [aveVelH'; aveVelB'];
    aveCen = [aveCenH'; aveCenB'];
    totalT1Changes = [totalT1ChangesH'; totalT1ChangesB'];
    totalT2Changes = [totalT2ChangesH'; totalT2ChangesB'];
    totalT3Changes = [totalT3ChangesH'; totalT3ChangesB'];
    startFr = [habitIdx(1:end, 1); behavIdx(1:end, 1)];
    enderFr = [habitIdx(1:end, 2); behavIdx(1:end, 2)];
    
    tableData = table(modeD, timeD, startFr, enderFr, totalDist, aveVel, aveCen, totalT1Changes, totalT2Changes, totalT3Changes);
    tableData.Properties.VariableNames = {'Behavior_Phase', 'Phase_Time_mins', 'Start_Frame', 'End_Frame', 'Total_Distance_cm', 'Average_Velocity_cm_per_s', 'Percent_Time_In_Center_perc', 'T1_Shifts', 'T2_Shifts', 'T3_Shifts'};
    if ~exist(outDir, 'dir')
        mkdir(outDir);
    end
    writetable(tableData, [outDir, dataName, '_Results.csv']);
    
    if makeHeatmaps
        figure('units', 'normalized', 'outerposition', [0 0 1 1]);
        if combineHeatmaps
            heatmapData = positionBeh + positionHab;
        else
            heatmapData = positionBeh;
        end
        heatmapData = heatmapData ./ fps;
        imagesc(heatmapData);
        set(gca, 'Colormap', jet);
        title(['Behavioral Linear Heatmap Data - #', num2str(dataName)], 'FontSize', 16);
        axis square off;
        c1 = colorbar;
        c1.FontSize = 14;
        c1.LineWidth = 1;
        title(c1, 'Occupancy (s)', 'FontSize', 12);
        saveas(gcf, [outDir, dataName, '_HeatmapLinear.png']);
        print('-painters', '-dsvg', [outDir, dataName, '_HeatmapLinear.svg']);
        set(gca, 'ColorScale', 'log');
        c1.TickLabels = cellstr(num2str(reshape(c1.Ticks, [], 1), '%0.3f'));
        %set(gca, 'CTickLabel', cellstr(num2str(reshape(get(gca, 'CTick'), [], 1), '%0.3f')));
        title(['Behavioral Logarithmic Heatmap Data - #', num2str(dataName)]);
        saveas(gcf, [outDir, dataName, '_HeatmapLogarithmic.png']);
        print('-painters', '-dsvg', [outDir, dataName, '_HeatmapLogarithmic.svg']);
        close gcf;
    end
        
    
    if makeVideo
        writerObj = VideoWriter([outDir, dataName, '.avi']);
        writerObj.FrameRate = fps;
        frameSpeedMultiplier = 4;
        
        readerObj = VideoReader(vidDir);
        hShifters = zeros([1, 3]);
        bShifters = zeros([1, 3]);  
        
        positionVidHabit = zeros([maxX, maxY])';
        positionVidBehav = zeros([maxX, maxY])';
        maxZ_hab = max(max(positionHab));
        maxZ_beh = max(max(positionBeh));
        
        open(writerObj);
        startFrme = frme(1) - timePrior*fps;
        if startFrme < 1
            startFrme = 1;
        end
        
        for i = startFrme:frameSpeedMultiplier:frme(1)-1
            frameCnt = i;
            figure('units', 'normalized', 'outerposition', [0 0 1 1]);
            subplot(3, 3, [1, 2, 4, 5]);
            vidFrame = read(readerObj, frameCnt);
            mints = ceil((frameCnt - habitFrames(1)) / (fps*60));
            seccs = ceil(mod((habitFrames(1) - frameCnt), (fps*60)) / fps);
            imshow(vidFrame);
            title([strrep(dataName, ' ', '-'), ' Video Analysis: -', sprintf('%02d', mints), ':', sprintf('%02d', seccs)]);

            subplot(3, 3, 3);
            plot([behavFrames(1)-frme(1), behavFrames(1)-frme(1)], [floor(min(cDist)), ceil(max(cDist))], 'r-', 'linewidth', 2);
            xlim([0, slidingWin*fps]);
            ylim([floor(min(cDist)), ceil(max(cDist))]);
            title('Total Distance: NULL cm');
            xlabel('Frame');
            ylabel('Total Distance (cm)');

            subplot(3, 3, 6); % For velocity plot
            plot([behavFrames(1)-frme(1), behavFrames(1)-frme(1)], [0, ceil(max(tVel))], 'r-', 'linewidth', 2);
            xlim([0, slidingWin*fps]);
            ylim([0, ceil(max(tVel))]);
            title('Velocity: NULL cm/s');
            xlabel('Frame');
            ylabel('Velocity (cm/s)');
            
            midLine = 'k--';
            
            subplot(3, 3, 7);
            imagesc(positionVidHabit);
            title('Habituation Position Map');
            set(gca, 'Colormap', jet);
            set(gca, 'ColorScale', 'log');
            hold on;
            plot([min(middX), min(middX)], [min(middY), max(middY)], midLine, 'linewidth', 3);
            plot([max(middX), max(middX)], [min(middY), max(middY)], midLine, 'linewidth', 3);
            plot([min(middX), max(middX)], [min(middY), min(middY)], midLine, 'linewidth', 3);
            plot([min(middX), max(middX)], [max(middY), max(middY)], midLine, 'linewidth', 3);
            hold off;
            axis square off;
            
            subplot(3, 3, 8); % For habituation heatmap
            imagesc(positionVidBehav);
            title('Behavior Position Map');
            set(gca, 'Colormap', jet);
            set(gca, 'ColorScale', 'log');
            hold on;
            plot([min(middX), min(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
            plot([max(middX), max(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
            plot([min(middX), max(middX)], [min(middY), min(middY)], 'k--', 'linewidth', 3);
            plot([min(middX), max(middX)], [max(middY), max(middY)], 'k--', 'linewidth', 3);
            hold off;
            axis square off;
            
            subplot(3, 3, 9); % For graph depicting center pressence
            %currPercInMidd = floor(length(find(isMiddl(1:i)==1)) / i);
            plot([behavFrames(1)-frme(1), behavFrames(1)-frme(1)], [-0.5, 1.5], 'r-', 'linewidth', 2);
            xlim([0, slidingWin*fps]);
            ylim([-0.5, 1.5]);
            title('Detected in Center: 00%');
            xlabel('Frame');
            ylabel('State Machine');
            
            currFrame = getframe(gcf);
            close gcf;
            writeVideo(writerObj, currFrame);
        end
        for i = 1:frameSpeedMultiplier:length(frme)
            figure('units', 'normalized', 'outerposition', [0 0 1 1]);
            subplot(3, 3, [1, 2, 4, 5]); % For video frames
            vidFrame = read(readerObj, frme(i));
            mints = floor((frme(i) - habitFrames(1)) / (fps*60));
            seccs = floor(mod((frme(i)-habitFrames(1)), (fps*60)) / fps);
            imshow(vidFrame);
            title([strrep(dataName, ' ', '-'), ' Video Analysis: ', sprintf('%02d', mints), ':', sprintf('%02d', seccs)]);
            
            xlimits(1) = i - (round(slidingWin/2) * fps);
            xlimits(2) = i + (round(slidingWin/2) * fps);
            
            if xlimits(1) < 0
                xlimits(1) = 0;
            end
            
            subplot(3, 3, 3); % For total distance plot
            plot(1:i, cDist(1:i), 'linewidth', 4);
            hold on;
            plot([behavFrames(1)-frme(1), behavFrames(1)-frme(1)], [floor(min(cDist)), ceil(max(cDist))], 'r-', 'linewidth', 2);
            hold off;
            xlim(xlimits);
            ylim([cDist(i)-1500, cDist(i)+1500]);
            title(['Total Distance: ', sprintf('%04d', cDist(i)), ' cm']);
            xlabel('Frame');
            ylabel('Total Distance (cm)');
            
            subplot(3, 3, 6); % For velocity plot
            plot(1:i, tVel(1:i), 'linewidth', 4);
            hold on;
            plot([behavFrames(1)-frme(1), behavFrames(1)-frme(1)], [0, ceil(max(tVel))], 'r-', 'linewidth', 2);
            hold off;
            xlim(xlimits);
            ylim([0, max(tVel((xlimits(1)+1):i))+5]);
            title(['Velocity: ', sprintf('%04d', tVel(i)), ' cm/s']);
            xlabel('Frame');
            ylabel('Velocity (cm/s)');
            
            if isMiddl(i)
                midLine = 'w--';
            else
                midLine = 'k--';
            end
            
            if frme(i) >= habitFrames(1) && frme(i) <= habitFrames(2)
                subplot(3, 3, 7); % For habituation heatmap
                isinside = (floor(x-xPts(i)).^2 + floor(y-yPts(i)).^2) <= markerSize^2;
                positionVidHabit = positionVidHabit + isinside;
                imagesc(positionVidHabit);
                set(gca, 'Colormap', jet);
                set(gca, 'ColorScale', 'log');
                hold on;
                plot([min(middX), min(middX)], [min(middY), max(middY)], midLine, 'linewidth', 3);
                plot([max(middX), max(middX)], [min(middY), max(middY)], midLine, 'linewidth', 3);
                plot([min(middX), max(middX)], [min(middY), min(middY)], midLine, 'linewidth', 3);
                plot([min(middX), max(middX)], [max(middY), max(middY)], midLine, 'linewidth', 3);
                
                plot([1*xZoneDiv, 1*xZoneDiv], [minY, maxY], 'm--', 'linewidth', 2);
                plot([2*xZoneDiv, 2*xZoneDiv], [minY, maxY], 'm--', 'linewidth', 2);
                plot([minX, maxX], [1*yZoneDiv, 1*yZoneDiv], 'm--', 'linewidth', 2);
                plot([minX, maxX], [2*yZoneDiv, 2*yZoneDiv], 'm--', 'linewidth', 2);
                if frameSpeedMultiplier > 1 && i ~= startFrme
                    if any(t1Shift(i-frameSpeedMultiplier:i)==1)
                        hShifters(1) = hShifters(1) + 1;
                    elseif any(t2Shift(i-frameSpeedMultiplier:i)==1)
                        hShifters(2) = hShifters(2) + 1;
                    elseif any(t3Shift(i-frameSpeedMultiplier:i)==1)
                        hShifters(3) = hShifters(3) + 1;
                    end
                end
                plot(xPts(i), yPts(i), 'wo', 'linewidth', 4, 'markersize', 4);
                plot(xPts(i), yPts(i), 'k*', 'markersize', 4);
                
                title(['Habituation Position Map: ', sprintf('%02d', hShifters(1)), ',', sprintf('%02d', hShifters(2)), ',', sprintf('%02d', hShifters(3))]);
                hold off;
                axis square off;
                
                subplot(3, 3, 8); % For habituation heatmap
                imagesc(positionVidBehav);
                title('Behavior Position Map');
                set(gca, 'Colormap', jet);
                set(gca, 'ColorScale', 'log');
                hold on;
                plot([min(middX), min(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
                plot([max(middX), max(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
                plot([min(middX), max(middX)], [min(middY), min(middY)], 'k--', 'linewidth', 3);
                plot([min(middX), max(middX)], [max(middY), max(middY)], 'k--', 'linewidth', 3);
                hold off;
                axis square off;
            elseif frme(i) >= behavFrames(1) && frme(i) <= behavFrames(2)
                subplot(3, 3, 7); % For habituation heatmap
                imagesc(positionVidHabit);
                hold on;
                plot([min(middX), min(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
                plot([max(middX), max(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
                plot([min(middX), max(middX)], [min(middY), min(middY)], 'k--', 'linewidth', 3);
                plot([min(middX), max(middX)], [max(middY), max(middY)], 'k--', 'linewidth', 3);
                hold off;
                title('Habituation Position Map');
                set(gca, 'Colormap', jet);
                set(gca, 'ColorScale', 'log');               
                axis square off;
                
                subplot(3, 3, 8); % For habituation heatmap
                isinside = (floor(x-xPts(i)).^2 + floor(y-yPts(i)).^2) <= markerSize^2;
                positionVidBehav = positionVidBehav + isinside;
                imagesc(positionVidBehav);
                set(gca, 'Colormap', jet);
                set(gca, 'ColorScale', 'log'); 
                hold on;
                plot([min(middX), min(middX)], [min(middY), max(middY)], midLine, 'linewidth', 3);
                plot([max(middX), max(middX)], [min(middY), max(middY)], midLine, 'linewidth', 3);
                plot([min(middX), max(middX)], [min(middY), min(middY)], midLine, 'linewidth', 3);
                plot([min(middX), max(middX)], [max(middY), max(middY)], midLine, 'linewidth', 3);
                
                plot([1*xZoneDiv, 1*xZoneDiv], [minY, maxY], 'm--', 'linewidth', 2);
                plot([2*xZoneDiv, 2*xZoneDiv], [minY, maxY], 'm--', 'linewidth', 2);
                plot([minX, maxX], [1*yZoneDiv, 1*yZoneDiv], 'm--', 'linewidth', 2);
                plot([minX, maxX], [2*yZoneDiv, 2*yZoneDiv], 'm--', 'linewidth', 2);
                if frameSpeedMultiplier > 1 && i ~= startFrme
                    if any(t1Shift(i-frameSpeedMultiplier:i)==1)
                        bShifters(1) = bShifters(1) + 1;
                    elseif any(t2Shift(i-frameSpeedMultiplier:i)==1)
                        bShifters(2) = bShifters(2) + 1;
                    elseif any(t3Shift(i-frameSpeedMultiplier:i)==1)
                        bShifters(3) = bShifters(3) + 1;
                    end
                end
                title(['Behavior Position Map: ', sprintf('%02d', bShifters(1)), ',', sprintf('%02d', bShifters(2)), ',', sprintf('%02d', bShifters(3))]);
                plot(xPts(i), yPts(i), 'wo', 'linewidth', 4, 'markersize', 4);
                plot(xPts(i), yPts(i), 'k*', 'markersize', 4);
                hold off;
                axis square off;
                
            else
                subplot(3, 3, 7);
                imagesc(positionVidHabit);
                hold on;
                plot([min(middX), min(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
                plot([max(middX), max(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
                plot([min(middX), max(middX)], [min(middY), min(middY)], 'k--', 'linewidth', 3);
                plot([min(middX), max(middX)], [max(middY), max(middY)], 'k--', 'linewidth', 3);
                hold off;
                title('Habituation Position Map');
                set(gca, 'Colormap', jet);
                set(gca, 'ColorScale', 'log');               
                axis square off;
                
                subplot(3, 3, 8);
                imagesc(positionVidBehav);
                title('Behavior Position Map');
                set(gca, 'Colormap', jet);
                set(gca, 'ColorScale', 'log');
                hold on;
                plot([min(middX), min(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
                plot([max(middX), max(middX)], [min(middY), max(middY)], 'k--', 'linewidth', 3);
                plot([min(middX), max(middX)], [min(middY), min(middY)], 'k--', 'linewidth', 3);
                plot([min(middX), max(middX)], [max(middY), max(middY)], 'k--', 'linewidth', 3);
                hold off;
                title('Behavior Position Map');
                set(gca, 'Colormap', jet);
                set(gca, 'ColorScale', 'log');
                axis square off;
            end
            
            subplot(3, 3, 9); % For graph depicting center pressence
            %currPercInMidd = floor(length(find(isMiddl(1:i)==1)) / i);
            plot(1:i, isMiddl(1:i), 'linewidth', 4);
            hold on;
            plot([behavFrames(1)-frme(1), behavFrames(1)-frme(1)], [-0.5, 1.5], 'r-', 'linewidth', 2);
            hold off;
            xlim(xlimits);
            ylim([-0.5, 1.5]);
            title(['Detected in Center: ', sprintf('%02d', floor((length(find(isMiddl(1:i)==1))/i)*100)), '%']);
            xlabel('Frame');
            ylabel('State Machine');
            
            currFrame = getframe(gcf);
            close gcf;
            writeVideo(writerObj, currFrame);
        end
        close(writerObj);
    end
    
end