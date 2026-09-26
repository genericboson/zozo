using System.Text;

public static partial class ExcelSchemaConverter
{
    // 파일명(확장자 없는 소문자)으로 CLASS_ID를 만든다.
    // Engine/StaticData/StaticDataId.h의 FnvHash64와 반드시 동일한 알고리즘이어야 한다.
    private static long MakeClassId(string name)
    {
        ulong hash = 0xcbf29ce484222325UL;
        foreach (var b in Encoding.UTF8.GetBytes(NormalizeDataName(name)))
        {
            hash ^= b;
            hash *= 0x100000001b3UL;
        }

        return unchecked((long)hash);
    }

    // C++ 쪽과 키가 어긋나지 않도록 정규화 규칙을 한 곳에서만 정의한다.
    private static string NormalizeDataName(string name)
        => Path.GetFileNameWithoutExtension(name).ToLowerInvariant();
}
