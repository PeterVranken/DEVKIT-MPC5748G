$usage = `
'usage: .\S32DS-IDE.ps1
  Open S32DS Eclipse IDE for build and debugging of project'

function endWithError { write-host $usage; exit; }

# Support help
#if($args[0] -match '^$|^(-h|/h|/\?|--help)$') {endWithError}

# Limit the allowed number of parameters.
#if($args[0] -match '.') {endWithError}

# Prepare required environment variables and system search path.
.\setEnv.ps1

# The Eclipse based Code Warrior IDE is started with a local, project owned workspace.
."$env:S32DS_HOME\eclipse\s32ds.exe" -data .\workspaceS32DS
