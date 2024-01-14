local Path = workspace.R6

local Instance_Info = ({
	['Part'] = {
		'Position',
		'Anchored',
		'CFrame',
		'Color',
		'Transparency',
		'Material',
		'CastShadow',
		'Size',
		'CanQuery',
		'CanTouch',
		'CanCollide',
		'CollisionGroup',
		'Shape',
		'Name',
		'Parent',
	},
	["SurfaceAppearance"] = { 
		'AlphaMode',
		'ColorMap',
		'MetalnessMap', 
		'NormalMap',
		'RoughnessMap',
		'ClassName',
		'Name',
		'Parent',
	},
	['MeshPart'] = {
		'Parent',
		'ClassName',
		'Size',
		'Position',
		'Anchored',
		'CanCollide',
		'BrickColor',
		'Color',
		'Name',
		'MeshId',
		'Material',
		'CanQuery',
		'CanTouch',
		'CollisionGroup',
		'Transparency',
		'MeshType',
		'TextureID',
		'Touched',
		'CFrame',
	},
	['Bone'] = {
		'CFrame',
		'Length',
		'Thickness',
		'Rotation',
		'Position',
		'Transform',
		'Parent',
		'Name',
	},
	['AnimationController'] = {
		'Name',
		'Parent'
	},
	['Animator'] = {
		'Name',
		'Parent'
	},
	['Folder'] = {
		'Name',
		'Parent'
	},
	['Model'] = {
		'Name',
		'Parent',
		'PrimaryPart'
	},
	['KeyframeSequence'] = {
		'Parent',
		'Priority',
		'Name',
	},
	['Keyframe'] = {
		'Parent',
		'Time',
		'Name',
	},
	['Pose'] = {
		'Parent',
		'CFrame',
		'EasingDirection',
		'EasingStyle',
		'Name',
		'Weight'
	},
	['Humanoid'] = {
		'ClassName',
		'Health',
		'MaxHealth',
		'WalkSpeed',
		'JumpPower',
		'PlatformStand',
		'HipHeight',
		'RigType',
		'DisplayName',
		'Parent',
		'Name',
	},
	['Motor6D'] = {
		'Name',
		'ClassName',
		'Parent',
		'C0',
		'C1',
		'CurrentAngle',
		'DesiredAngle',
		'MaxVelocity',
		'Part0',
		'Part1',
		'Enabled'
	},
	['Decal'] = {
		'Name',
		'ClassName',
		'Parent',
		'Texture',
		'Color3',
		'Transparency',
		'ZIndex'
	},
	['ParticleEmitter'] = {
		'Name',
		'ClassName',
		'Parent',	
		'Acceleration',
		'LightInfluence',
		'AngularVelocity',
		'AutoOrientation',
		'Color',
		'Drag',
		'EmissionDirection',
		'EmissionInheritance',
		'EmissionSpeed',
		'EmitterOffset',
		'EmitterSize',
		'EmitterShape',
		'EmitterSpread',
		'Enabled',
		'Lifetime',
		'LightEmission',
		'LightInfluence',
		'LockedToPart',
		'Orientation',
		'Rate',
		'Rotation',
		'RotSpeed',
		'Size',
		'Speed',
		'SpeedSpread',
		'SpreadAngle',
		'Texture',
		'Transparency',
		'VelocitySpread',
		'ZOffset',
	},
	['PointLight'] = {
		'Brightness',
		'Color',
		'Enabled',
		'Range',
		'Shadows',
		'Name',
		'ClassName',
		'Parent',
	}
})

local Setting = {
	LockPosition = true,
	TabLineCode = true,
}

local ItemJustCoder = {}

local function AddTab(str)
	if Setting.TabLineCode then
		return tostring(str or '')..'\n'
	end
	return str or ''
end

local function itemFind(name, item)
	for _, v in ipairs(ItemJustCoder) do
		local isMatch = false
		if not item then
			if v['OLD'] == name or v['NEW'] == name then
				isMatch = true
			end
		else
			if v['InstanceItem'] == item then
				isMatch = true
			end
		end

		if isMatch then
			return v['NEW']
		end
	end

	return false
end

function NumberSequenceToLua(sequence)
	local points = sequence.Keypoints
	local luaCode = "NumberSequence.new({"

	for _, point in pairs(points) do
		luaCode = luaCode .. "\n    NumberSequenceKeypoint.new(" .. point.Time .. ", " .. point.Value .. ", " .. point.Envelope .. "),"
	end

	if #points > 0 then
		luaCode = luaCode:sub(1, -2)
	end

	luaCode = luaCode .. "\n})"

	return luaCode
end

function colorSequenceToLua(colorSequence)
	local luaCode = "ColorSequence.new({"

	for _, keypoint in pairs(colorSequence.Keypoints) do
		local color = keypoint.Value
		local time = keypoint.Time

		local colorString = string.format("ColorSequenceKeypoint.new(%f, Color3.new(%f, %f, %f))", time, color.r, color.g, color.b)
		local keypointString = string.format("%s,", colorString)

		luaCode = luaCode .. keypointString
	end

	luaCode = string.sub(luaCode, 1, -2)

	luaCode = luaCode .. "})"

	return luaCode
