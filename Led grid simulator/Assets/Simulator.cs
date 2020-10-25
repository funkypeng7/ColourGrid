using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System;

public class Simulator : MonoBehaviour
{
    [SerializeField] bool isRunningInDebug;
    string currentDir = Environment.GetFolderPath(System.Environment.SpecialFolder.UserProfile);
    const string coloursFile = "/Programming/Colours.txt";
    const string mousePosFile = "/Programming/MousePos.txt";

    RawImage[][] blocks = new RawImage[10][];
    Color32[][] colours = new Color32[10][];

    [SerializeField] GameObject cell;

    // Start is called before the first frame update
    void Start()
    {
        if (isRunningInDebug)
            currentDir += "/Programming/ColourGrid";
        if(!File.Exists(currentDir + "/Programming/MousePos.txt"))
        {
            FileStream file = File.Create(currentDir + "/Programming/MousePos.txt");
            file.Close();
        }


        for (int i = 0; i < 10; i++)
        {
            blocks[i] = new RawImage[8];
            colours[i] = new Color32[8];
        }

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                GameObject obj = Instantiate(cell);
                obj.name = "Cell: (" + x + ", " + y + ")";
                obj.transform.SetParent(transform);
                obj.transform.localPosition = new Vector2(105 * x - 472.5f, 105 * y - 367.5f);
                blocks[x][y] = obj.GetComponent<RawImage>();
            }
        }
        StartCoroutine(ReadFile());
    }

    private void Update()
    {
        string str;
        Vector3 MousePos = (Input.mousePosition - new Vector3(437.5f, 122.5f));
        
        if (MousePos.x < 0 || MousePos.x > 1045 || MousePos.y < 0 || MousePos.y > 835f || !Input.GetMouseButton(0))
            str = "10000, 10000";
        else
        {
            str = MousePos.x.ToString() + "," + MousePos.y.ToString();
        }
        //Debug.Log(str);
        File.WriteAllText(currentDir + "/Programming/MousePos.txt", str);

    }
    

    IEnumerator ReadFile()
    {

        
        while (true)
        {
            int offset;
            string text = System.IO.File.ReadAllText(currentDir + "/Programming/Colours.txt");
            if (text == "")
                continue;
            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 10; x++)
                {
                    byte[] colour = new byte[3];
                    for (int c = 0; c < 3; c++)
                    {
                        int startChar = (y * 30 + x * 3 + c) * 2;
                        try
                        {
                            colour[c] = byte.Parse(text.Substring(startChar, 2), System.Globalization.NumberStyles.HexNumber);
                        }
                        catch
                        {
                            Debug.Log("Failed at " + startChar);
                        }
                    }
                    blocks[x][y].color = new Color32(colour[0], colour[1], colour[2], 255);
                }
            }
            yield return null;
        }
    }
}