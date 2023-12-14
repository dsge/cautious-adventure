
import urllib.request
import os
import zipfile
import shutil
import json

last_version_filename = "last_downloaded_version.json"


def ensure_godot_binaries(version='4.2.1', suffix='stable', override_godot_editor_path='./godot-editor'):
    editorDirectory = os.path.abspath(os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', override_godot_editor_path))
    if (not os.path.isdir(editorDirectory)):
        os.makedirs(editorDirectory)
    force = needs_fresh_download(version, suffix, editorDirectory)
    did_download = False
    if (ensure_binary(version, suffix, 'linux.x86_64', editorDirectory, force)):
        did_download = True
    if (ensure_binary(version, suffix, 'win64.exe', editorDirectory, force)):
        did_download = True
    if (did_download):
        update_last_downloaded_version(version, suffix, editorDirectory)
    ensure_export_templates(version, suffix, editorDirectory)
    ensure_godot_selfcontained_mode(editorDirectory)
    ensure_godot_editor_project(editorDirectory)


def ensure_binary(version, suffix, platformBinaryName, editorDirectory, force):
    binaryName = "Godot_v{version}-{suffix}_{platformBinaryName}".format(
        version=version, suffix=suffix, platformBinaryName=platformBinaryName)
    targetBinaryName = "Godot_{platformBinaryName}".format(
        platformBinaryName=platformBinaryName)
    finalEditorPath = os.path.abspath(
        os.path.join(editorDirectory, targetBinaryName))

    if (not os.path.isfile(finalEditorPath) or force):
        print("Downloading fresh {platformBinaryName} Godot Editor binary to '<project_root>/godot-editor'...".format(
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
        print("Downloading fresh Export Templates to '<project_root>/godot-editor/editor_data/export-templates'...")
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



def needs_fresh_download(version, suffix, editorDirectory):
    filename=os.path.join(editorDirectory, last_version_filename)
    if not os.path.isfile(filename):
        return True
    with open(filename) as f:
        data=json.load(f)
        return data['version'] != version or data['suffix'] != suffix


def update_last_downloaded_version(version, suffix, editorDirectory):
    filename=os.path.join(editorDirectory, last_version_filename)
    dict={
        'version': version,
        'suffix': suffix
    }
    with open(filename, "w") as outfile:
        json.dump(dict, outfile)


def ensure_godot_selfcontained_mode(editorDirectory):
    filename=os.path.join(editorDirectory, '._sc_')
    if not os.path.isfile(filename):
        open(filename, 'a').close()


def ensure_godot_editor_project(editorDirectory):
    filename=os.path.join(editorDirectory, 'editor_data', 'projects.cfg')
    if not os.path.isfile(filename):
        if (not os.path.isdir(os.path.dirname(filename))):
            os.makedirs(os.path.dirname(filename))
        project_root=os.path.abspath(os.path.join(os.path.dirname(
            os.path.realpath(__file__)), '..'))
        with open(filename, "w") as outfile:
            outfile.write("[{project_root}]\n\nfavorite=false\n\n".format(
                project_root=project_root))