end


local function GetCodeProp(typeofitem,item)
	if typeof(typeofitem) == 'CFrame' then
		return 'CFrame.new('..tostring(typeofitem)..')'
	end

	if typeof(typeofitem) == 'Vector3' then
		return 'Vector3.new('..tostring(typeofitem)..')'
	end

	if typeof(typeofitem) == 'Vector2' then
		return 'Vector2.new('..tostring(typeofitem)..')'
	end

	if typeof(typeofitem) == 'Instance' then
		local ppname = itemFind(nil,typeofitem) or tostring(typeofitem)
		return ppname
	end

	if typeof(typeofitem) == 'boolean' then
		return tostring(typeofitem)
	end

	if typeof(typeofitem) == 'number' then
		return tostring(typeofitem)
	end

	if typeof(typeofitem) == 'string' then
		return "[["..tostring(typeofitem).."]]"
	end

	if typeof(typeofitem) == 'BrickColor' then
		return "BrickColor.new('"..typeofitem.."')"
	end

	if typeof(typeofitem) == 'Color3' then
		return "Color3.new("..tostring(typeofitem)..")"
	end

	if typeof(typeofitem) == 'NumberRange' then
		return "NumberRange.new("..tostring(typeofitem.Min)..','..tostring(typeofitem.Max)..")"
	end

	if typeof(typeofitem) == 'NumberSequence' then
		return tostring(NumberSequenceToLua(typeofitem))
	end

	if typeof(typeofitem) == 'ColorSequence' then 
		return tostring(colorSequenceToLua(typeofitem))
	end

	if typeof(typeofitem) == 'EnumItem' then
		return tostring(typeofitem)
	end
end

local function AddCode(name,prop,item):BrickColor
	local code = [[-- item: ]]..name
	code = AddTab(code)
	for i,v in ipairs(prop) do
		pcall(function()
			if item[v] and v~='ClassName' then
				code = AddTab(code)
				local typeofitem = item[v]

				local IsAdd = false

				local value = GetCodeProp(typeofitem,item)

				if value then
					if v =='MeshId' then
						code = code..'pcall(function() print("MeshID Of '..tostring(item)..' mybe has error check Attribute name MeshIdFixed") '..name..':SetAttribute("MeshIdFixed",[['..tostring(typeofitem)..']])'
					end
					code = code..' '..name..'.'..v..' = '..value..';'
					if v =='MeshId' then
						code = code..'end)'
					end
				else
					print('UnknowIndex',typeofitem,v)
				end
			end
		end)
	end

	local index = code

	if item.ClassName == 'MeshPart' then
		code = AddTab(code)
		local namea = "_"..tostring(math.random(100,1000))
		code = code..' local '..namea..' = false;'
		code = code..tostring(name)..':GetPropertyChangedSignal("Size"):Connect(function() if '..namea..' == true then return end task.wait()'..index..' '..name..' = true'..' end)'
	end


	return code
end

local function StartTraveTable(Info:{etc},old:string)
	old = AddTab(old)

	for i,v:Instance in ipairs(Info) do
		local ItemName = '_'..v.Name..'_'

		if itemFind(ItemName) then
			ItemName = '_'..v.Name..tostring(math.random(10,1000))..tostring(math.random(10,1000))..'_'
		end

		ItemName = ItemName:gsub('[%-=+()%.]','_')
		ItemName = ItemName:gsub(' ','_')

		if itemFind(ItemName) then
			ItemName = '_'..ItemName..tostring(math.random(10,1000))..tostring(math.random(10,1000))..'_'
		end

		local parent = (itemFind(v.Parent.Name,v.Parent) or 'TargetModel')
		old = AddTab(old)
		old = old..'local '..ItemName..' = Instance.new("'..(v.ClassName)..'",'..parent..')'

		table.insert(ItemJustCoder,{
			OLD = v.Name,
			NEW = ItemName,
			InstanceItem = v,
			ParentName = parent
		})

		local ItemInfo = v:GetChildren()
		if ItemInfo[1] then
			old = old .. ' '..StartTraveTable(ItemInfo)
		end
	end

	return old
end

local function RunningCommand(Model:Model)
	ItemJustCoder = {}

	local Coding = [[--MODEL LEAK BY CAT_SUS | ]]..tostring(Model)..' |'; 
	Coding = AddTab(Coding)
	Coding = Coding..'local TargetModel = Instance.new("'..Model.ClassName..'",workspace)'

	table.insert(ItemJustCoder,{
		OLD = Model.Name,
		NEW = 'TargetModel',
		InstanceItem = Model,
		ParentName = 'workspace'
	})

	Coding = Coding..' '..tostring(StartTraveTable(Model:GetChildren()),Coding)

	for i,v in ipairs(ItemJustCoder) do
		if Instance_Info[v.InstanceItem.ClassName] then
			Coding = AddTab(Coding)
			local inded = Instance_Info[v.InstanceItem.ClassName]
			Coding = Coding..AddCode(v.NEW,inded,v.InstanceItem)
		end
		game:GetService("RunService").Heartbeat:Wait()
	end

	return Coding
end

RunningCommand(Path)
