
import urllib.request
import os
import zipfile
import shutil
import json
import tarfile
import configparser

last_version_filename = "last_downloaded_version.json"


def ensure_blender_and_godot_binaries(godot_version='4.2.2', godot_suffix='stable', blender_version='4.2.0', override_blender_and_godot_editor_path='./blender-and-godot-editor'):
    """
    (Re)downloads godot and blender with the correct versions and extracts them to `override_blender_and_godot_editor_path` if they aren't already there

    Parameters:
        godot_version (str): e.g. "4.2.1"
        godot_suffix (str): e.g. "stable"
        blender_version (str): e.g. "4.0.2"
        override_blender_and_godot_editor_path (str): absolute path to a folder
    """
    editorDirectory = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', override_blender_and_godot_editor_path))
    if (not os.path.isdir(editorDirectory)):
        os.makedirs(editorDirectory)
    force = needs_fresh_download(godot_version, godot_suffix, blender_version, editorDirectory)
    did_download = False
    if (ensure_godot_binary(godot_version, godot_suffix, 'linux.x86_64', editorDirectory, force)):
        did_download = True
    if (ensure_godot_binary(godot_version, godot_suffix, 'win64.exe', editorDirectory, force)):
        did_download = True
    if (ensure_blender_folder(blender_version, 'windows', editorDirectory, force)):
        did_download = True
    if (ensure_blender_folder(blender_version, 'linux', editorDirectory, force)):
        did_download = True
    if (did_download):
        update_last_downloaded_version(godot_version, godot_suffix, blender_version, editorDirectory)
    ensure_export_templates(godot_version, godot_suffix, editorDirectory)
    ensure_godot_selfcontained_mode(editorDirectory)

def ensure_blender_folder(blender_version, platformName, editorDirectory, force):
    """
    Downloads blender and extracts it to `editorDirectory` if it isn't already there
    e.g.
        from: https://mirrors.sahilister.in/blender/release/Blender4.0/blender-4.0.2-linux-x64.tar.xz
        to: <repo root>/blender-and-godot-editor/blender_linux/ (folder)
 
    Parameters:
        blender_version (str): e.g. "4.0.2"
        platformName (str): "windows" or "linux"
        editorDirectory (str): absolute path to a folder
        force (bool): set it to true to re-download the folder even if it already exists
 
    Returns:
        bool: whether or not a download actually happened
    """
    mirror = "https://mirrors.sahilister.in"
    targetFolderName = "blender_{platformName}".format(version=blender_version, platformName=platformName)
    finalFolderPath = os.path.abspath(os.path.join(editorDirectory, targetFolderName))

    isZip = platformName == "windows"
    downloadFileName = "blender-{blender_version}-{platformName}-x64".format(blender_version=blender_version, platformName=platformName, extension=('zip' if isZip else 'tar.xz'))
    downloadFileNameWithExtension = "{downloadFileName}.{extension}".format(downloadFileName=downloadFileName, extension=('zip' if isZip else 'tar.xz'))

    if (not os.path.isdir(finalFolderPath) or force):
        print("Downloading fresh {targetFolderName} to '<project_root>/blender-and-godot-editor'...".format(
            targetFolderName=targetFolderName))
        majorMinorVersion = '.'.join([blender_version.split(".")[0], blender_version.split(".")[1]])
        url = "{mirror}/blender/release/Blender{majorMinorVersion}/{downloadFileNameWithExtension}".format(mirror=mirror, downloadFileNameWithExtension=downloadFileNameWithExtension, majorMinorVersion=majorMinorVersion)
        local_tmp_filename, headers=urllib.request.urlretrieve(url)      


        extractDirectory=os.path.dirname(local_tmp_filename)
        if (isZip):
            with zipfile.ZipFile(local_tmp_filename, "r") as zip_ref:
                zip_ref.extractall(extractDirectory)
        else:
            with tarfile.open(local_tmp_filename) as tar_ref:
                tar_ref.extractall(extractDirectory)
        os.remove(local_tmp_filename)
        shutil.move(os.path.join(extractDirectory, downloadFileName), finalFolderPath)
        if not os.name == 'nt':
            os.chmod(finalFolderPath, 0o744)
        return True
    return False


def ensure_godot_binary(version, suffix, platformBinaryName, editorDirectory, force):
    """
    Downloads Godot and extracts it to `editorDirectory` if it isn't already there
    e.g.
        from: https://downloads.tuxfamily.org/godotengine/4.2.1/Godot_v4.2.1-stable_linux.x86_64.zip
        to: <repo root>/blender-and-godot-editor/Godot_linux.x86_64 (file)
 
    Parameters:
        version (str): e.g. "4.2.1"
        suffix (str): e.g. "stable"
        platformBinaryName (str): "win64.exe" or "linux.86_64"
        editorDirectory (str): absolute path to a folder
        force (bool): set it to true to re-download the folder even if it already exists
 
    Returns:
        bool: whether or not a download actually happened
    """
    binaryName = "Godot_v{version}-{suffix}_{platformBinaryName}".format(
        version=version, suffix=suffix, platformBinaryName=platformBinaryName)
    targetBinaryName = "Godot_{platformBinaryName}".format(
        platformBinaryName=platformBinaryName)
    finalEditorPath = os.path.abspath(
        os.path.join(editorDirectory, targetBinaryName))

    if (not os.path.isfile(finalEditorPath) or force):
        print("Downloading fresh {platformBinaryName} Godot Editor binary to '<project_root>/blender-and-godot-editor'...".format(
            platformBinaryName=platformBinaryName))
        url = "https://downloads.tuxfamily.org/godotengine/{version}/{binaryName}.zip".format(
            version=version, binaryName=binaryName)        
        local_tmp_filename, headers=urllib.request.urlretrieve(url)
        with zipfile.ZipFile(local_tmp_filename, "r") as zip_ref:
            extractDirectory=os.path.dirname(local_tmp_filename)
            zip_ref.extractall(extractDirectory)
            shutil.move(os.path.join(extractDirectory,
                        binaryName), finalEditorPath)
            if not os.name == 'nt':
                os.chmod(finalEditorPath, 0o744)

            return True
    return False

