using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Simulator : MonoBehaviour
{

    RawImage[][] blocks = new RawImage[10][];

    [SerializeField] GameObject cell;

    // Start is called before the first frame update
    void Start()
    {
        for(int i = 0; i < 10; i++)
        {
            blocks[i] = new RawImage[8];
        }

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                GameObject obj = Instantiate(cell);
                obj.name = "Cell: (" + x + ", " + y + ")";
                obj.transform.parent = transform;
                obj.transform.localPosition = new Vector2(105*x-450, 105*y -350);
                blocks[x][y] = obj.GetComponent<RawImage>();
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
