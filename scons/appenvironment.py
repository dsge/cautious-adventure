
import urllib.request
import os
import zipfile
import shutil
import json
import tarfile

last_version_filename = "last_downloaded_version.json"


def ensure_blender_and_godot_binaries(godot_version='4.2.1', godot_suffix='stable', blender_version='4.0.2', override_blender_and_godot_editor_path='./blender-and-godot-editor'):

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
    mirror = "https://mirrors.sahilister.in"
    targetFolderName = "blender_{platformName}".format(version=blender_version, platformName=platformName)
    finalFolderPath = os.path.abspath(os.path.join(editorDirectory, targetFolderName))

    isZip = platformName == "windows"
    downloadFileName = "blender-{blender_version}-{platformName}-x64".format(blender_version=blender_version, platformName=platformName, extension=('zip' if isZip else 'tar.xz'))
    downloadFileNameWithExtension = "{downloadFileName}.{extension}".format(downloadFileName=downloadFileName, extension=('zip' if isZip else 'tar.xz'))

    if (not os.path.isdir(finalFolderPath) or force):
        print("Downloading fresh {targetFolderName} to '<project_root>/blender-and-godot-editor'...".format(
            targetFolderName=targetFolderName))
        url = "{mirror}/blender/release/Blender4.0/{downloadFileNameWithExtension}".format(mirror=mirror, downloadFileNameWithExtension=downloadFileNameWithExtension)
        local_tmp_filename, headers=urllib.request.urlretrieve(url)


        extractDirectory=os.path.dirname(local_tmp_filename)
        if (isZip):
            with zipfile.ZipFile(local_tmp_filename, "r") as zip_ref:
                zip_ref.extractall(extractDirectory)
        else:
            with tarfile.open(local_tmp_filename) as tar_ref:
                tar_ref.extractall(extractDirectory)
        shutil.move(os.path.join(extractDirectory, downloadFileName), finalFolderPath)
        if not os.name == 'nt':
            os.chmod(finalFolderPath, 0o744)
        return True
    return False


def ensure_godot_binary(version, suffix, platformBinaryName, editorDirectory, force):
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
    filename=os.path.join(editorDirectory, last_version_filename)
    if not os.path.isfile(filename):
        return True
    with open(filename) as f:
        data=json.load(f)
        return data['godot_version'] != version or data['godot_suffix'] != suffix or data['blender_version'] != blender_version


def update_last_downloaded_version(godot_version, godot_suffix, blender_version, editorDirectory):
    filename=os.path.join(editorDirectory, last_version_filename)
    dict={
        'godot_version': godot_version,
        'godot_suffix': godot_suffix,
        'blender_version': blender_version
    }
    with open(filename, "w") as outfile:
        json.dump(dict, outfile)


def ensure_godot_selfcontained_mode(editorDirectory):
    filename=os.path.join(editorDirectory, '._sc_')
    if not os.path.isfile(filename):
        with open(filename, 'a') as f:
            absolute_repo_root = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), '..'))
            relative_repo_root = os.path.relpath(absolute_repo_root, editorDirectory)
            if (relative_repo_root == '..'):
                repo_parent = os.path.join(absolute_repo_root, '..')
                relative_repo_root = os.path.join('..', '..', os.path.relpath(absolute_repo_root, repo_parent), 'godot-project')
            blender3_path = os.path.abspath(os.path.join(absolute_repo_root, 'blender-and-godot-editor', "blender_{}".format("windows" if os.name == 'nt' else "linux")))
            f.write("[init_projects]\nlist=[\"{}\"]\n\n[presets]\nfilesystem/import/blender/blender3_path = \"{}\"".format(relative_repo_root, blender3_path))