def ensure_export_templates(version, suffix, editorDirectory):
    """
    Downloads all of Godot's "export templates" and extracts them to `editorDirectory`/editor_data/export_templates if they aren't already there
    e.g.
        from: https://downloads.tuxfamily.org/godotengine/4.2.1/Godot_v4.2.1-stable_export_templates.tpz
        to: <repo root>/blender-and-godot-editor/editor_data/export_templates (folder)
 
    Parameters:
        version (str): e.g. "4.2.1"
        suffix (str): e.g. "stable"
        editorDirectory (str): absolute path to a folder
        force (bool): set it to true to re-download the folder even if it already exists
 
    Returns:
        bool: whether or not a download actually happened
    """
    templatesFinalFolder=os.path.abspath(os.path.join(
        editorDirectory, 'editor_data', 'export_templates', "{}.{}".format(version, suffix)))
    if (not os.path.isdir(templatesFinalFolder)):
        print("Downloading fresh Export Templates to '<project_root>/blender-and-godot-editor/editor_data/export-templates'...")
        url="https://downloads.tuxfamily.org/godotengine/{version}/Godot_v{version}-{suffix}_export_templates.tpz".format(
            version=version, suffix=suffix)
        local_tmp_filename, headers=urllib.request.urlretrieve(url)
        with zipfile.ZipFile(local_tmp_filename, "r") as zip_ref:
            extractDirectory=os.path.dirname(local_tmp_filename)
            zip_ref.extractall(extractDirectory)
            src = os.path.join(extractDirectory, 'templates')
            if (not os.path.isdir(templatesFinalFolder)):
                os.makedirs(templatesFinalFolder)
            file_names = os.listdir(src)   
            for file_name in file_names:
                shutil.move(os.path.join(src, file_name), templatesFinalFolder)



def needs_fresh_download(version, suffix, blender_version, editorDirectory):
    """
    Checks `editorDirectory`/last_downloaded_version.json to see if a forced fresh download for everything is necessary
    It's necessary when the json file doesn't exist or contains different versions compared to what we need now.
 
    Parameters:
        version (str): e.g. "4.2.1"
        suffix (str): e.g. "stable"
        editorDirectory (str): absolute path to a folder
 
    Returns:
        bool: whether or not a complete fresh download is necessary
    """
    filename=os.path.join(editorDirectory, last_version_filename)
    if not os.path.isfile(filename):
        return True
    with open(filename) as f:
        data=json.load(f)
        return data['godot_version'] != version or data['godot_suffix'] != suffix or data['blender_version'] != blender_version


def update_last_downloaded_version(godot_version, godot_suffix, blender_version, editorDirectory):
    """
    Updates `editorDirectory`/last_downloaded_version.json to make sure it contains information about the newly downloaded versions
    """
    filename=os.path.join(editorDirectory, last_version_filename)
    dict={
        'godot_version': godot_version,
        'godot_suffix': godot_suffix,
        'blender_version': blender_version
    }
    with open(filename, "w") as outfile:
        json.dump(dict, outfile)


def ensure_godot_selfcontained_mode(editorDirectory):
    """
    (Re)creates the `editorDirectory`/._sc_ to set Godot into the "self-contained" mode
    Also puts some default values in it that Godot will read upon it's first ever startup
    """
    filename=os.path.join(editorDirectory, '._sc_')
    if not os.path.isfile(filename) or True:
        absolute_repo_root = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), '..'))
        relative_repo_root = os.path.relpath(absolute_repo_root, editorDirectory)
        if (relative_repo_root == '..'):
            repo_parent = os.path.join(absolute_repo_root, '..')
            relative_repo_root = os.path.join('..', '..', os.path.relpath(absolute_repo_root, repo_parent), 'godot-project')
        blender3_path = os.path.abspath(os.path.join(editorDirectory, "blender_{}".format("windows" if os.name == 'nt' else "linux")))
        
        config = configparser.ConfigParser()
        config['init_projects'] = {'list': "[\"{}\"]".format(relative_repo_root)}
        config['presets'] = {
            'filesystem/import/blender/blender3_path': "\"{}\"".format(blender3_path),
            'filesystem/import/blender/rpc_port': 0
        }
        with open(filename, 'w') as f:
            config.write(f)
